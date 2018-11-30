#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include <QDir>
#include <opencv2/ocl/ocl.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::detectAndDisplay(cv::Mat videoFrame)
{
    Mat frame=videoFrame.clone();
    cv::CascadeClassifier _faceCascade;
    cv::CascadeClassifier _eyesCascade;
    cv::SVM svm;
    cv::HOGDescriptor hogDescriptor = cv::HOGDescriptor(cv::Size(64, 144), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
    std::vector<float> feature;

    //載入face model
    _faceCascade.load("haarcascade_frontalface_alt_tree.xml");
    _eyesCascade.load("haarcascade_eye_tree_eyeglasses.xml");
    // load people model
    string modelpath = "people.xml";
    unsigned int peopleNum=0;
    FileStorage svm_fs(modelpath,FileStorage::READ);
    if(svm_fs.isOpened())
        svm.load(modelpath.c_str());
    else
        qDebug()<<"load model Fail!";

    std::vector<cv::Rect> faces;
    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, CV_BGR2GRAY);
    // detect face 找人臉
    _faceCascade.detectMultiScale(frameGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(16, 16));
    //qDebug() << faces.size();
    for (size_t i = 0; i < faces.size(); i++)
    {
        cv::rectangle(frame, faces[i], cv::Scalar(0, 128, 255), 3);
        faceRoi = frameGray(faces[i]);
        cv::resize(faceRoi, faceRoi, Size(250,250), 0, 0, CV_INTER_LINEAR);
        std::vector<cv::Rect> eyes;
        //detect face 找眼睛
        _eyesCascade.detectMultiScale(faceRoi, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(16, 16));
        //把眼睛位置畫出來
//        for (size_t j = 0; j < eyes.size(); j++)
//        {
//            cv::Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height *0.5);
//            int radius = round((eyes[j].width + eyes[j].height) * 0.25);
//            cv::circle(frame, center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
//        }

        Rect box = faces[i];
        box = box+Point(-box.width, -box.height*0.2);
        box = box+Size(box.width*2, box.height*8.5);
        //qDebug()<<videoFrame.cols<<videoFrame.rows;
        //qDebug()<<box.tl().x<<box.tl().y<<box.br().x<<box.tl().y;
        if(box.tl().x<0)
            box.x=0;
        if(box.tl().y<0)
            box.y=0;
        if(box.br().x > videoFrame.cols)
            box.width=videoFrame.cols - box.tl().x;
        if(box.br().y>videoFrame.rows)
            box.height=videoFrame.rows-box.tl().y;
        //qDebug()<<box.tl().x<<box.tl().y<<box.br().x<<box.tl().y;

        Mat sample = videoFrame(box); // ROI
        cv::resize(sample, sample, Size(64,144), CV_INTER_CUBIC);
        imshow("",sample);


        //計算HOG特徵
        hogDescriptor.compute(sample, feature);
        cv::Mat testSampleFeatureMat = cv::Mat(cv::Size(feature.size(), 1), CV_32FC1);
        for (int i = 0; i < feature.size(); i++)
            testSampleFeatureMat.ptr<float>(0)[i] = feature[i];

        //判斷
        if(svm.predict(testSampleFeatureMat, true)>0){
            rectangle(frame, box, Scalar(0, 255, 0),3);
            peopleNum++;
        }
        //qDebug()<<"people:"<<peopleNum;
        feature.clear();
    }
    QString face_number = QString::number(faces.size(), 10);
    ui->NumberF->setText("Number of faces:" + face_number);
    QString People_number = QString::number(peopleNum, 10);
    ui->NumberP->setText("Number of People:" + People_number);
    ui->Detect->setPixmap(QPixmap::fromImage(dialog->Mat2QImage(frame)).scaled(this->ui->Detect->size())); //顯示
}

void MainWindow::Recognizer(){
    QFileInfo file("model.xml");
    qDebug()<<"!!!!!!!!!!"<<file.exists();
    if(file.exists()==false)
        qDebug()<<"Please train model";
    else
        model->load("model.xml");
}

void MainWindow::updateModel(QString dir){
    dir_face = dir.toUtf8().constData();
    QDir dest;
    QStringList filter;
    filter<<"*.jpg";
    dest.setPath(dir);
    dest.setNameFilters(filter);
    QFileInfoList list = dest.entryInfoList();
    //qDebug() << "count!!";
    //qDebug() << list.count();
    for(int i=1;i<=list.count();i++){
        stringstream ss;
        ss << i;
        String s = ss.str();
        s = dir_face + "/" + s + ".jpg";
        images.push_back(imread(s, CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(j);
    }
    j++;
    qDebug()<<"j "<<j;
    model->train(images,labels);
    model->save("model.xml");
}

void MainWindow::updatePicture() {
    Mat QtVideoFrame;
    cap >> videoFrame; // get a new frame from camera
    QtVideoFrame=videoFrame.clone();
    if(videoFrame.empty())
        qDebug() << "video frame empty!!";
    detectAndDisplay(videoFrame);
    ui->Input->setPixmap(QPixmap::fromImage(dialog->Mat2QImage(QtVideoFrame)).scaled(this->ui->Input->size())); //顯示
}

void MainWindow::on_Open_clicked()
{
    cap = VideoCapture(0); // 開攝影機
    if(!cap.isOpened())
        qDebug() << "Could not open camera";
    else{
        timer = new QTimer(this);
        timer->setInterval(1000); // 設定每30ms觸發一次
        connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
        timer->start();
    }
}

void MainWindow::on_NewFace_clicked()
{
    dialog = new Dialog();
    dialog->getFrame(&cap);
    dialog->setWindowTitle(tr("dialog"));
    connect(dialog, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    dialog->show();
//    dialog->exec();
}

void MainWindow::receiveData(QString dir){
    updateModel(dir);
}

void MainWindow::on_Recognition_clicked()
{
    QFileInfo file("model.xml");
    if(file.exists()!=false){
        model->load("model.xml");
        int predicted = model->predict(faceRoi);
        qDebug() <<"pre"<< predicted;
        if(predicted<1){
            ui->Name->setText("Name: NaN");
        }
        else{
        QString face_name = QString::number(predicted, 10);
        ui->Name->setText("Name:" + face_name);
        }
    }
    else
        qDebug()<<"Please train model";
}
