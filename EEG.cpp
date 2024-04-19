#include "EEG.h"


   EEG::EEG(){
      this->WaveformGenerator = WaveformFactory();
      this->battery = 100;
      for(int i=0; i<NUM_SENSORS; i++){
        this->sensors[i] = Sensor(i, this->WaveformGenerator.generateWaveform()); //sensor constructor
      }
      this->on = false;
      for(int i=0; i<NUM_SENSORS; i++){
        this->dominant_frequency[i] = 0; 
      }
   }

   double EEG::CalcDominantFrequency(Sensor s){
       Waveform w = s.getWaveform();
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

   void EEG::setDominantFrequency(){
      for(int i=0; i<NUM_SENSORS; i++){
        this->dominant_frequency[i] = this->CalcDominantFrequency(this->sensors[i]); 
      }
   }

   void EEG::run_treatment(int pos){
      //add offset of 5 to each waveform in sensor
      this->sensors[pos].getWaveform().addFrequency(5);
      //update new dominant frequency value for sensor
      this->dominant_frequency[pos] = this->CalcDominantFrequency(sensors[pos]);
      this->battery -= 5;
   }

   //write getBaseline function that calculates the mean across all baseline values
   double EEG::getBaseline(){
      double avg = 0.0;  //or double for higher precision
      double sum = 0.0;
      for (int i = 0; i < NUM_SENSORS; i++)
      {
          sum += this->dominant_frequency[i];
      }
      avg = ((double)sum)/NUM_SENSORS;
      return avg;
   }

   void EEG::reset(){
      this->battery = 100;
      this->on = false;
      for(int i=0; i<NUM_SENSORS; i++){
        this->dominant_frequency[i] = 0; 
      }
   }

   void EEG::power_off(){
      this->on = false;
   }

   void EEG::power_on(){
      this->reset();
      this->on = true;
   }

   Sensor EEG::getSensor(int num){
       return sensors[num-1];
   }

   //Function should be triggerd in UI slot every 1 minute once connection lost button is clicked
   void EEG::connection_lost(){
      qDebug() << QString::fromStdString("Beep! Connection Lost") << "\n";
   }
