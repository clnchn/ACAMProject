#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T16:55:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCameraUI2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread_cam.cpp

HEADERS  += mainwindow.h \
    thread_cam.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

//QMAKE_LIBDIR += /usr/local/lib

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_videoio.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_imgcodecs.so

