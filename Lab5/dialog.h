#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
signals:
    void sendData(QString);

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QImage Mat2QImage(Mat &);
    Mat faceFrame;
    QString dir_str;
    void getFrame(VideoCapture *);
    int num;
    void detect(Mat,String);


private slots:
    void on_capture_clicked();
    void update();
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    VideoCapture *cap2;
};

#endif // DIALOG_H
