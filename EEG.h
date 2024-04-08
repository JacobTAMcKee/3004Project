#ifndef EEG_H
#define EEG_H
#include "Sensor.h"
 #include <QString>
#include <vector>
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
    Qtimer timer;



public:
   EEG EEG();
   int getGreen();
   int getBlue();
   int getRed();
   void setGreen();
   void setBlue();
   void setRed();
   int getSignal();
   double CalcDominantFrequency;
   QString lowBattery();
   void run_session();
   QString power_off();
   QString connection_lost();
   
};
#endif // EEG