#ifndef EEG_H
#define EEG_H
#include "Sensor.h"
#include "Waveform.h"
#include "WaveformFactory.h"
#include "math.h"
#include <vector>
#include <QString>
#include <QtTypes>
#include <QElapsedTimer>
class EEG
{
private:
    bool red_light;
    bool green_light;
    bool blue_light;
    qint64 sessionTime;
    int battery;
    Sensor sensors[21];
    bool on;
    int baselines[21];
    QElapsedTimer timer;
    WaveformFactory WaveformGenerator;



public:
   EEG EEG();
   bool getGreen();
   bool getBlue();
   bool getRed();
   void setGreen(bool is_on);
   void setBlue(bool is_on);
   void setRed(bool is_on);
   int getSignal();
   double CalcDominantFrequency(Sensor s);
   QString lowBattery();
   void run_session();
   void updateSessionTime()
   void power_off();
   void power_on();
   QString logger();
   void EEG::connection(){
   QString connection_lost();
   
};
#endif // EEG
