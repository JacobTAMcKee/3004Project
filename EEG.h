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

    int battery;
    Sensor sensors[NUM_SENSORS];
    bool on;
    int dominant_frequency[NUM_SENSORS];
    WaveformFactory WaveformGenerator;



public:
   EEG();
   double CalcDominantFrequency(Sensor s);
   void run_treatment();
   void reset();
   double getBaseline();
   void setDominantFrequency();
   void power_off();
   void power_on();
   Sensor getSensor(int num);
   QString connection_lost();
   
};
#endif // EEG
