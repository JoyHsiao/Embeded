#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;

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

void MainWindow::on_OpenImageButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileName(ui->label_1, "Open Image","/home/ubuntu/Lab2/Image", "Image Files (*.png *.bmp *.jpg)");
    QString fileName = QFileDialog::getOpenFileName(ui->label_1, "Open Image","/home/joy_hsiao/Nvidea/TK1/106598009/Lab/Lab2/Image", "Image Files (*.png *.bmp *.jpg)");

    if(fileName.isEmpty())
        return;

    image = cv::imread(fileName.toLocal8Bit().data());
    cvtColor(image, grayimg, CV_RGB2GRAY);
    myShowImage = convertProcess(image);
    ui->label_1->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_1->size()));
}


QImage MainWindow::convertProcess(cv::Mat converImage)
{
    if(converImage.type() == CV_8UC1){
        return QImage((unsigned char * )converImage.data, converImage.cols, converImage.rows, converImage.step, QImage::Format_Indexed8);
    }
    else{
        cvtColor(converImage, converImage, CV_BGR2RGB);
        return QImage((unsigned char * )converImage.data, converImage.cols, converImage.rows, converImage.step, QImage::Format_RGB888);
    }
}

void MainWindow::on_GrayButton_clicked()
{
    time_exec.start();
    myShowImage = convertProcess(grayimg);
    ui->label_2->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_2->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_EqHistButton_clicked()
{
    cv::Mat histImg;
    time_exec.start();
    equalizeHist(grayimg, histImg);
    myShowImage = convertProcess(histImg);
    ui->label_2->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_2->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_lineEdit_textChanged(const QString &str)
{
    int value = str.toInt();
    if(value > 255)
        ui->lineEdit->setText("255");
    if(value < 0)
        ui->lineEdit->setText("0");
}

void MainWindow::on_ThresholdButton_clicked()
{
    QString str = ui->lineEdit->text();
    cv::Mat thresholdImg;
    time_exec.start();
    threshold(grayimg, thresholdImg, str.toInt(), 255, THRESH_BINARY);

    myShowImage = convertProcess(thresholdImg);
    ui->label_4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_4->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BlurButton_clicked()
{
    cv::Mat blurImg;
    time_exec.start();
    blur(grayimg,blurImg, Size(3,3));

    myShowImage = convertProcess(blurImg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_MedianButton_clicked()
{
    cv::Mat medianImg;
    time_exec.start();
    medianBlur(grayimg, medianImg, 5);

    myShowImage = convertProcess(medianImg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_GaussianButton_clicked()
{
    cv::Mat gaussianImg;
    time_exec.start();
    GaussianBlur(grayimg, gaussianImg, Size(5,5), 0, 0);

    myShowImage = convertProcess(gaussianImg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BilateralButton_clicked()
{
    cv::Mat bilateralImg;
    time_exec.start();
    bilateralFilter(grayimg, bilateralImg, 5, 30, 30);

    myShowImage = convertProcess(bilateralImg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_OtsuButton_clicked()
{
    QString str = ui->lineEdit->text();
    cv::Mat thresholdImg;
    time_exec.start();
    threshold(grayimg, thresholdImg, str.toInt(), 255, THRESH_BINARY|THRESH_OTSU);

    myShowImage = convertProcess(thresholdImg);
    ui->label_4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_4->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_DilateButton_clicked()
{
    cv::Mat dilateImg;
    time_exec.start();
    dilate(grayimg,dilateImg,Mat());
    myShowImage = convertProcess(dilateImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_ErodeButton_clicked()
{
    cv::Mat erodeImg;
    time_exec.start();
    erode(grayimg,erodeImg,Mat());
    myShowImage = convertProcess(erodeImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_OpenButton_clicked()
{
    cv::Mat openImg;
    time_exec.start();
    morphologyEx(grayimg,openImg,MORPH_OPEN,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(openImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_CloseButton_clicked()
{
    cv::Mat closeImg;
    time_exec.start();
    morphologyEx(grayimg,closeImg,MORPH_CLOSE,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(closeImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_GradientButton_clicked()
{
    cv::Mat gradientImg;
    time_exec.start();
    morphologyEx(grayimg,gradientImg,MORPH_GRADIENT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(gradientImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_TopHatButton_clicked()
{
    cv::Mat tophatImg;
    time_exec.start();
    morphologyEx(grayimg,tophatImg,MORPH_TOPHAT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(tophatImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BlackHatButton_clicked()
{
    cv::Mat blackhatImg;
    time_exec.start();
    morphologyEx(grayimg,blackhatImg,MORPH_BLACKHAT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(blackhatImg);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_ClearButton_clicked()
{
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
}
