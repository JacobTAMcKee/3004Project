#include "Sensor.h"

Sensor::Sensor(int electrodeLocationNumber, Waveform waveform) :
waveform(waveform) {
    this->electrodeLocationNumber = electrodeLocationNumber;
    // Wait for the EEG to calculate it
    dominantFrequency = 0.0;
    YPlotData = new double[3000];
}

Sensor::Sensor() {}

int Sensor::getElectrodeLocationNumber() {
    return this->electrodeLocationNumber;
}

double Sensor::getDominantFrequency() {
    return this->dominantFrequency;
}

Waveform Sensor::getWaveform() {
    return this->waveform;
}

double* Sensor::getYPlotData() {
    for (int i = 0; i < 3000; i++) {
        YPlotData[i] = waveform.getValue(i / 100.0f);
    }
    return YPlotData;
}

void Sensor::setDominantFrequency(double domF) {
    dominantFrequency = domF;
}
