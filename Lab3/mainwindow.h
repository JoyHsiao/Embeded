#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage convertProcess(cv::Mat converImage);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openTarget_clicked();

    void on_openTemp_clicked();

    void on_countors_clicked();

    void on_circle_clicked();

    void on_triangle_clicked();

    void on_rectangle_clicked();

    void on_surf_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat lImage;
    cv::Mat rImage;
    QImage myShowImage;
    cv::Mat grayimg;

};

#endif // MAINWINDOW_H
