#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QTime>
#include <QString>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage convertProcess(cv::Mat converImage);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenImageButton_clicked();

    void on_GrayButton_clicked();

    void on_EqHistButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_ThresholdButton_clicked();

    void on_BlurButton_clicked();

    void on_MedianButton_clicked();

    void on_GaussianButton_clicked();

    void on_BilateralButton_clicked();

    void on_OtsuButton_clicked();

    void on_DilateButton_clicked();

    void on_ErodeButton_clicked();

    void on_OpenButton_clicked();

    void on_CloseButton_clicked();

    void on_GradientButton_clicked();

    void on_TopHatButton_clicked();

    void on_BlackHatButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
    cv::Mat grayimg;
    QImage myShowImage;
    QTime time_exec;
    QString time;
};

#endif // MAINWINDOW_H
