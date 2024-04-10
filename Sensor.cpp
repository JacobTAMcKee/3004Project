#include "Sensor.h"

Sensor::Sensor(int electrodeLocationNumber, Waveform waveform) {
    this->electrodeLocation = electrodeLocationNumber;
    this->waveForm = waveForm;
    // Get the amplitude and frequency values from the waveform
    for (int i = 0; i < 4; ++i) {
        amplitudes[i] = waveform.getAmplitude(i);
        frequencies[i] = waveform.getFrequency(i);
    }
    // Wait for the EEG to calculate it
    this->dominantFrequency = 0.0;
}

int Sensor::getElectrodeLocationNumber() {
    return this->electrodeLocationNumber;
}

float Sensor::getAmplitute(int num) {
    return amplitudes[num];
}

float Sensor::getFrequency(int num) {
    return frequencies[num;]
}

double Sensor::getDominantFrequency() {
    return this->dominantFrequency;
}

void Sensor::setAmplitute(int num, float a) {
    amplitudes[num] = a;
}

void Sensor::setFrequency(int num, float f) {
    frequencies[num] = f;
}

void Sensor::setDominantFrequency(double domF) {
    dominantFrequency = domF;
}