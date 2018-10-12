#-------------------------------------------------
#
# Project created by QtCreator 2018-10-05T10:06:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include

LIBS += /usr/lib/libopencv_calib3d.so \
        /usr/lib/libopencv_stitching.so \
        /usr/lib/libopencv_gpu.so \
        /usr/lib/libopencv_contrib.so \
        /usr/lib/libopencv_superres.so \
        /usr/lib/libopencv_highgui.so \
        /usr/lib/libopencv_objdetect.so \
        /usr/lib/libopencv_core.so \
        /usr/lib/libopencv_imgproc.so \
        /usr/lib/libopencv_video.so \
        /usr/lib/libopencv_features2d.so \
        /usr/lib/libopencv_legacy.so \
        /usr/lib/libopencv_videostab.so \
        /usr/lib/libopencv_photo.so \
        /usr/lib/libopencv_flann.so \
        /usr/lib/libopencv_ml.so
