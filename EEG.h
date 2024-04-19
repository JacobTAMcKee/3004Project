#ifndef EEG_H
#define EEG_H
#include "Sensor.h"
#include "WaveformFactory.h"
#include "math.h"
#include "defs.h"
#include <QString>
#include <QtTypes>
#include "QtCore/qdebug.h"
#include <QElapsedTimer>
class EEG
{
private:

    int battery;
    Sensor sensors[NUM_SENSORS];
    bool on;
    double dominant_frequency[NUM_SENSORS];
    WaveformFactory WaveformGenerator;



public:
   EEG();
   double CalcDominantFrequency(Sensor s);
   void run_treatment(int pos);
   void reset();
   double getBaseline();
   void setDominantFrequency();
   void power_off();
   void power_on();
   Sensor getSensor(int num);
   QString connection_lost();
   
};
#endif // EEG
