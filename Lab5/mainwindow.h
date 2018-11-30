#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QTimer>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage Mat2QImage(Mat &);
    void HOG_SVM(Mat);
    void detectAndDisplay(Mat);
    void Recognizer();
    VideoCapture cap;
    Mat videoFrame,faceRoi;
    string dir_face;
    Dialog *dialog;
    int j=1;
    void sendData(QString);
    void updateModel(QString);
    void count(QString, int);

private slots:
    void on_Open_clicked();
    void updatePicture();
    void on_NewFace_clicked();
    void on_Recognition_clicked();
    void receiveData(QString);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    vector<Mat> images;
    vector<int> labels;
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
};

#endif // MAINWINDOW_H
