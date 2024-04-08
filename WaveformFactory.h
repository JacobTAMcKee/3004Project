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

        Waveform generateWaveform(); // Create and return a new Waveform
};

#endif