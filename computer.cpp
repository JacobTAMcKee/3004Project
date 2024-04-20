#include "computer.h"
#include <QDebug>
#include <QTimer>
#include <thread>

Computer::Computer(QObject *parent) : QObject(parent) {
    eeg = new EEG();
}

void Computer::startSession(){
    reset();
    eeg->power_on();
    before_bl = eeg->getBaseline();
    int count = 1;
    while(currentSite<=NUM_ROUNDS){
        if(ready()){
            if(currentSite==NUM_ROUNDS){
                //rounds complete
                if(count%6 ==1){
                    qDebug()<<"Final analysis...";
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                decreaseTimer();
                if(count%6==5){
                    emit displayProgress(100);
                    break;
                }
            }
            else if(count%6==1){
                qDebug()<<"Starting round"<<(currentSite+1)<<"of therapy:";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                decreaseTimer();
            }else if(count%6==2){
                qDebug()<<"Calculating dominant frequency...";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                decreaseTimer();
            } else if(count%6 ==0){
                qDebug()<<"Applying treatment.";
                applyTreatment();
                std::this_thread::sleep_for(std::chrono::seconds(1));
                endTreatment();
                qDebug()<<"Round"<<(currentSite)<<"complete.";
            } else{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                decreaseTimer();
            }
            count++;
        }else if(timerRanOut() || stopped){
            qDebug()<<"Session ended early.";
            start_session = false;
            connected = false;
            eeg->power_off();
            emit displayTimer(21);
            emit displayProgress(0);
            emit mainMenu();
            break;
        }
    }
    if(!stopped){
      //session complete
      after_bl = eeg->getBaseline();
      endSession();
    }
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
    playing = true;
    stopped = false;
    currentSite = 0;
    secondsRemaining = 29;
    disconnectTime.start();
    pauseTime.invalidate();
}

bool Computer::ready(){
   if(!connected){
       qDebug() << "Beep! Connect to continue session";
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }else if(!playing){
       qDebug() << "Beep! Press play to continue session";
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }
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
  int percentage = (currentSite*(100)/(NUM_ROUNDS+1));
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
    stopped =true;
}

void Computer::endSession(){
    //uncomment this to clear log history
    /*
    QFile mfile("data.txt");
    mfile.open(QIODevice::WriteOnly | QIODevice::Truncate);
        // Write an empty string to clear the file
        mfile.write("");
        mfile.close();
    */

    qDebug()<<"Session Complete.";
    //add session to log
    QFile file("data.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream fout(&file);
        fout << "date:" << date << ", time:" << time
             << ", before baseline:" << before_bl << ", after baseline:" << after_bl << "\n";
        file.close();
    } else {
        qDebug() << "Error opening file for append:" << file.errorString();
    }

    start_session = false;
    connected = false;
    eeg->power_off();
    emit mainMenu();
    emit displayTimer(29);
    emit displayProgress(0);
}

void Computer::setDateTime(QString d, QString t){
    date = d;
    time = t;
}

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

EEG* Computer::getEEG(){
    return eeg;
}

Computer::~Computer(){
    delete eeg;
}

void Computer::applyTreatment(){
    greenLight(true);
    eeg->run_treatment(currentSite);

}

void Computer::endTreatment(){
    decreaseTimer();
    currentSite++;
    increaseProgBar();
    greenLight(false);
}

//continuously loops until new session is started
void Computer::start(){
    while(true){
        if(start_session){
            numTreatments++;
            if(numTreatments == 2){
                qDebug() << "Low battery (10%)";
                lowBattery();
            }else if(numTreatments ==3){
                qDebug() << "Critically low battery (5%)";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                powerOff();
            }
            qDebug() << "Starting session...";
            startSession();
        }
    }
}


void Computer::triggerSession(){
    start_session = true;
}

QString Computer::getLog(bool fullVersion){
    QFile file("data.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString log;
    if(fullVersion){
        log = in.readAll();
        file.close();
        log.replace("date", "<br>date");
        return log;
    } else{
        int lineNum = 0;
        while (!in.atEnd() && lineNum < curLogNum) {
            log = in.readLine();
            lineNum++;
        }
        if(in.atEnd()){
            curLogNum = lineNum -1;
        }
        file.close();

        return (log.mid(0,log.indexOf(", before")).replace(",", "<br>"));
    }
}

void Computer::setCurLogNum(int upDown){
    if(upDown == 0){
        curLogNum =1;
    } else if(upDown == 1){
        curLogNum++;
    } else if(upDown == -1 && curLogNum > 1){
        curLogNum--;
    }
}
