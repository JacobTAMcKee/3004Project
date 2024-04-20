#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computer.h"
#include "newwindow.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setRedLight(bool is_on);
    void setGreenLight(bool is_on);
    void setBlueLight(bool is_on);
    void setTimer(int seconds);
    void setProgBar(int percentage);
    void displayLowBattery();

private:
    NewWindow* plotWindow;
    Ui::MainWindow *ui;
    Computer *computer;
    int logPage = 1;

private slots:
    void newSessionPressed();
    void sessionLogPressed();
    void dateTimePressed();
    void menuPressed();
    void powerOff();
    void connectPressed();
    void disconnectPressed();
    void submitDateTime();
    void pause();
    void stop();
    void play();
    void waveformPage();
    void openGraph();
    void displayDeviceLog();
    void displayPCLog();
    void displayLastLog();
    void displayNextLog();
};
#endif // MAINWINDOW_H
