#include "Sensor.h"

Sensor::Sensor(int electrodeLocationNumber, Waveform waveform) {
    this->electrodeLocation = electrodeLocationNumber;
    this->waveForm = waveForm;
    // Wait for the EEG to calculate it
    this->dominantFrequency = 0.0;
}

int Sensor::getElectrodeLocationNumber() {
    return this->electrodeLocationNumber;
}

double Sensor::getDominantFrequency() {
    return this->dominantFrequency;
}

void Sensor::setDominantFrequency(double domF) {
    dominantFrequency = domF;
}
