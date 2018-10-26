#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
    cvtColor(lImage, grayimg, CV_RGB2GRAY);

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
    Mat contoursImg = lImage.clone();

    cvtColor(lImage, grayimg, CV_RGB2GRAY);
    Canny( grayimg, canny_output, thresh, thresh*3, 3 );
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( 255, 0, 0 );
        drawContours( contoursImg, contours, idx, color, 2, 8, hierarchy );
    }

    myShowImage = convertProcess(contoursImg);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_circle_clicked()
{
    int thresh = 50;
    Mat canny_output;
    Mat contoursImg = lImage.clone();
    vector<Vec3f> circles;

    Canny( grayimg, canny_output, thresh, thresh*3, 3 );
    HoughCircles(canny_output, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100);

    for(size_t i=0; i<circles.size(); i++){
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(contoursImg, center, radius, Scalar(255,0,0), 3, 8, 0 );
    }

    myShowImage = convertProcess(contoursImg);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_triangle_clicked()
{
    //標籤起始值
    #define label_init 100

    cv::Mat contoursImg = lImage.clone();
    cv::Mat temp;
    cv::Mat object = cv::Mat::zeros(grayimg.rows, grayimg.cols, grayimg.type()); //連通物件結構的bounding box
    cv::Rect compRect[255];
    int label_num = label_init;
    //物件計數索引
    int comp_idx = 0;
    //物件弧度臨界值
    float ratio_thr1 = 0.56;
    float ratio_thr2 = 0.53;

    threshold(grayimg, temp, 0, 255, THRESH_BINARY);
    //將二值化影像複製到pObject空間
    object = temp.clone();
    //開始進行連通物件偵測並標籤化
    for (int i = 0; i < object.rows; i++) {
        for (int j = 0; j < object.cols; j++) {
            Scalar color = object.at<uchar>(Point(j, i));
            if (color.val[0] == 255) { //表示為前景物件像素
                //取得連通物件資料, 包含物件面積, 座標及寬高, 並給予指定標籤數值
                floodFill(object, Point(j, i), Scalar(label_num), &compRect[comp_idx]);
                label_num++;
                comp_idx++;
            }
        }
    }

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //由二值影像進行輪廓擷取, 並取得輪廓長度
    cv::findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    //計算物件特徵, 顯示物件面積, 輪廓長度以及弧度值
    for (int i = comp_idx - 1; i >= 0; i--)
    {
        float parameter = arcLength(contours[i], true);
        //物體弧度：e = 4π(面積)/(周長)2
        float tempR = 4 * CV_PI * contourArea(contours[i]) / (parameter * parameter);
        //ratio[i] = 4 * CV_PI * contourArea(contours[i]) / (parameter * parameter);
        std::cout<< tempR <<std::endl;
        //若第i物件弧度值介於1.0至0.79之間，則可能為正方
        if (tempR < ratio_thr1 && tempR > ratio_thr2){
            cv::Scalar color = cv::Scalar(255, 0, 0);
            cv::drawContours(contoursImg, contours, i, color, 2, 8, hierarchy);
        }
    }
    myShowImage = convertProcess(contoursImg);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_rectangle_clicked()
{
    //標籤起始值
    #define label_init 100

    cv::Mat contoursImg = lImage.clone();
    cv::Mat temp;
    cv::Mat object = cv::Mat::zeros(grayimg.rows, grayimg.cols, grayimg.type()); //連通物件結構的bounding box
    cv::Rect compRect[255];
    int label_num = label_init;
    //物件計數索引
    int comp_idx = 0;
    //物件弧度臨界值
    float ratio_thr1 = 0.80;
    float ratio_thr2 = 0.77;

    threshold(grayimg, temp, 0, 255, THRESH_BINARY);
    //將二值化影像複製到pObject空間
    object = temp.clone();
    //開始進行連通物件偵測並標籤化
    for (int i = 0; i < object.rows; i++) {
        for (int j = 0; j < object.cols; j++) {
            Scalar color = object.at<uchar>(Point(j, i));
            if (color.val[0] == 255) { //表示為前景物件像素
                //取得連通物件資料, 包含物件面積, 座標及寬高, 並給予指定標籤數值
                floodFill(object, Point(j, i), Scalar(label_num), &compRect[comp_idx]);
                label_num++;
                comp_idx++;
            }
        }
    }

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //由二值影像進行輪廓擷取, 並取得輪廓長度
    cv::findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    //計算物件特徵, 顯示物件面積, 輪廓長度以及弧度值
    for (int i = comp_idx - 1; i >= 0; i--)
    {
        float parameter = arcLength(contours[i], true);
        //物體弧度：e = 4π(面積)/(周長)2
        float tempR = 4 * CV_PI * contourArea(contours[i]) / (parameter * parameter);
        //ratio[i] = 4 * CV_PI * contourArea(contours[i]) / (parameter * parameter);
        //若第i物件弧度值介於1.0至0.79之間，則可能為正方
        if (tempR < ratio_thr1 && tempR > ratio_thr2){
            cv::Scalar color = cv::Scalar(255, 0, 0);
            cv::drawContours(contoursImg, contours, i, color, 2, 8, hierarchy);
        }
    }
    myShowImage = convertProcess(contoursImg);
    ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
}

void MainWindow::on_surf_clicked()
{
    //標籤起始值
    #define label_init 100

    cv::Mat contoursImg = lImage.clone();
    cv::Mat temp;
    cv::Mat object = cv::Mat::zeros(grayimg.rows, grayimg.cols, grayimg.type()); //連通物件結構的bounding box
    cv::Rect compRect[255];
    int label_num = label_init;
    //物件計數索引
    int comp_idx = 0;

    threshold(grayimg, temp, 0, 255, THRESH_BINARY);
    //將二值化影像複製到pObject空間
    object = temp.clone();
    //開始進行連通物件偵測並標籤化
    for (int i = 0; i < object.rows; i++) {
        for (int j = 0; j < object.cols; j++) {
            Scalar color = object.at<uchar>(Point(j, i));
            if (color.val[0] == 255) { //表示為前景物件像素
                //取得連通物件資料, 包含物件面積, 座標及寬高, 並給予指定標籤數值
                floodFill(object, Point(j, i), Scalar(label_num), &compRect[comp_idx]);
                label_num++;
                comp_idx++;
            }
        }
    }

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    Mat srcROI;
    //vector<Point> bound; // minX, minY, MaxX, MaxY
    int minX, minY, MaxX, MaxY;
    int X,Y;
    //由二值影像進行輪廓擷取, 並取得輪廓長度
    cv::findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    //計算物件bounding box and 座標
    for (int i = comp_idx - 1; i >= 0; i--){
    //for (int i = 4; i >= 4; i--){
        qDebug()<< i;
        minX=INT_MAX, minY=INT_MAX, MaxX=INT_MIN, MaxY=INT_MIN;
        for(size_t j = 0; j<contours[i].size(); j++){
            //qDebug() <<" ("<< contours[i][j].x<<","<<contours[i][j].y<<")";
            X = contours[i][j].x;
            Y = contours[i][j].y;

            if(minX > X)
                minX = X;
            if(minY > Y)
                minY = Y;
            if(MaxX < X)
                MaxX = X;
            if(MaxY < Y)
                MaxY = Y;
        }
        // setting ROI by bounding box
        srcROI = contoursImg(cvRect(minX,minY,MaxX-minX,MaxY-minY));

        qDebug()<< minX<< " "<< minY<< " "<<  MaxX<< " "<< MaxY;

        int minHessian = 100;

        SurfFeatureDetector detector( minHessian );
        vector<cv::KeyPoint> keypoints_object, keypoints_scene;
        detector.detect( srcROI, keypoints_object );
        detector.detect( rImage, keypoints_scene );

        SurfDescriptorExtractor extractor;
        Mat descriptors_object, descriptors_scene;
        extractor.compute( srcROI, keypoints_object, descriptors_object );
        extractor.compute( rImage, keypoints_scene, descriptors_scene );

        FlannBasedMatcher matcher;
        std::vector< DMatch > matches;
        matcher.match( descriptors_object, descriptors_scene, matches );

        double max_dist = 0; double min_dist = 100;

        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < descriptors_object.rows; i++ ){
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }

        qDebug()<< " -- Max dist :"<< max_dist;
        qDebug()<< " -- Min dist :"<< min_dist <<endl;

        //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
        std::vector< DMatch > good_matches;

        for( int i = 0; i < descriptors_object.rows; i++ ){
            if( matches[i].distance < 3*min_dist ){
                good_matches.push_back( matches[i]);
            }
        }

        Mat img_matches;
        drawMatches(srcROI, keypoints_object, rImage, keypoints_scene, good_matches, img_matches,
                    Scalar::all(-1),Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

        //-- Localize the object
        std::vector<Point2f> obj;
        std::vector<Point2f> scene;

        for( size_t i = 0; i < good_matches.size(); i++ ){
            //-- Get the keypoints from the good matches
            obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
            scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
        }

        if(good_matches.size()>5){
            rectangle(contoursImg, Rect(minX,minY,MaxX-minX,MaxY-minY), Scalar(0, 255, 0),2);
            qDebug()<<"~~~~~~~~~~~~~~~~~~~";
            myShowImage = convertProcess(contoursImg);
            ui->target->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->target->size()));
        }

// x,y verify point for draw image
//        Point p(minX, minY);
//        circle(contoursImg, p, 2, Scalar(0, 255, 0));
//        Point a(MaxX, MaxY);
//        circle(contoursImg, a, 2, Scalar(0, 255, 0));
//        qDebug()<< minX << " "<< minY<< " "<< MaxX<< " "<< MaxY<<endl;
    }



// opencv Official website Surf sample program
//    int minHessian = 100;
//    //Ptr<SurfFeatureDetector> detector = SurfFeatureDetector::create(minHessian);

//    SurfFeatureDetector detector( minHessian );
//    vector<cv::KeyPoint> keypoints_object, keypoints_scene;
//    detector.detect( lImage, keypoints_object );
//    detector.detect( rImage, keypoints_scene );

//    SurfDescriptorExtractor extractor;
//    Mat descriptors_object, descriptors_scene;
//    extractor.compute( lImage, keypoints_object, descriptors_object );
//    extractor.compute( rImage, keypoints_scene, descriptors_scene );

//    Mat dstImage1, dstImage2;
////    detector->detectAndCompute(lImage, Mat(), key_points_1, dstImage1);
////    detector->detectAndCompute(rImage, Mat(), key_points_2, dstImage2);//可以分成detect和compute

//    FlannBasedMatcher matcher;
//    std::vector< DMatch > matches;
//    matcher.match( descriptors_object, descriptors_scene, matches );

//    double max_dist = 0; double min_dist = 100;

//    //-- Quick calculation of max and min distances between keypoints
//    for( int i = 0; i < descriptors_object.rows; i++ )
//    { double dist = matches[i].distance;
//      if( dist < min_dist ) min_dist = dist;
//      if( dist > max_dist ) max_dist = dist;
//    }

//    printf("-- Max dist : %f \n", max_dist );
//    printf("-- Min dist : %f \n", min_dist );

//    //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
//    std::vector< DMatch > good_matches;

//    for( int i = 0; i < descriptors_object.rows; i++ )
//    { if( matches[i].distance < 3*min_dist )
//       { good_matches.push_back( matches[i]); }
//    }

//    Mat img_matches;
//    drawMatches( lImage, keypoints_object, rImage, keypoints_scene,
//                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
//                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

//    //-- Localize the object
//    std::vector<Point2f> obj;
//    std::vector<Point2f> scene;

//    for( int i = 0; i < good_matches.size(); i++ )
//    {
//      //-- Get the keypoints from the good matches
//      obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
//      scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
//    }

//    Mat H = findHomography( obj, scene, CV_RANSAC );

//    //-- Get the corners from the image_1 ( the object to be "detected" )
//    std::vector<Point2f> obj_corners(4);
//    obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( lImage.cols, 0 );
//    obj_corners[2] = cvPoint( lImage.cols, lImage.rows ); obj_corners[3] = cvPoint( 0, lImage.rows );
//    std::vector<Point2f> scene_corners(4);

//    perspectiveTransform( obj_corners, scene_corners, H);

//    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
//    line( img_matches, scene_corners[0] + Point2f( lImage.cols, 0), scene_corners[1] + Point2f( lImage.cols, 0), Scalar(0, 255, 0), 4 );
//    line( img_matches, scene_corners[1] + Point2f( lImage.cols, 0), scene_corners[2] + Point2f( lImage.cols, 0), Scalar( 0, 255, 0), 4 );
//    line( img_matches, scene_corners[2] + Point2f( lImage.cols, 0), scene_corners[3] + Point2f( lImage.cols, 0), Scalar( 0, 255, 0), 4 );
//    line( img_matches, scene_corners[3] + Point2f( lImage.cols, 0), scene_corners[0] + Point2f( lImage.cols, 0), Scalar( 0, 255, 0), 4 );

//    myShowImage = convertProcess(img_matches);
//    ui->temp->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->temp->size()));
}
