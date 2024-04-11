#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    computer = new Computer(this);

    //sets up ui
    ui->display->setCurrentIndex(0);
    ui->connectButton->setVisible(false);
    ui->disconnectButton->setVisible(false);
    ui->lowBatteryIcon->setVisible(false);

    //slots
    connect(ui->newSessionButton, SIGNAL(released()), this, SLOT(newSessionPressed()));
    connect(ui->sessionLogButton, SIGNAL(released()), this, SLOT(sessionLogPressed()));
    connect(ui->timeAndDateButton, SIGNAL(released()), this, SLOT(dateTimePressed()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(menuPressed()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(powerOff()));
    connect(ui->connectButton, SIGNAL(released()), this, SLOT(connectPressed()));
    connect(ui->disconnectButton, SIGNAL(released()), this, SLOT(disconnectPressed()));
    connect(ui->submitDateTimeButton, SIGNAL(released()), this, SLOT(submitDateTime()));
    connect(ui->pauseButton, SIGNAL(released()), this, SLOT(pause()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(stop()));
    connect(ui->playButton, SIGNAL(released()), this, SLOT(play()));

    //signals emitted from classes
    connect(computer, &Computer::displayBlueLight, this,&MainWindow::setBlueLight);
    connect(computer, &Computer::displayRedLight, this,&MainWindow::setRedLight);
    connect(computer, &Computer::displayGreenLight, this,&MainWindow::setGreenLight);
    connect(computer, &Computer::batteryIsLow, this,&MainWindow::displayLowBattery);
    connect(computer, &Computer::turnPowerOff, this,SLOT(powerOff()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete computer;
}

void MainWindow::newSessionPressed(){
    //updates ui
    ui->display->setCurrentIndex(1);
    ui->connectButton->setVisible(true);
    ui->pauseButton->setEnabled(true);
    ui->stopButton->setEnabled(true);


    computer->startSession();
}

void MainWindow::sessionLogPressed(){
    //updates ui
    ui->display->setCurrentIndex(2);
}

void MainWindow::dateTimePressed(){
    //updates ui
    ui->display->setCurrentIndex(3);
}

void MainWindow::menuPressed(){
    //updates ui
    ui->display->setCurrentIndex(0);
    ui->connectButton->setVisible(false);
    ui->disconnectButton->setVisible(false);
}

void MainWindow::powerOff(){
    //exits app
    QApplication::quit();
}

void MainWindow::connectPressed(){
    //updates ui
    ui->connectButton->setVisible(false);
    ui->disconnectButton->setVisible(true);

    computer->setConnected(true);
}

void MainWindow::disconnectPressed(){
    //updates ui
    ui->connectButton->setVisible(true);
    ui->disconnectButton->setVisible(false);

    computer->setConnected(false);
}

void MainWindow::submitDateTime(){
    //sets current date/time
    QDateTime dateTime = ui->dateTimeEdit->dateTime();
    QString dateString = dateTime.date().toString("yyyy-MM-dd");
    QString timeString = dateTime.time().toString("HH:mm");
    computer->setDateTime(dateString, timeString);

    //return to menu
    ui->display->setCurrentIndex(0);
}

void MainWindow::setRedLight(bool is_on){
    if(is_on){
        ui->contactLostLight->setStyleSheet("background-color: #FFC0CB");
    } else{
        ui->contactLostLight->setStyleSheet("background-color: DarkRed");
    }
}

void MainWindow::setBlueLight(bool is_on){
    if(is_on){
        ui->contactLight->setStyleSheet("background-color: LightBlue");
    } else{
        ui->contactLight->setStyleSheet("background-color: DarkBlue");
    }
}

void MainWindow::setGreenLight(bool is_on){
    if(is_on){
        ui->contactLight->setStyleSheet("background-color: LightGreen");
    } else{
        ui->contactLight->setStyleSheet("background-color: DarkGreen");
    }
}

void MainWindow::pause(){
    //updates ui
    ui->pauseButton->setEnabled(false);
    ui->playButton->setEnabled(true);

    computer->pause();
}

void MainWindow::stop(){
    //updates ui
    ui->pauseButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    computer->stop();
}

void MainWindow::play(){
    //updates ui
    ui->pauseButton->setEnabled(true);
    ui->playButton->setEnabled(false);

    computer->play();
}

void MainWindow::displayLowBattery(){
    ui->lowBatteryIcon->setVisible(true);
}
