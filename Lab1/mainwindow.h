#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLineEdit>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void LedInitShine();
public:
    explicit MainWindow(QWidget *parent = 0);
    void LedInit();
    void LedValue();
    void LedClose();
    void LedChange(bool one, bool two, bool three);
    void LedStart();
    ~MainWindow();

private slots:
    void on_Start_clicked();
    void on_Stop_clicked();
    void on_Reset_clicked();

    void showValue(int val);
    void sliderValue(QString str);

private:
    Ui::MainWindow *ui;
    QTimer *myTimer;
    bool LedOn;
    QSlider *mySlider;
    QLineEdit   *myLabel;
};

#endif // MAINWINDOW_H
