#include "computer.h"
#include <QDebug>

Computer::Computer(QObject *parent) : QObject(parent){
}

void Computer::startSession(){
    reset();
    eeg->power_on();
    //loops until all sites are complete or session is stopped
    while(currentSite < NUM_SENSORS){
      if(ready()){
        eeg->run_treatment(currentSite);
        greenLight(true);
        decreaseTimer();
        currentSite++;
        increaseProgBar();
      } else if(timerRanOut() || stopped){
        //session ended early
        break;
      }
    }
    if(currentSite == NUM_SENSORS){
      //session finished
      endSession();
    }
    emit mainMenu();
}

void Computer::setConnected(bool isConnected){
    connected = isConnected;
    if(!connected){
      eeg->connection_lost();
      disconnectTime.start();
    } else{
      disconnectTime.invalidate();
    }
}

void Computer::reset(){
    //resets variables for new session
    connected = false;
    playing = true;
    stopped = false;
    currentSite = 0;
    secondsRemaining = 21;
    disconnectTime.start();
    pauseTime.invalidate();
    emit displayTimer(21);
}

bool Computer::ready(){
  return(connected && playing && !stopped && !timerRanOut());
}

bool Computer::timerRanOut(){
  return ((pauseTime.isValid() && pauseTime.hasExpired(300000)) || (disconnectTime.isValid() && disconnectTime.hasExpired(300000)));
}

void Computer::decreaseTimer(){
  secondsRemaining--;
  emit displayTimer(secondsRemaining);
}

void Computer::increaseProgBar(){
  int percentage = (currentSite/NUM_SENSORS)*100;
  emit displayProgress(percentage);
}

void Computer::pause(){
    playing = false;
    pauseTime.start();
}

void Computer::play(){
    playing = true;
    pauseTime.invalidate();
}

void Computer::stop(){
    stopped = true;
}

void Computer::endSession(){
    //add session to log
    //info needed: time, date, before and after baselines (average of each site)

    
    eeg->power_off();
}

void Computer::setDateTime(QString d, QString t){
    date = d;
    time = t;
}

void Computer::greenLight(bool is_on){
    //flashes green light for one second
    emit displayGreenLight(true);
    QThread::sleep(1);
    emit displayGreenLight(false);
}

void Computer::redLight(bool is_on){
    emit displayRedLight(is_on);
}

void Computer::blueLight(bool is_on){
    emit displayBlueLight(is_on);
}

void Computer::lowBattery(){

}

void Computer::powerOff(){
    emit turnPowerOff();
}

EEG* Computer::getEEG(){
    return eeg;
}
