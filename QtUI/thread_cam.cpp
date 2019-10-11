#include "thread_cam.h"
#include <QString>


thread_cam::thread_cam(QObject *parent) : QThread(parent)
{

}

void thread_cam::run()
{

    //cap = VideoCapture("nvcamerasrc sensor-id=0 auto-exposure=0 exposure-time=0.02 ! video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
    Mat frame;
    cap.set(CAP_PROP_FRAME_WIDTH,1920);
    cap.set(CAP_PROP_FRAME_HEIGHT,1080);
    cap.set(CAP_PROP_FORMAT,CV_8UC1);//I420
    cap.set(CAP_PROP_FPS,30);

    QString massage=QString("camera%1 opens fail").arg(count);

    if(!cap.isOpened())
    {
        qDebug()<<massage;
    }
    timer=new QTimer();
    timer->start(50);
    connect(timer,&QTimer::timeout,this,&thread_cam::show_cam);
    this->exec();

}

void thread_cam::show_cam()
{
    double dCurTime=getTimeMS();		// Time1

    double dTimeDiff=dCurTime-dPreTime;
    double dFPS=1000.0/(dCurTime-dPreTime);

    dPreTime=dCurTime;

    Mat frame;
    Mat imgTh;
    Mat imgProc1;
    Mat imgGray;
    Mat imgProc2;

    QString massage=QString("camera%1 capture fail").arg(count);
    //if (!cam.retrieve(img))
    //{
//        qDebug()<<massage;
  //  }

    Rect rect1=Rect(100,100,1000,500);
    //Rect rect1=Rect(300,300,600,200);

    imgProc1=img(rect1);

    cvtColor( imgProc1, imgGray, CV_BGR2GRAY );



    threshold(imgGray,imgTh,150,255,THRESH_BINARY_INV);


    Mat imgFF=imgTh.clone();
    floodFill(imgFF,cv::Point(10,10),Scalar(0));
    floodFill(imgFF,cv::Point(10,490),Scalar(0));

    //imshow("imgFF",imgFF);

    //cv::Vec3b wPixel(255,255,255);
    Rect ccomp;
    for(int m=0;m<imgFF.rows;m++)
    {
        for(int n=0;n<imgFF.cols;n++)
        {
            int iPixel=imgFF.at<uchar>(m,n);
            if(iPixel==255)
            {
                int iArea=floodFill(imgFF,Point(n,m),Scalar(50),&ccomp);
                if(iArea<200)
                {
                    floodFill(imgFF,Point(n,m),Scalar(0));
                }
                else
                {
                    circle(imgProc1,Point(ccomp.x+ccomp.width/2,ccomp.y+ccomp.height/2),30,Scalar(255,0,0),2,LINE_8);
                }
            }
        }
    }


    QImage  Qimg((uchar*) imgProc1.data, imgProc1.cols, imgProc1.rows, imgProc1.step, QImage::Format_RGB888 );

    QString cam_name=QString("camera%1").arg(count);

    //imshow(cam_name.toStdString(),img);
    emit return_QImage(Qimg);

    double dTime1=getTimeMS();		// Time1

    emit return_FPS(dTime1-dCurTime);


}

double thread_cam::getTimeMS(void)
{
    struct timeval  time1;
    double time1_ms;

    // convert tv_sec & tv_usec to millisecond
    gettimeofday(&time1, NULL);
    time1_ms=(time1.tv_sec) * 1000 + (time1.tv_usec) / 1000;

    return time1_ms;
}
