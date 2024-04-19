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
        Waveform();
        // Initialize Waveform with four amplitudes and frequencies -- these represent four different sine waves
        // in the form y = Asin(Bx) where A is an amplitude constant and B is a frequency constant
        Waveform(double a1, double a2, double a3, double a4, double f1, double f2, double f3, double f4);

        // Returns a single y value for the waveform for plotting
        double getValue(double x);

        // Returns one of the four amplitudes for dominant frequency calculation
        double getAmplitude(int index);

        // Returns one of the four frequencies for dominant frequency calculation
        double getFrequency(int index);

        //Adds offset value to each of the four frequencies
        void addFrequency(int offset);
        
    private:
        double amplitudes[4];
        double frequencies[4];
};

#endif
