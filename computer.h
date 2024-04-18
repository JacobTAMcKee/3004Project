#ifndef COMPUTER_H
#define COMPUTER_H
#include "EEG.h"
#include "defs.h"
#include <QObject>
#include <QElapsedTimer>
#include <QThread>

class Computer : public QObject {
    Q_OBJECT
public:
    Computer(QObject *parent);
    ~Computer();
    void startSession();
    void setConnected(bool isConnected);
    void setDateTime(QString d, QString t);
    void greenLight(bool is_on);
    void redLight(bool is_on);
    void blueLight(bool is_on);
    void lowBattery();
    void pause();
    void play();
    void stop();
    void powerOff();

private:
    QString date = "2024-01-01";
    QString time = "12:00";
    bool connected;
    bool playing;
    bool stopped;
    int currentSite;
    int secondsRemaining;
    EEG *eeg;
    QElapsedTimer pauseTime;
    QElapsedTimer disconnectTime;
    void endSession();
    void reset();
    void decreaseTimer();
    void increaseProgBar();
    bool ready();
    bool timerRanOut();

signals:
    void displayGreenLight(bool is_on);
    void displayTimer(int seconds);
    void displayProgress(int percentage);
    void displayBlueLight(bool is_on);
    void displayRedLight(bool is_on);
    void batteryIsLow();
    void turnPowerOff();
    void mainMenu();
};

#endif // COMPUTER_H
