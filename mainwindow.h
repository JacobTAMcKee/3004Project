#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computer.h"

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
    void displayLowBattery();

private:
    Ui::MainWindow *ui;
    Computer *computer;

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
};
#endif // MAINWINDOW_H
