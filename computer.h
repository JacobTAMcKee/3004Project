#ifndef COMPUTER_H
#define COMPUTER_H
#include "EEG.h"
#include <QObject>


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
    EEG *eeg;
    void endSession();

signals:
    void displayGreenLight(bool is_on);
    void displayBlueLight(bool is_on);
    void displayRedLight(bool is_on);
    void batteryIsLow();
    void turnPowerOff();
};

#endif // COMPUTER_H
