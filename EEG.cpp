#include "EEG.h"


   EEG::EEG(){
      //Initially all lights are off 
      this->red_light = false;
      this->green_light = false;
      this->blue_light = false;
      this->dominant_frequency = 0.0;
      //Battery is fully charged
      this->battery = 100;
      for(int i=0; i<21; i++){
        this->sensors[i] = Sensor(); //sensor constructor, change later if necessary
      }
      this->on = false;
      for(int i=0; i<21; i++){
        this->baseline[i] = 0; //sensor constructor, change later if necessary
      }
      this->timer = new QTimer(this);
      this->timer.setInterval(msec);

   }
   bool EEG::getGreen(){
      return this->green_light;
   }
   bool EEG::getBlue(){
      return this->blue_light;
   }
   bool EEG::getRed(){
      return this->red_light;
   }
   void EEG::setGreen(bool is_on){
      this->green_light = is_on;
   }
   void EEG::setBlue(bool is_on){
      this->blue_light = is_on;
   }
   void EEG::setRed(bool is_on){
      this->red_light = is_on;
   }
   int EEG::getSignal(){
      return this->dominant_frequency;
   }
   double EEG::CalcDominantFrequency(Waveform w){
       double f1 = w.getFrequency(1);
       double f2 = w.getFrequency(2);
       double f3 = w.getFrequency(3);
       double f4 = w.getFrequency(4);

       double a1 = w.getAmplitude(1);
       double a2 = w.getAmplitude(2);
       double a3 = w.getAmplitude(3);
       double a4 = w.getAmplitude(4);

       return (((f1*pow(a1, 2)) + (f2*pow(a2, 2)) + (f3*pow(a3, 2)) + f4*pow(a4, 2))/
       (pow(a1, 2) + pow(a2, 2) + pow(a3, 2) + pow(a4, 2)));
   }

   QString EEG::lowBattery(){

   }

   void EEG::run_session();
   QString EEG::power_off();
   QString EEG::connection_lost();
   




/*
    bool red_light;
    bool green_light;
    bool blue_light;
    double dominant_frequency;
    int battery;
    Sensor sensors[21];
    bool on;
    int baselines[21];
    Qtimer timer;

*/ 