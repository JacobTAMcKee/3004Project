#include "computer.h"
#include <QDebug>

Computer::Computer(QObject *parent) : QObject(parent){
}

void Computer::startSession(){
    eeg->run_session();
}

void Computer::setConnected(bool isConnected){
    //tell eeg connected = isConnected;
}

void pause(){
    //tell eeg session is paused
}

void play(){
    //tell eeg session playing
}

void stop(){
    //tell eeg session stopped
}

void Computer::endSession(){
    //add session to log

    //return to main window

}

void Computer::setDateTime(QString d, QString t){
    date = d;
    time = t;
}

//maybe these functions go in EEG class?
void Computer::greenLight(bool is_on){
    emit displayGreenLight(is_on);
}

void Computer::redLight(bool is_on){
    emit displayRedLight(is_on);
}

void Computer::blueLight(bool is_on){
    emit displayBlueLight(is_on);
}

void Computer::lowBattery(){
    emit batteryIsLow();
}

void Computer::powerOff(){
    emit turnPowerOff();
}
