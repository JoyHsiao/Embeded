#include "mainwindow.h"
#include "ui_mainwindow.h"

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

int MainWindow::findBiggestContour(std::vector<std::vector<Point> > contours){ //找最大contours
    int indexOfBiggestContour = -1;
    size_t sizeOfBiggestContour = 0;
    for (size_t i = 0; i < contours.size(); i++){
        if(contours[i].size() > sizeOfBiggestContour){
            sizeOfBiggestContour = contours[i].size();
            indexOfBiggestContour = i;
        }
    }
    return indexOfBiggestContour;
}
double MainWindow::findAngle(cv::Point p, cv::Point p1, cv::Point p2){ //判斷角度
    double dval = ((p1.x-p.x)*(p2.x-p.x)+(p1.y-p.y)*(p2.y-p.y))
    / (norm(Mat(p1), cv::Mat(p))*norm(Mat(p2), Mat(p)));
    return acos(dval)*180.0/3.1415926;
}

void MainWindow::on_Open_clicked()
{
    VideoCapture video(0); // 開攝影機
    if(!video.isOpened())
        qDebug() << "Could not open camera";

    Mat videoFrame;
    while(true){
        video >> videoFrame; // 讀Frame

        if(videoFrame.empty()){
            qDebug() << "video frame empty";
            break;
        }
        waitKey(100);
        ui->Camera->setPixmap(QPixmap::fromImage(Mat2QImage(videoFrame)).scaled(this->ui->Camera->size())); //顯示

        Mat camera_detect = videoFrame.clone();
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        Mat grayFrame, canny_output;
        int thresh =50;
        cvtColor(videoFrame, grayFrame, CV_RGB2GRAY);
        Canny(grayFrame, canny_output, thresh, thresh*3, 3);
        cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE); // 找輪廓
        for (std::size_t i = 0; i < contours.size(); i++) { // 畫輪廓
            cv::Scalar color = cv::Scalar(0, 255, 255);
            cv::drawContours(camera_detect, contours, i, color, 2, 8, hierarchy);
        }
        ui->Detect->setPixmap(QPixmap::fromImage(Mat2QImage(camera_detect)).scaled(this->ui->Detect->size()));
    }





//    int IndexOfBiggestContour = findBiggestContour(contours); // 找最大輪廓
//    std::vector<std::vector<int> >hull( contours.size() );
//    std::vector<std::vector<int> >hullsI( contours.size() );
//    std::vector<std::vector<Vec4i> >defects( contours.size() );
//    for( size_t i = 0; i < hull.size(); i++ ){
//        if (IndexOfBiggestContour == i){
//        convexHull( Mat(contours[i]), hull[i], false ); // 找凸包
//        convexityDefects(Mat(contours[i]),hull[i], defects[i]); // 找凹點
//        break;
//        }
//    }
//    std::vector<cv::Point> fingerTips;
//    std::vector<Vec4i>::iterator d = defects[IndexOfBiggestContour].begin();
//    bool hasFinger = false;
//    while( d!=defects[IndexOfBiggestContour].end() ) {
//        std::vector<cv::Point> contour = contours[IndexOfBiggestContour];
//        Vec4i& v=(*d);
//        int startidx=v[0];
//        int endidx=v[1];
//        Point ptStart( contour[startidx] ); // point of the contour where the defect begins
//        Point ptEnd( contour[endidx] ); // point of the contour where the defect ends
//        float distance = v[3] / 256; // distance between the farthest point and the convex hull
//        int maxIdx = -1;
//        double maxDist = 0;
//        if (distance >= 10)
//            hasFinger = true;
//        // Find longest point between starting point and end point
//        for (int j=startidx+1; j < endidx; j++){
//            cv::Point p = contour[j];
//            double d = cv::norm(p - ptStart) + cv::norm(p - ptEnd);
//            if (d > maxDist){
//                maxDist = d;
//                maxIdx = j;
//            }
//        }
//        // qualify tip by angle
//        if (maxIdx >= 0 && findAngle(contour[maxIdx], ptStart, ptEnd) < 90)
//            fingerTips.push_back(contour[maxIdx]);
//        d++;
//    }
}
