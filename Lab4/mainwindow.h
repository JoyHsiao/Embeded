#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
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
    int findBiggestContour(std::vector<std::vector<Point> >);
    double findAngle(cv::Point, cv::Point, cv::Point);

private slots:
    void on_Open_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
