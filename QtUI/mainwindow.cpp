#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread_cam1=new thread_cam(0);
//    thread_cam2=new thread_cam(1);
//    thread_cam3=new thread_cam(2);
//    thread_cam4=new thread_cam(3);

    connect(thread_cam1,&thread_cam::return_QImage,this,&MainWindow::get_QImage1);
    connect(thread_cam1,&thread_cam::return_FPS,this,&MainWindow::get_FPS);

//    connect(thread_cam2,&thread_cam::return_QImage,this,&MainWindow::get_QImage2);
//    connect(thread_cam3,&thread_cam::return_QImage,this,&MainWindow::get_QImage3);
//    connect(thread_cam4,&thread_cam::return_QImage,this,&MainWindow::get_QImage4);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_QImage1(QImage img_temp)
{
    image=img_temp;
    image.scaled(ui->liveLabel1->width(),ui->liveLabel1->height());
    ui->liveLabel1->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::get_FPS(double dFPS)
{
    QString strFPS=QString::number(dFPS);
    ui->fpsLabel->setText(strFPS);
}

//void MainWindow::get_QImage2(QImage img_temp)
//{
//    image=img_temp;
//    image.scaled(ui->label_2->width(),ui->label_2->height());
//    ui->label_2->setPixmap(QPixmap::fromImage(image));
//}

//void MainWindow::get_QImage3(QImage img_temp)
//{
//    image=img_temp;
//    image.scaled(ui->label_3->width(),ui->label_3->height());
//    ui->label_3->setPixmap(QPixmap::fromImage(image));
//}

//void MainWindow::get_QImage4(QImage img_temp)
//{
//    image=img_temp;
//    image.scaled(ui->label_4->width(),ui->label_4->height());
//    ui->label_4->setPixmap(QPixmap::fromImage(image));
//}

void MainWindow::on_grabButton_clicked()
{
    thread_cam1->start();
//    thread_cam2->start();
//    thread_cam3->start();
//    thread_cam4->start();
}

void MainWindow::on_stopButton_clicked()
{
    thread_cam1->quit();
//    thread_cam2->quit();
//    thread_cam3->quit();
//    thread_cam4->quit();
}
