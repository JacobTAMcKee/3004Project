#ifndef SENSOR_h
#define SENSOR_h

#include "WaveformFactory.h"

class Sensor {

    public:
        Sensor();
        Sensor(int electrodeLocationNumber, Waveform waveform);
        int getElectrodeLocationNumber();
        Waveform getWaveform();
        double* getYPlotData();

    private:
        int electrodeLocationNumber;
        Waveform waveform;
        double* YPlotData;

};
#endif // SENSOR
