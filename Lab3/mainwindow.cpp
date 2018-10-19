#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

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

QImage MainWindow::convertProcess(cv::Mat converImage)
{
    if(converImage.type() == CV_8UC1){
        return QImage((unsigned char * )converImage.data, converImage.cols, converImage.rows, converImage.step, QImage::Format_Indexed8);
    }
    else{
        //cvtColor(converImage, converImage, CV_BGR2RGB);
        return QImage((unsigned char * )converImage.data, converImage.cols, converImage.rows, converImage.step, QImage::Format_RGB888);
    }
}

void MainWindow::on_openTarget_clicked()
{
    Mat image;
    QString fileName = QFileDialog::getOpenFileName(ui->target, "Open Image","/home/ubuntu/Embeded/Lab3/Pro3_Image", "Image Files (*.png *.bmp *.jpg)");
    //QString fileName = QFileDialog::getOpenFileName(ui->target, "Open Image","/home/joy_hsiao/Nvidea/TK1/106598009/Lab/Lab3/Pro3_Image", "Image Files (*.png *.bmp *.jpg)");

    if(fileName.isEmpty())
        return;

    image = imread(fileName.toLocal8Bit().data());
    cv::resize(image, lImage, Size(400,300), 0, 0, CV_INTER_LINEAR);

    myShowImage = convertProcess(lImage);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_openTemp_clicked()
{
    Mat image;
    QString fileName = QFileDialog::getOpenFileName(ui->temp, "Open Image","/home/ubuntu/Embeded/Lab3/Pro3_Image", "Image Files (*.png *.bmp *.jpg)");
    //QString fileName = QFileDialog::getOpenFileName(ui->target, "Open Image","/home/joy_hsiao/Nvidea/TK1/106598009/Lab/Lab3/Pro3_Image", "Image Files (*.png *.bmp *.jpg)");

    if(fileName.isEmpty())
        return;

    image = imread(fileName.toLocal8Bit().data());
    cv::resize(image, rImage, Size(400,300), 0, 0, CV_INTER_LINEAR);

    myShowImage = convertProcess(rImage);
    ui->temp->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->temp->size()));
}

void MainWindow::on_countors_clicked()
{
    int thresh = 50;
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor(lImage, grayimg, CV_RGB2GRAY);
    Canny( grayimg, canny_output, thresh, thresh*3, 3 );
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( 255, 0, 0 );
        drawContours( lImage, contours, idx, color, 2, 8, hierarchy );
    }

    myShowImage = convertProcess(lImage);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_circle_clicked()
{
    int thresh = 50;
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor(lImage, grayimg, CV_RGB2GRAY);

    for(int i=0; i<grayimg.rows; i++){
        for(int j=0; j<grayimg.cols; j++){
            Scalar color = grayimg.at<uchar>(Point(j,i));
            if(color.val[0] ==255){
                floodFill(grayimg, Point(j,i), Scalar(label_num, &compRect[com_idx]));
                label_num++;
                com_idx++;
            }
        }

    }

    Canny( grayimg, canny_output, thresh, thresh*3, 3 );
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

//    vector<vector<Point> > contours_poly(contours.size());
    for (int i = 0; i<contours.size(); i++)
    {
//        approxPolyDP(Mat(contours[i]), contours_poly[i], 2, true);
//        Scalar color( 255, 0, 0 );
//        drawContours( lImage, contours_poly, i, color, 2, 8);
    }

    myShowImage = convertProcess(lImage);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}
