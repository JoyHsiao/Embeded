#include "dialog.h"
#include "ui_dialog.h"

#include "QTimer"
#include <QDir>
#include <string>
#include <iostream>
#include <opencv2/ocl/ocl.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QImage Dialog::Mat2QImage(Mat &image)
{
    if (image.type() == CV_8UC1) {
        return QImage((unsigned char *)image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
    }
    else
    {
        cvtColor(image, image, CV_BGR2RGB);
        return QImage((unsigned char *)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    }
}

void Dialog::getFrame(VideoCapture *cap){
    num = 0;
    cap2 =cap;
    if(!cap2->isOpened())
        qDebug() << "Cap2 is empty!";
    else{
        timer = new QTimer(this);
        timer->setInterval(1000); // 設定每30ms觸發一次
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start();
    }
}

void Dialog::update() {
    Mat QtFaceFrame;
    *cap2 >> faceFrame; // get a new frame from camera
    QtFaceFrame=faceFrame.clone();
    if(faceFrame.empty())
        qDebug() << "video frame empty!!";
    ui->face->setPixmap(QPixmap::fromImage(Mat2QImage(QtFaceFrame)).scaled(this->ui->face->size())); //顯示
}

void Dialog::detect(cv::Mat frame,String dir)
{
    cv::CascadeClassifier _faceCascade;
    cv::CascadeClassifier _eyesCascade;
    //載入model
    _faceCascade.load("haarcascade_frontalface_alt_tree.xml");
    _eyesCascade.load("haarcascade_eye_tree_eyeglasses.xml");
    std::vector<cv::Rect> faces;
    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, CV_BGR2GRAY);
    // detect face 找人臉
    _faceCascade.detectMultiScale(frameGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(16, 16));
    qDebug() << faces.size();
    for (size_t i = 0; i < faces.size(); i++)
    {
        num += 1;
        Mat faceRoi = frameGray(faces[i]);
        cv::resize(faceRoi, faceRoi, Size(250,250), 0, 0, CV_INTER_LINEAR);
        stringstream ss;
        ss << num;
        String s = ss.str();
        s = dir + "/" + s + ".jpg";
        cv::imwrite( s, faceRoi );
    }
}

void Dialog::on_capture_clicked()
{
    dir_str = ui->lineEdit->text();
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "success" << res;
    }
    std::string dir_face = dir_str.toUtf8().constData();
    detect(faceFrame, dir_face);
}

void Dialog::on_buttonBox_accepted()
{
    emit sendData(ui->lineEdit->text());
}
