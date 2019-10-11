#ifndef THREAD_CAM_H
#define THREAD_CAM_H

#include <QThread>
#include <QTimer>
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QDebug>
#include <QImage>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include "raspicam/raspicam_cv.h"
//#include "raspicam/raspicam.h"

using namespace cv;
using namespace std;
using namespace raspicam;
//using namespace raspicam_cv;

class thread_cam : public QThread
{
    Q_OBJECT
public:
    explicit thread_cam(QObject *parent = 0);
    thread_cam(int set_count=0)
    {
        count=set_count;
    }

    void show_cam();
    double getTimeMS(void);

protected:
    void run();

private:
    int count;
    QTimer *timer;
    Mat img;
    QImage Qimg;
    VideoCapture cap;
    //RaspiCam_Cv cam;

    double dPreTime;

signals:
    void return_QImage(QImage);
    void return_FPS(double);

public slots:
};

#endif // THREAD_CAM_H
