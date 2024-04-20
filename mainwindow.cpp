#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add computer to its own thread
    QThread* computerThread = new QThread();
    computer = new Computer(nullptr);
    computer->moveToThread(computerThread);
    computerThread->start();

    // Connect signals and slots
    connect(computerThread, &QThread::started, computer, &Computer::start);
    connect(computerThread, &QThread::finished, computer, &Computer::deleteLater);

    //sets up ui
    ui->display->setCurrentIndex(0);
    ui->PCLog->setVisible(false);
    ui->backButton->setVisible(false);
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
    connect(ui->displayWaveformButton, SIGNAL(released()), this, SLOT(waveformPage()));
    connect(ui->openGraphButton, SIGNAL(released()), this, SLOT(openGraph()));
    connect(ui->deviceDisplayButton, SIGNAL(released()), this, SLOT(displayDeviceLog()));
    connect(ui->PCDisplayButton, SIGNAL(released()), this, SLOT(displayPCLog()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(displayLastLog()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(displayNextLog()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(sessionLogPressed()));

    //signals emitted from classes
    connect(computer, &Computer::displayBlueLight, this,&MainWindow::setBlueLight);
    connect(computer, &Computer::displayRedLight, this,&MainWindow::setRedLight);
    connect(computer, &Computer::displayGreenLight, this,&MainWindow::setGreenLight);
    connect(computer, &Computer::turnPowerOff, this,&MainWindow::powerOff);
    connect(computer, &Computer::displayTimer, this,&MainWindow::setTimer);
    connect(computer, &Computer::displayProgress, this,&MainWindow::setProgBar);
    connect(computer, &Computer::mainMenu, this, &MainWindow::menuPressed);
    connect(computer, &Computer::batteryIsLow, this, &MainWindow::displayLowBattery);
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

    computer->triggerSession();
}

void MainWindow::sessionLogPressed(){
    //updates ui
    ui->backButton->setVisible(false);
    ui->deviceDisplayButton->setVisible(true);
    ui->PCDisplayButton->setVisible(true);
    ui->sessionLog->setHtml("");
    ui->display->setCurrentIndex(2);
    ui->PCLog->setVisible(false);

    computer->setCurLogNum(0);
}

void MainWindow::dateTimePressed(){
    //updates ui
    ui->display->setCurrentIndex(3);
}

void MainWindow::menuPressed(){
    //stops treatment if happening
    if(ui->display->currentIndex() == 1){
      computer->stop();
    }
    //updates ui
    ui->display->setCurrentIndex(0);
    ui->connectButton->setVisible(false);
    ui->disconnectButton->setVisible(false);
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    setBlueLight(false);
    setRedLight(false);
    setGreenLight(false);

}

void MainWindow::powerOff(){
    //exits app
    QApplication::quit();
}

void MainWindow::connectPressed(){
    //updates ui
    ui->connectButton->setVisible(false);
    ui->disconnectButton->setVisible(true);
    setBlueLight(true);
    setRedLight(false);

    computer->setConnected(true);
}

void MainWindow::disconnectPressed(){
    //updates ui
    ui->connectButton->setVisible(true);
    ui->disconnectButton->setVisible(false);
    setRedLight(true);
    setBlueLight(false);

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
        ui->treatmentLight->setStyleSheet("background-color: LightGreen");
    } else{
        ui->treatmentLight->setStyleSheet("background-color: DarkGreen");
    }
}

void MainWindow::setTimer(int seconds){
    QString timeString = QString("<html><body style=\"font-size: 36pt; text-align: center;\">0:%1</body></html>").arg(seconds, 2, 10, QChar('0'));
    ui->timeDisplay->setHtml(timeString);
}

void MainWindow::setProgBar(int percentage){
  ui->progressBar->setValue(percentage);
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
    //updates ui
    ui->lowBatteryIcon->setVisible(true);
}

void MainWindow::waveformPage(){
    //updates ui
    ui->display->setCurrentIndex(4);
}

void MainWindow::openGraph(){
    int electrodeNum = ui->electrodeSpinBox->value();
    Sensor s = computer->getEEG()->getSensor(electrodeNum);
    double* yData = s.getYPlotData();
    plotWindow = new NewWindow();
    plotWindow->show();

    //ADD CODE HERE
}

void MainWindow::displayDeviceLog(){
    ui->PCDisplayButton->setVisible(false);
    ui->deviceDisplayButton->setVisible(false);
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    QString log = computer->getLog(false);
    QString logString = "<html><body style=\"font-size: 18pt; text-align: center; margin: auto;\">" + log + "</body></html>";
    ui->sessionLog->setHtml(logString);
}

void MainWindow::displayPCLog(){
    ui->PCLog->setHtml("<html><body style=\"font-size: 10pt; text-align: center; margin: auto;\">" + computer->getLog(true)+ "</body></html>");
    ui->PCLog->setVisible(true);
    ui->backButton->setVisible(true);
}

void MainWindow::displayLastLog(){
    computer->setCurLogNum(-1);
    displayDeviceLog();
}

void MainWindow::displayNextLog(){
    computer->setCurLogNum(1);
    displayDeviceLog();
}

