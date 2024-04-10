#ifndef SENSOR_h
#define SENSOR_h

#include "WaveformFactory.h"

Class Sensor {
    public:
        Sensor(int electrodeLocationNumber, Waveform waveform);
        int getElectrodeLocationNumber();
        float getAmplitute(int num);
        float getFrequency(int num);
        double getDominantFrequency();
        void setAmplitute(int num, float a);
        void setFrequency(int num, float f);
        void setDominantFrequency(double domF);

    private:
        int electrodeLocationNumber;
        float amplitudes[4];
        float frequencies[4];
        double dominantFrequency;
        Waveform waveform;

};
#endif // SENSOR