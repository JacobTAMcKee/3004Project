#include "Waveform.h"

Waveform::Waveform(double a1, double a2, double a3, double a4, double f1, double f2, double f3, double f4)
{
    amplitudes[0] = a1;
    amplitudes[1] = a2;
    amplitudes[2] = a3;
    amplitudes[3] = a4;
    frequencies[0] = f1;
    frequencies[1] = f2;
    frequencies[2] = f3;
    frequencies[3] = f4;
}

double Waveform::getValue(double x)
{
    return (getAmplitude(1) * sin(getFrequency(1) * x)) + (getAmplitude(2) * sin(getFrequency(2) * x)) +
    (getAmplitude(3) * sin(getFrequency(3) * x)) + (getAmplitude(4) * sin(getFrequency(4) * x));
}

double Waveform::getAmplitude(int index)
{
    if (index > 4 || index < 1) {
        cout << "Invalid index: " << index << ". Requires an index 1-4." << endl;
        return 0.0;
    }
    return amplitudes[index-1];
}

double Waveform::getFrequency(int index)
{
    if (index > 4 || index < 1) {
        cout << "Invalid index: " << index << ". Requires an index 1-4." << endl;
        return 0.0;
    }
    return frequencies[index-1];
}

void Waveform::addFrequency(int offset)
{
    for(int i = 0; i < 4; i++){
        frequencies[i] += offset;
    }
}
