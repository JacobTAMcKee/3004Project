#ifndef SENSOR_h
#define SENSOR_h

#include "WaveformFactory.h"

class Sensor {

    public:
        Sensor(int electrodeLocationNumber, Waveform waveform);
        int getElectrodeLocationNumber();
        double getDominantFrequency();
        Waveform getWaveform();
        void setDominantFrequency(double domF);
        double* getYPlotData();

    private:
        int electrodeLocationNumber;
        double dominantFrequency;
        Waveform waveform;
        double* YPlotData;
        int size;

};
#endif // SENSOR
