#include "EEG.h"


   EEG::EEG(){
      //Initially all lights are off 
      this->red_light = false;
      this->green_light = false;
      this->blue_light = false;
      this->dominant_frequency = 0.0;
      this->WaveformGenerator = WaveformFactory()
      //Battery is fully charged
      this->battery = 100;
      for(int i=0; i<21; i++){
        this->sensors[i] = Sensor(i, this->WaveformGenerator.generateWaveform()); //sensor constructor
      }
      this->on = false;
      for(int i=0; i<21; i++){
        this->baseline[i] = 0; //sensor constructor, change later if necessary
      }
      this->timer = QElapsedTimer timer;
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

   QString EEG::lowBattery(){
      QString EEG::connection_lost(){
      this->red_light() = true;
      if(this->battery < 10){
         qDebug() << QString::fromStdString("Low Battery: Battery at 10%") << "\n";
      }
      if(this->battery < 5){
         qDebug() << QString::fromStdString("Battery critically low. Powering off") << "\n";
         this->power_off();
      }

   }

   void EEG::run_session(){
      this->setBlue(true);
      for(int i=0; i<21; i++){
        this->baseline[i] = this->CalcDominantFrequency(this->sensors[i]); //sensor constructor, change later if necessary
      }
      QTimer* sensorTimer = new QTimer();
      for(int i=0; i < 21; i++){
         QElapsedTimer ->setInterval(60); //Time in milliseconds
         int count = 0;
         connect(sensorTimer, &QTimer::timeout, this, [=](){
            count = count + 1;
            this->setGreen(true);
            this->baseline[i] = this->baseline[i]+5;
            this->sensors[i]->setDominantFrequency(this->baseline[i]);
            this->baseline[i] = this->CalcDominantFrequency(sensors[i])
            this->setGreen(false);
            if(count==16){
               sensorTimer.stop();
            }
         });
         sensorTimer->start();
      }
   }

   void EEG::updateSessionTime(){
      this->sessionTime = this->sessionTime + this->timer.nsecsElapsed();
   }

   void EEG::power_off(){
      this->updateSessionTime()
      this->timer.invalidate();
      this->on = false;

   }
   void EEG::power_on(){
      this->timer.start();
      this->on = true;

   }

   QString EEG:logger(){
      //Temp message
      return QString::fromStdString("DATA LOG FOR SESSION")
   }

   void EEG::connection(){
      this->timer.invalidate();
   }
   //Function should be triggerd in UI slot every 1 minute once connection lost button is clicked
   QString EEG::connection_lost(){
      this->red_light() = true;
      this->updateSessionTime()
      this->timer.reset();
      while((!this->timer.hasExpired(5000)) && this->timer.isValid()){
         qDebug() << QString::fromStdString("Beep! Connection Lost") << "\n";
      }
      if(this->timer.isValid == true){
         this->power_off();
         return this->logger();
      }
      else{
         this->timer.reset();
      }
      return QString::fromStdString("Connection Restored")
   }



/*
    bool red_light;
    bool green_light;
    bool blue_light;
    int battery;
    QElapsedTimer timer;
    Sensor sensors[21];
    bool on;
    qint64 sessionTime;
    int baselines[21];\

*/ 