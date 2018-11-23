#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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

private slots:
    void on_Open_clicked();
    void updatePicture();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture cap;
};

#endif // MAINWINDOW_H
