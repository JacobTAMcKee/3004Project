#ifndef SENSOR_h
#define SENSOR_h

#include "WaveformFactory.h"

Class Sensor {
    public:
        Sensor(int electrodeLocationNumber, Waveform waveform);
        int getElectrodeLocationNumber();
        double getDominantFrequency();
        void setDominantFrequency(double domF);

    private:
        int electrodeLocationNumber;
        double dominantFrequency;
        Waveform waveform;

};
#endif // SENSOR
