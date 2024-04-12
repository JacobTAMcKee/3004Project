#ifndef WaveformFactory_H
#define WaveformFactory_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <random>
#include "Waveform.h"

using namespace std;

class WaveformFactory {
    public:
        // Initialize Waveform Factory
        WaveformFactory();

        // Obtain a random double within the range (min, max)
        double randDouble(double min, double max);

        // Create and return a new Waveform
        Waveform generateWaveform();
};

#endif