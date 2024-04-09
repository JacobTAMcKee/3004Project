#ifndef EEG_H
#define EEG_H
#include "Sensor.h"
#include "Waveform.h"
#include "math.h"
#include <vector>
#include <QString>
#include <QTimer>
class EEG
{
private:
    bool red_light;
    bool green_light;
    bool blue_light;
    double dominant_frequency;
    int battery;
    Sensor sensors[21];
    bool on;
    int baselines[21];
    QTimer timer;



public:
   EEG EEG();
   bool getGreen();
   bool getBlue();
   bool getRed();
   void setGreen(bool is_on);
   void setBlue(bool is_on);
   void setRed(bool is_on);
   int getSignal();
   double CalcDominantFrequency(Waveform w);
   QString lowBattery();
   void run_session();
   QString power_off();
   QString connection_lost();
   
};
#endif // EEG