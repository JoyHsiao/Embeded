/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *OpenImageButton;
    QPushButton *GrayButton;
    QPushButton *ClearButton;
    QPushButton *EqHistButton;
    QPushButton *CloseAppButton;
    QPushButton *BlurButton;
    QPushButton *ThresholdButton;
    QPushButton *MedianButton;
    QPushButton *OtsuButton;
    QPushButton *GaussianButton;
    QPushButton *BilateralButton;
    QLineEdit *lineEdit;
    QPushButton *CloseButton;
    QPushButton *ErodeButton;
    QPushButton *OpenButton;
    QPushButton *DilateButton;
    QPushButton *TopHatButton;
    QPushButton *GradientButton;
    QPushButton *BlackHatButton;
    QLabel *TimeLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(791, 561);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(40, 10, 161, 141));
        label_1->setFrameShape(QFrame::Panel);
        label_1->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 180, 161, 141));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 10, 161, 141));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(300, 180, 161, 141));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(570, 10, 161, 141));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        OpenImageButton = new QPushButton(centralWidget);
        OpenImageButton->setObjectName(QStringLiteral("OpenImageButton"));
        OpenImageButton->setGeometry(QRect(10, 330, 99, 27));
        QFont font;
        font.setPointSize(9);
        OpenImageButton->setFont(font);
        GrayButton = new QPushButton(centralWidget);
        GrayButton->setObjectName(QStringLiteral("GrayButton"));
        GrayButton->setGeometry(QRect(120, 330, 99, 27));
        GrayButton->setFont(font);
        ClearButton = new QPushButton(centralWidget);
        ClearButton->setObjectName(QStringLiteral("ClearButton"));
        ClearButton->setGeometry(QRect(10, 360, 99, 27));
        ClearButton->setFont(font);
        EqHistButton = new QPushButton(centralWidget);
        EqHistButton->setObjectName(QStringLiteral("EqHistButton"));
        EqHistButton->setGeometry(QRect(120, 360, 99, 27));
        EqHistButton->setFont(font);
        CloseAppButton = new QPushButton(centralWidget);
        CloseAppButton->setObjectName(QStringLiteral("CloseAppButton"));
        CloseAppButton->setGeometry(QRect(10, 390, 99, 27));
        CloseAppButton->setFont(font);
        BlurButton = new QPushButton(centralWidget);
        BlurButton->setObjectName(QStringLiteral("BlurButton"));
        BlurButton->setGeometry(QRect(260, 330, 99, 27));
        BlurButton->setFont(font);
        ThresholdButton = new QPushButton(centralWidget);
        ThresholdButton->setObjectName(QStringLiteral("ThresholdButton"));
        ThresholdButton->setGeometry(QRect(370, 330, 99, 27));
        ThresholdButton->setFont(font);
        MedianButton = new QPushButton(centralWidget);
        MedianButton->setObjectName(QStringLiteral("MedianButton"));
        MedianButton->setGeometry(QRect(260, 360, 99, 27));
        MedianButton->setFont(font);
        OtsuButton = new QPushButton(centralWidget);
        OtsuButton->setObjectName(QStringLiteral("OtsuButton"));
        OtsuButton->setGeometry(QRect(370, 360, 99, 27));
        OtsuButton->setFont(font);
        GaussianButton = new QPushButton(centralWidget);
        GaussianButton->setObjectName(QStringLiteral("GaussianButton"));
        GaussianButton->setGeometry(QRect(260, 390, 99, 27));
        GaussianButton->setFont(font);
        BilateralButton = new QPushButton(centralWidget);
        BilateralButton->setObjectName(QStringLiteral("BilateralButton"));
        BilateralButton->setGeometry(QRect(260, 420, 99, 27));
        BilateralButton->setFont(font);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(480, 330, 41, 27));
        CloseButton = new QPushButton(centralWidget);
        CloseButton->setObjectName(QStringLiteral("CloseButton"));
        CloseButton->setGeometry(QRect(550, 420, 99, 27));
        CloseButton->setFont(font);
        ErodeButton = new QPushButton(centralWidget);
        ErodeButton->setObjectName(QStringLiteral("ErodeButton"));
        ErodeButton->setGeometry(QRect(550, 360, 99, 27));
        ErodeButton->setFont(font);
        OpenButton = new QPushButton(centralWidget);
        OpenButton->setObjectName(QStringLiteral("OpenButton"));
        OpenButton->setGeometry(QRect(550, 390, 99, 27));
        OpenButton->setFont(font);
        DilateButton = new QPushButton(centralWidget);
        DilateButton->setObjectName(QStringLiteral("DilateButton"));
        DilateButton->setGeometry(QRect(550, 330, 99, 27));
        DilateButton->setFont(font);
        TopHatButton = new QPushButton(centralWidget);
        TopHatButton->setObjectName(QStringLiteral("TopHatButton"));
        TopHatButton->setGeometry(QRect(660, 360, 99, 27));
        TopHatButton->setFont(font);
        GradientButton = new QPushButton(centralWidget);
        GradientButton->setObjectName(QStringLiteral("GradientButton"));
        GradientButton->setGeometry(QRect(660, 330, 99, 27));
        GradientButton->setFont(font);
        BlackHatButton = new QPushButton(centralWidget);
        BlackHatButton->setObjectName(QStringLiteral("BlackHatButton"));
        BlackHatButton->setGeometry(QRect(660, 390, 99, 27));
        BlackHatButton->setFont(font);
        TimeLabel = new QLabel(centralWidget);
        TimeLabel->setObjectName(QStringLiteral("TimeLabel"));
        TimeLabel->setGeometry(QRect(490, 460, 201, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 791, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(CloseAppButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_1->setText(QApplication::translate("MainWindow", "Original Image", 0));
        label_2->setText(QApplication::translate("MainWindow", "Gray Image", 0));
        label_3->setText(QApplication::translate("MainWindow", "Denoise Image", 0));
        label_4->setText(QApplication::translate("MainWindow", "Threshlod Image", 0));
        label_5->setText(QApplication::translate("MainWindow", "Morphology Image", 0));
        OpenImageButton->setText(QApplication::translate("MainWindow", "Open Image", 0));
        GrayButton->setText(QApplication::translate("MainWindow", "Gray", 0));
        ClearButton->setText(QApplication::translate("MainWindow", "Clear Processing", 0));
        EqHistButton->setText(QApplication::translate("MainWindow", "EqHist", 0));
        CloseAppButton->setText(QApplication::translate("MainWindow", "Close App", 0));
        BlurButton->setText(QApplication::translate("MainWindow", "Blur", 0));
        ThresholdButton->setText(QApplication::translate("MainWindow", "Threshold", 0));
        MedianButton->setText(QApplication::translate("MainWindow", "Median Blur", 0));
        OtsuButton->setText(QApplication::translate("MainWindow", "Threshold(otsu)", 0));
        GaussianButton->setText(QApplication::translate("MainWindow", "Gaussian Blur", 0));
        BilateralButton->setText(QApplication::translate("MainWindow", "Bilateral Blur", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "128", 0));
        CloseButton->setText(QApplication::translate("MainWindow", "Closing", 0));
        ErodeButton->setText(QApplication::translate("MainWindow", "Erode", 0));
        OpenButton->setText(QApplication::translate("MainWindow", "Open", 0));
        DilateButton->setText(QApplication::translate("MainWindow", "Dilate", 0));
        TopHatButton->setText(QApplication::translate("MainWindow", "TopHat", 0));
        GradientButton->setText(QApplication::translate("MainWindow", "Gradient", 0));
        BlackHatButton->setText(QApplication::translate("MainWindow", "BlackHat", 0));
        TimeLabel->setText(QApplication::translate("MainWindow", "ExecuteTime:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
