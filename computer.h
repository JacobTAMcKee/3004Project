#ifndef COMPUTER_H
#define COMPUTER_H
#include "EEG.h"
#include "defs.h"
#include <QObject>
#include <QElapsedTimer>
#include <QThread>
#include <QFile>
#include <QTextStream>


class Computer : public QObject {
    Q_OBJECT
public:
    Computer(QObject *parent);
    ~Computer();
    void triggerSession();
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
    void setCurLogNum(int upDown);
    EEG* getEEG();
    QString getLog(bool fullVersion);

private:
    QString date = "2024-01-01";
    QString time = "12:00";
    bool connected=false;
    bool playing;
    bool stopped;
    int currentSite;
    int secondsRemaining;
    bool inTreatment = false;
    bool start_session = false;;
    EEG *eeg;
    QElapsedTimer pauseTime;
    QElapsedTimer disconnectTime;
    double before_bl;
    double after_bl;
    int curLogNum = 1;
    int numTreatments = 0;
    void endSession();
    void reset();
    void decreaseTimer();
    void increaseProgBar();
    bool ready();
    bool timerRanOut();
    void applyTreatment();
    void endTreatment();
    void startSession();

signals:
    void displayGreenLight(bool is_on);
    void displayTimer(int seconds);
    void displayProgress(int percentage);
    void displayBlueLight(bool is_on);
    void displayRedLight(bool is_on);
    void batteryIsLow();
    void turnPowerOff();
    void mainMenu();

public slots:
    void start();
};

#endif // COMPUTER_H
