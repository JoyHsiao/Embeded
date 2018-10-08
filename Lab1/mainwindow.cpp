#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimpleGPIO.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->mySlider,SIGNAL(valueChanged(int)),this,SLOT(showValue(int)));
    connect(ui->myLabel,SIGNAL(textChanged(QString)),this,SLOT(sliderValue(QString)));
    LedInit();

    myTimer = new QTimer(this);
    myTimer->start(1000);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(LedInitShine()));
}

void MainWindow::showValue(int val) // Editor change
{
    if(!ui->Start->isEnabled()){
        QString str = QString("%1").arg(val);
        ui->myLabel->setText(str);

        LedStart();
    }
    else{
        ui->myLabel->setText("0");
    }
}

void MainWindow::sliderValue(QString str) // slider change
{
    if(!ui->Start->isEnabled()){
        int value = str.toInt();

        if(value>3)
            ui->myLabel->setText("3");
        if(value<0)
            ui->myLabel->setText("0");
        ui->mySlider->setValue(value);

        LedStart();
    }
    else{
        ui->mySlider->setValue(0);
    }
}

MainWindow::~MainWindow()
{
    LedClose();
    delete ui;
}

void MainWindow::LedInit(){
    gpio_export(166);
    gpio_export(165);
    gpio_export(164);
    gpio_set_dir(166, OUTPUT_PIN);
    gpio_set_dir(165, OUTPUT_PIN);
    gpio_set_dir(164, OUTPUT_PIN);
}

void MainWindow::LedClose(){
    gpio_unexport(166);
    gpio_unexport(165);
    gpio_unexport(164);
}

void MainWindow::LedValue(){
    if(gpio_get_value(166)==1 && gpio_get_value(165)==1 && gpio_get_value(164)==1)
        LedOn=1;
    else
        LedOn=0;
}

void MainWindow::LedInitShine(){
    //LedValue();   // XD
    if(LedOn){
        LedChange(false, false, false);
        qDebug() << "close\n";
        LedOn=false;    // QQ
    }
    else{
        LedChange(true, true, true);
        qDebug() << "open\n";
        LedOn=true;    // QQ
    }
}

void MainWindow::LedChange(bool one, bool two, bool three){
    if(one)
        gpio_set_value(166, HIGH);
    else
        gpio_set_value(166, LOW);
    if(two)
        gpio_set_value(165, HIGH);
    else
        gpio_set_value(165, LOW);
    if(three)
        gpio_set_value(164, HIGH);
    else
        gpio_set_value(164, LOW);
}

void MainWindow::LedStart(){
    int SValue = ui->mySlider->value();
    switch(SValue){
        case 0:
            qDebug() <<"165 LOW, 164 LOW\n";
            //LedChange(true, false, false); XD
            qDebug()<< "100\n";
            break;
        case 1:
            qDebug() <<"165 HIGH, 164 LOW\n";
            //LedChange(true, false, true); XD
            qDebug()<< "101\n";
            break;
        case 2:
            qDebug() <<"165 LOW, 164 HIGH\n";
            //LedChange(true, true, false); XD
            qDebug()<< "110\n";
            break;
        case 3:
            qDebug() <<"165 HIGH, 164 HIGH\n";
            //LedChange(true, true, true); XD
            qDebug()<< "111\n";
            break;
    }
}

void MainWindow::on_Start_clicked()
{
    myTimer->stop();
    LedStart();
    ui->Start->setEnabled(false);
    ui->Stop->setEnabled(true);
    ui->Reset->setEnabled(true);
}

void MainWindow::on_Stop_clicked()
{
    LedChange(false, false, false);
    qDebug()<<"000\n";
    ui->Start->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->Reset->setEnabled(true);
}

void MainWindow::on_Reset_clicked()
{
    //LedChange(false, false, false);
    myTimer = new QTimer(this);
    myTimer->start(1000);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(LedInitShine()));

    ui->Start->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->mySlider->setValue(0);
    ui->myLabel->setText("0");
}
