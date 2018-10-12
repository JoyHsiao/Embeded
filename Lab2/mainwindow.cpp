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
    QString fileName = QFileDialog::getOpenFileName(ui->label_1, "Open Image","/home/ubuntu/Embeded/Lab2/Image", "Image Files (*.png *.bmp *.jpg)");
    //QString fileName = QFileDialog::getOpenFileName(ui->label_1, "Open Image","/home/joy_hsiao/Nvidea/TK1/106598009/Lab/Lab2/Image", "Image Files (*.png *.bmp *.jpg)");

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
    time_exec.start();
    equalizeHist(grayimg, eqhist);
    myShowImage = convertProcess(eqhist);
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
    time_exec.start();
    threshold(blurimg, otsu, str.toInt(), 255, THRESH_BINARY);

    myShowImage = convertProcess(otsu);
    ui->label_4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_4->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BlurButton_clicked()
{
    time_exec.start();
    blur(grayimg,blurimg, Size(3,3));

    myShowImage = convertProcess(blurimg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_MedianButton_clicked()
{
    time_exec.start();
    medianBlur(grayimg, blurimg, 5);

    myShowImage = convertProcess(blurimg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_GaussianButton_clicked()
{
    time_exec.start();
    GaussianBlur(grayimg, blurimg, Size(5,5), 0, 0);

    myShowImage = convertProcess(blurimg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BilateralButton_clicked()
{
    time_exec.start();
    bilateralFilter(grayimg, blurimg, 5, 30, 30);

    myShowImage = convertProcess(blurimg);
    ui->label_3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_3->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_OtsuButton_clicked()
{
    QString str = ui->lineEdit->text();
    time_exec.start();
    threshold(blurimg, otsu, str.toInt(), 255, THRESH_BINARY|THRESH_OTSU);

    myShowImage = convertProcess(otsu);
    ui->label_4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_4->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_DilateButton_clicked()
{
    time_exec.start();
    dilate(otsu,morphy,Mat());
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_ErodeButton_clicked()
{
    time_exec.start();
    erode(otsu,morphy,Mat());
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_OpenButton_clicked()
{
    time_exec.start();
    morphologyEx(otsu,morphy,MORPH_OPEN,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_CloseButton_clicked()
{
    time_exec.start();
    morphologyEx(otsu,morphy,MORPH_CLOSE,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_GradientButton_clicked()
{
    time_exec.start();
    morphologyEx(otsu,morphy,MORPH_GRADIENT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_TopHatButton_clicked()
{
    time_exec.start();
    morphologyEx(otsu,morphy,MORPH_TOPHAT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(morphy);
    ui->label_5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_5->size()));
    time = QString::number(time_exec.elapsed(),10);
    ui->TimeLabel->setText("execute time : " +time +" ms");
}

void MainWindow::on_BlackHatButton_clicked()
{
    time_exec.start();
    morphologyEx(otsu,morphy,MORPH_BLACKHAT,Mat(), Point(-1,-1), 2);
    myShowImage = convertProcess(morphy);
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
