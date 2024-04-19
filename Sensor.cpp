#include "Sensor.h"

Sensor::Sensor() {}

Sensor::Sensor(int electrodeLocationNumber, Waveform waveform) :
waveform(waveform) {
    this->electrodeLocationNumber = electrodeLocationNumber;
    // Wait for the EEG to calculate it
    YPlotData = new double[3000];
}

int Sensor::getElectrodeLocationNumber() {
    return this->electrodeLocationNumber;
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

