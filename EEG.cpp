#include "EEG.h"


   EEG::EEG(){
      this->WaveformGenerator = WaveformFactory()
      this->battery = 100;
      for(int i=0; i<NUM_SENSORS; i++){
        this->sensors[i] = Sensor(i, this->WaveformGenerator.generateWaveform()); //sensor constructor
      }
      this->on = false;
      for(int i=0; i<NUM_SENSORS; i++){
        this->baseline[i] = 0; 
      }
   }

   double EEG::CalcDominantFrequency(Sensor s){
       w = s.getWaveForm();
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

   void EEG::lowBattery(){
      this->red_light() = true;
      if(this->battery < 10){
         qDebug() << QString::fromStdString("Low Battery: Battery at 10%") << "\n";
      }
      if(this->battery < 5){
         qDebug() << QString::fromStdString("Battery critically low. Powering off") << "\n";
         this->power_off();
      }

   }

   void EEG::setBaselines(){
      this->setBlue(true);
      for(int i=0; i<NUM_SENSORS; i++){
        this->baseline[i] = this->CalcDominantFrequency(this->sensors[i]); 
      }
   }

   void EEG::run_treatment(int pos){
      this->baseline[pos] = this->baseline[pos]+5;
      this->sensors[pos]->setDominantFrequency(this->baseline[pos]);
      this->baseline[pos] = this->CalcDominantFrequency(sensors[pos])
      
   }

   void EEG::power_off(){
      this->on = false;
   }

   void EEG::power_on(){
      this->on = true;
   }

   //Function should be triggerd in UI slot every 1 minute once connection lost button is clicked
   QString EEG::connection_lost(){
      qDebug() << QString::fromStdString("Beep! Connection Lost") << "\n";
   }
