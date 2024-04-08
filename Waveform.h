#ifndef Waveform_H
#define Waveform_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;

class Waveform {
    public:
        // Initialize Waveform with four amplitudes and frequencies -- these represent the four sine waves we will sum
        Waveform(float a1, float a2, float a3, float a4, float f1, float f2, float f3, float f4);

        float getValue(float x); // For plotting
        float getAmplitude(int num); // For dominant calculation
        float getFrequency(int num); // For dominant calculation
        
    private:
        float amplitudes[4];
        float frequencies[4];
};

#endif