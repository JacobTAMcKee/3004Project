#ifndef EEG_H
#define EEG_H
#include "Sensor.h"
#include "Waveform.h"
#include "WaveformFactory.h"
#include "math.h"
#include <vector>
#include "defs.h"
#include <QString>
#include <QtTypes>
#include <QElapsedTimer>
class EEG
{
private:
    //bool red_light;
    //bool green_light;
    //bool blue_light;
    //qint64 sessionTime;
    int battery;
    Sensor sensors[NUM_SENSORS];
    bool on;
    int baselines[NUM_SENSORS];
    WaveformFactory WaveformGenerator;



public:
   EEG EEG();
   // bool getGreen();
   // bool getBlue();
   // bool getRed();
   // void setGreen(bool is_on);
   // void setBlue(bool is_on);
   // void setRed(bool is_on);
   //int getSignal();
   double CalcDominantFrequency(Sensor s);
   void lowBattery();
   void run_treatment();
   void power_off();
   void power_on();
   //QString logger();
   //void EEG::connection(){
   void connection_lost();
   
};
#endif // EEG
