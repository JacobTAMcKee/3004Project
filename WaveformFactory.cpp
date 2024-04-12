#include "WaveformFactory.h"

WaveformFactory::WaveformFactory()
{
    srand(time(NULL));
}

double WaveformFactory::randDouble(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}

Waveform WaveformFactory::generateWaveform()
{
    double a1 = randDouble(0.0, 5.0);
    double a2 = randDouble(0.0, 5.0);
    double a3 = randDouble(0.0, 5.0);
    double a4 = randDouble(0.0, 5.0);
    double f1 = randDouble(8.0, 12.0); // Alpha Wave 8-12 Hz
    double f2 = randDouble(12.0, 30.0); // Beta wave 12-30 Hz
    double f3 = randDouble(1.0, 4.0); // Delta Wave 1-4 Hz
    double f4 = randDouble(4.0, 8.0); // Theta Wave 4-8 Hz
    Waveform w = Waveform(a1, a2, a3, a4, f1, f2, f3, f4);
    return w;
}
