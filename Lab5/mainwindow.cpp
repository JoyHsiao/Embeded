#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"

#include <opencv2/ocl/ocl.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>

//正樣本數量
#define POSAMOUNT 735
//負樣本數量
#define NEGAMOUNT 1512
#define FEATUREAMOUNT 1764

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

//void MainWindow::HOG_SVM(Mat videoFrame){
//    char filepath[100];
//    //樣本大小
//    cv::Mat sample = cv::Mat(cv::Size(64, 64), CV_8UC1);
//    //***********訓練時請調成自己的需求************ 一般人物偵測是64X128
//    //這裡的window為(64, 64), block為(16, 16), block的stride為(8, 8), cell是8X8, 每个cell的直方圖是9
//    cv::HOGDescriptor hogDescriptor = cv::HOGDescriptor(cv::Size(64, 144), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
//    std::vector<float> feature;
//    //暫存feature
//    cv::Mat sampleFeatures = cv::Mat(cv::Size(FEATUREAMOUNT, POSAMOUNT + NEGAMOUNT),
//    CV_32FC1);
//    cv::Mat sampleLabels = cv::Mat(cv::Size(1, POSAMOUNT + NEGAMOUNT), CV_32FC1);
//    cv::SVM svm;
//    //訓練用參數
//    cv::SVMParams params;
//    params.kernel_type = cv::SVM::LINEAR;
//    params.svm_type = cv::SVM::C_SVC;
//    params.C = 1;
//    params.term_crit = cv::TermCriteria(CV_TERMCRIT_ITER, 100, 0.000001);
//    //for testing
//    cv::Mat testSampleFeatureMat = cv::Mat(cv::Size(FEATUREAMOUNT, 1), CV_32FC1);
////    //pos sample
////    std::cout << "Pos sample compute" << std::endl;
////    for (int index = 1; index < POSAMOUNT; index++) {
////        sprintf(filepath, "Samples\\totalPos\\pos (%d).jpg", index);
////        sample = cv::imread(filepath, 0);
////        //計算HOG特徵
////        hogDescriptor.compute(sample, feature);
////        for (int featureIndex = 0; featureIndex < FEATUREAMOUNT; featureIndex++)
////            sampleFeatures.ptr<float>(index)[featureIndex] = feature[featureIndex];
////        feature.clear();
////        //給正樣本Label
////        sampleLabels.ptr<float>(index)[0] = 1.0;
////    }
////    //neg sample
////    std::cout << "Neg sample compute" << std::endl;
////    for (int index = 1; index < NEGAMOUNT; index++){
////        sprintf(filepath, "Samples\\totalNeg\\neg (%d).jpg", index);
////        sample = cv::imread(filepath, 0);
////        //計算HOG特徵
////        hogDescriptor.compute(sample, feature);
////        for (int featureIndex = 0; featureIndex < FEATUREAMOUNT; featureIndex++)
////            sampleFeatures.ptr<float>(POSAMOUNT + index - 1)[featureIndex] =
////        feature[featureIndex];
////        feature.clear();
////        //給負樣本Label
////        sampleLabels.ptr<float>(POSAMOUNT + index - 1)[0] = -1.0;
////    }
////    std::cout << "Start training" << std::endl;
////    //訓練
////    svm.train(sampleFeatures, sampleLabels, cv::Mat(), cv::Mat(), params);
////    //儲存Model
////    svm.save("mouse.xml");

//    sample = videoFrame;
//    string modelpath = "people.xml";
//    FileStorage svm_fs(modelpath,FileStorage::READ);
//    std::cout<<"load";
//    if(svm_fs.isOpened()){
//        svm.load(modelpath.c_str());
//        std::cout<<"load OK!!!";
//    }
////    //testing sample
////    std::cout << "Testing Positive Sample" << std::endl;
////    for (int index = 1; index < POSAMOUNT; index++){
//////        sprintf(filepath, "Samples\\totalPos\\pos (%d).jpg", index);
//////        sample = cv::imread(filepath, 0);
////        //計算HOG特徵
////        hogDescriptor.compute(sample, feature);
////        cout<<"======";
////        for (int featureIndex = 0; featureIndex < FEATUREAMOUNT; featureIndex++)
////        testSampleFeatureMat.ptr<float>(0)[featureIndex] = feature[featureIndex];
////        feature.clear();
////        //判斷
////        std::cout << svm.predict(testSampleFeatureMat, true) << std::endl;
////    }
////    std::cout << "Testing Negative Sample" << std::endl;
////    for (int index = 1; index < NEGAMOUNT; index++){
//////        sprintf(filepath, "Samples\\totalNeg\\neg (%d).jpg", index);
//////        sample = cv::imread(filepath, 0);
////        //計算HOG特徵
////        hogDescriptor.compute(sample, feature);
////        for (int featureIndex = 0; featureIndex < FEATUREAMOUNT; featureIndex++)
////        testSampleFeatureMat.ptr<float>(0)[featureIndex] = feature[featureIndex];
////        //判斷結果
////        std::cout << svm.predict(testSampleFeatureMat, true) << std::endl;
////        feature.clear();
////    }
//}

QImage MainWindow::Mat2QImage(Mat &image)
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

void MainWindow::detectAndDisplay(cv::Mat frame)
{
    cv::CascadeClassifier _faceCascade;
    cv::CascadeClassifier _eyesCascade;
    //載入model
    _faceCascade.load("haarcascade_frontalface_alt_tree.xml");
    _eyesCascade.load("haarcascade_eye_tree_eyeglasses.xml");
    std::vector<cv::Rect> faces;
    cv::Mat frameGray,faceRoi;
    cv::cvtColor(frame, frameGray, CV_BGR2GRAY);
    // detect face 找人臉
    _faceCascade.detectMultiScale(frameGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(16, 16));
    qDebug() << faces.size();
    for (size_t i = 0; i < faces.size(); i++)
    {
        cv::rectangle(frame, faces[i], cv::Scalar(0, 128, 255), 3);
        Mat faceRoi = frameGray(faces[i]);
        std::vector<cv::Rect> eyes;
        //detect face 找眼睛
        _eyesCascade.detectMultiScale(faceRoi, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(16, 16));
        //把眼睛位置畫出來
        for (size_t j = 0; j < eyes.size(); j++)
        {
            cv::Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height *0.5);
            int radius = round((eyes[j].width + eyes[j].height) * 0.25);
            cv::circle(frame, center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
        }
    }
    QString face_number = QString::number(faces.size(), 10);
    ui->NumberF->setText("Number of faces:" + face_number);
    ui->Detect->setPixmap(QPixmap::fromImage(Mat2QImage(frame)).scaled(this->ui->Detect->size())); //顯示
}

void MainWindow::Recognizer(){
    Mat temp;
    vector<Mat> images;
    vector<Mat> faceRoi;
    vector<int> labels;
    // images for first person
    images.push_back(imread("corn/1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    images.push_back(imread("corn/1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
    labels.push_back(0);
    // images for second person
//    images.push_back(imread("joy/0.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(1);
//    images.push_back(imread("joy/1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(1);
    //opencv有提供三種方法。
    //有門檻值
    //Ptr<FaceRecognizer> model = createEigenFaceRecognizer(component, threshold);
    //無門檻值
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    //訓練
    model->train(images, labels);
    //儲存model
    model->save("model.xml");
    Mat img = imread("corn/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //測試
    //有參數。
    //predicted = model->predict(img, label, conf)
    //無參數。
    int predicted = model->predict(img);
    qDebug() << predicted;
}

void MainWindow::updatePicture() {
    Mat videoFrame;
    Mat QtVideoFrame;
    cap >> videoFrame; // get a new frame from camera
    QtVideoFrame=videoFrame.clone();

    if(videoFrame.empty())
        qDebug() << "video frame empty";
//    imshow("wiffs", videoFrame);
//    HOG_SVM(videoFrame); // Number of People
    detectAndDisplay(videoFrame);
    ui->Input->setPixmap(QPixmap::fromImage(Mat2QImage(QtVideoFrame)).scaled(this->ui->Input->size())); //顯示
}

void MainWindow::on_Open_clicked()
{
    cap = VideoCapture(0); // 開攝影機
    Recognizer();
    if(!cap.isOpened())
        qDebug() << "Could not open camera";
    else{
        timer = new QTimer(this);
        timer->setInterval(1000); // 設定每30ms觸發一次
        connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
        timer->start();
    }
}
