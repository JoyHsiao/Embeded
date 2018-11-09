#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"

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

void MainWindow::detection(Mat src) {
    //重新調整圖片大小
    Mat bgrToRgbImg, inputImg;
    cv::resize(src, inputImg, Size(src.cols * 3 / 8, src.rows * 3 / 8));
    picNum++;



    if (picNum == 1) { //第一次初始化
        extractionImg = Mat::zeros(inputImg.rows, inputImg.cols, inputImg.type());
        bgrToRgbImg = Mat::zeros(inputImg.rows, inputImg.cols, inputImg.type());
        palmImg = Mat::zeros(inputImg.rows, inputImg.cols, inputImg.type());
        outputImg = Mat::zeros(inputImg.rows, inputImg.cols, inputImg.type());
    }
    else {
        cvtColor(inputImg, bgrToRgbImg, CV_BGR2YCrCb);
    //---------------------YCrCb-----------------------
        Vec3b bgrToRgbImgVec3b, extractionImgVec3b;
        for (int i = 0; i < inputImg.rows; i++) {
            for (int j = 0; j < inputImg.cols; j++) {
                bgrToRgbImgVec3b = bgrToRgbImg.at<Vec3b>(i, j);
                extractionImgVec3b = extractionImg.at<Vec3b>(i, j);
                double sky; // Skin Y
                double skcr; // Skin cr
                double skcb; // Skin cb
                sky = bgrToRgbImgVec3b.val[0];
                skcr = bgrToRgbImgVec3b.val[1];
                skcb = bgrToRgbImgVec3b.val[2];

                //if (sky >= 70 && sky <= 255 && skcr >= 133 && skcr <= 180 && skcb >= 77 && skcb <= 135) {
                if (sky >= 70 && sky <= 255 && skcr >= 134 && skcr <= 160 && skcb >= 80 && skcb <= 128) {
                    //顏色是皮膚色
                    extractionImgVec3b.val[0] = 255;
                    extractionImgVec3b.val[1] = 255;
                    extractionImgVec3b.val[2] = 255;
                } else {
                    //顏色不是皮膚色
                    extractionImgVec3b.val[0] = 0;
                    extractionImgVec3b.val[1] = 0;
                    extractionImgVec3b.val[2] = 0;
                }
                extractionImg.at<Vec3b>(i, j) = extractionImgVec3b; //set the (i,j) pixel value
            }
        }

        //膨脹與侵蝕- palmImg把手指去掉------------------
        erode(extractionImg, extractionImg, Mat(), Point(-1, -1), 1);
        dilate(extractionImg, extractionImg, Mat(), Point(-1, -1), 2);
        erode(extractionImg, extractionImg, Mat(), Point(-1, -1), 1);
        dilate(extractionImg, extractionImg, Mat(), Point(-1, -1), 1);
        erode(extractionImg, extractionImg, Mat(), Point(-1, -1), 1);
        extractionImg.copyTo(palmImg);
        extractionImg.copyTo(outputImg);
        //把outputImg減去palmImg –就會剩下手指-----------------------
        erode(palmImg, palmImg, Mat(), Point(-1, -1), 9);
        dilate(palmImg, palmImg, Mat(), Point(-1, -1), 10);
        dilate(outputImg, outputImg, Mat(), Point(-1, -1), 1);
        //subtract(outputImg, palmImg, outputImg);
        QImage showOutputImg = Mat2QImage(outputImg);
        QImage showOutputImg1 = Mat2QImage(palmImg);
        ui->_label->setPixmap(QPixmap::fromImage(showOutputImg));
        ui->_label2->setPixmap(QPixmap::fromImage(showOutputImg1));
        subtract(outputImg, palmImg, outputImg);
        QImage showOutputImg2 = Mat2QImage(outputImg);
        ui->_label3->setPixmap(QPixmap::fromImage(showOutputImg2));
        //cvtColor(extractionImg, outputImg, CV_YCrCb2BGR);
        countConnected(outputImg); //去數手指的數目

    }
}

void MainWindow::countConnected(Mat img) {
    vector<Rect> comps;
    Scalar color;
    Mat temp;

//    cvtColor(extractionImg, outputImg, CV_YCrCb2BGR);
    cvtColor(img, temp, CV_BGR2GRAY);

    for (int i = 0; i < temp.rows; i++) {
        for (int j = 0; j < temp.cols; j++) {
            color = temp.at<uchar>(i, j);
            if (color.val[0] == 255) {
                //qDebug()<< "("<< i<<", "<<j<<")";
                Rect rect;
                floodFill(temp, Point(j, i), Scalar(comps.size()), &rect);
                comps.push_back(rect);
            }
        }
    }
    vector<vector<Point> > contours;

//    QImage showOutputImg3 = Mat2QImage(temp);
//    ui->_label4->setPixmap(QPixmap::fromImage(showOutputImg3));


    findContours(temp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    std::vector<cv::Vec4i> hierarchy;
    for (std::size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(temp, contours, i, color, 2, 8, hierarchy);
    }
//    ui->_label4->setPixmap(QPixmap::fromImage(Mat2QImage(temp)).scaled(this->ui->_label4->size()));

    int fingerNum = 0;
    //qDebug()<<"======"<<contours.size();
    for (int i = 0; i < contours.size(); i++) {
    //calculate area
        int area = contourArea(contours[i]);
    //門檻值,判斷是否是手指
        qDebug()<< "area="<<area;
        if (area > 200) {
            fingerNum++;
            qDebug()<<area;
        }
    }
    //cout << "fingerNum= " << fingerNum << endl;
    switch (fingerNum) //決定有幾個手指
    {
    case 0:
        ui->label_3->setText("Gesture : NaN");
        break;
    case 1:
        ui->label_3->setText("Gesture : 1");
        break;
    case 2:
        ui->label_3->setText("Gesture : 2");
        break;
    case 3:
        ui->label_3->setText("Gesture : 3");
        break;
    case 4:
        ui->label_3->setText("Gesture : 4");
        break;
    case 5:
        ui->label_3->setText("Gesture : 5");
        break;
    }
}

//void MainWindow::subtract(outputImg, palmImg, outputImg) {
//}

void MainWindow::updatePicture() {
    Mat videoFrame;
    Mat QtVideoFrame;

    cap >> videoFrame; // get a new frame from camera
    QtVideoFrame=videoFrame.clone();

    if(videoFrame.empty())
        qDebug() << "video frame empty";
    //imshow("wiffs", videoFrame);
    detection(videoFrame);
    ui->Camera->setPixmap(QPixmap::fromImage(Mat2QImage(QtVideoFrame)).scaled(this->ui->Camera->size())); //顯示

    Mat grayImg, canny_output;
    int thresh =30;
    cvtColor(extractionImg, outputImg, CV_YCrCb2BGR);
        cvtColor(outputImg, grayImg, CV_BGR2GRAY);
        Canny( grayImg, canny_output, thresh, thresh*3, 3 );
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE); // 找輪廓
        for (std::size_t i = 0; i < contours.size(); i++) { // 畫輪廓
            cv::Scalar color = cv::Scalar(0, 255, 255);
            cv::drawContours(outputImg, contours, i, color, 2, 8, hierarchy);
        }
        ui->Detect->setPixmap(QPixmap::fromImage(Mat2QImage(outputImg)).scaled(this->ui->Detect->size()));

}

void MainWindow::on_Open_clicked()
{
    cap = VideoCapture(0); // 開攝影機
    if(!cap.isOpened())
        qDebug() << "Could not open camera";
    else{
        timer = new QTimer(this);
        timer->setInterval(200); // 設定每30ms觸發一次
        connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
        timer->start();

        //VImage = videoFrame.clone();







//        int IndexOfBiggestContour = findBiggestContour(contours); // 找最大輪廓
//        std::vector<std::vector<int> >hull( contours.size() );
//        std::vector<std::vector<int> >hullsI( contours.size() );
//        std::vector<std::vector<Vec4i> >defects( contours.size() );
//        for( size_t i = 0; i < hull.size(); i++ ){
//            if (IndexOfBiggestContour == i){
//            convexHull( Mat(contours[i]), hull[i], false ); // 找凸包
//            convexityDefects(Mat(contours[i]),hull[i], defects[i]); // 找凹點
//            break;
//            }
//        }

//        std::vector<cv::Point> fingerTips;
//        std::vector<Vec4i>::iterator d = defects[IndexOfBiggestContour].begin();
//        bool hasFinger = false;
//        while( d!=defects[IndexOfBiggestContour].end() ) {
//            std::vector<cv::Point> contour = contours[IndexOfBiggestContour];
//            Vec4i& v=(*d);
//            int startidx=v[0];
//            int endidx=v[1];
//            Point ptStart( contour[startidx] ); // point of the contour where the defect begins
//            Point ptEnd( contour[endidx] ); // point of the contour where the defect ends
//            float distance = v[3] / 256; // distance between the farthest point and the convex hull
//            int maxIdx = -1;
//            double maxDist = 0;
//            if (distance >= 10)
//                hasFinger = true;
//            // Find longest point between starting point and end point
//            for (int j=startidx+1; j < endidx; j++){
//                cv::Point p = contour[j];
//                double d = cv::norm(p - ptStart) + cv::norm(p - ptEnd);
//                if (d > maxDist){
//                    maxDist = d;
//                    maxIdx = j;
//                }
//            }
//            // qualify tip by angle
//            if (maxIdx >= 0 && findAngle(contour[maxIdx], ptStart, ptEnd) < 90)
//                fingerTips.push_back(contour[maxIdx]);
//            d++;
//        }


//        ui->Detect->setPixmap(QPixmap::fromImage(Mat2QImage(camera_detect)).scaled(this->ui->Detect->size()));
    }



}
