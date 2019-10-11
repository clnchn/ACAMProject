#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread_cam.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_grabButton_clicked();

private slots:

    void get_QImage1(QImage);
    void get_FPS(double);

//    void get_QImage2(QImage);
//    void get_QImage3(QImage);
//    void get_QImage4(QImage);


    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;

    thread_cam *thread_cam1;
//    thread_cam *thread_cam2;
//    thread_cam *thread_cam3;
//    thread_cam *thread_cam4;

    double dFPS;
    QImage image;

};

#endif // MAINWINDOW_H

