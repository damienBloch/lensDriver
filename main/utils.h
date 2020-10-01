#ifndef UTILS_H
#define UTILS_H
#include<DueFlashStorage.h>
#include<PID_v1.h>
#define PARAMETERS_ADDRESS 4

struct Parameters{
  struct{
    int gain; 
    float imin, imax;
    float frequency;
  }DAC;
  struct{
    double P,I,D;
    double setpoint;
    double imin,imax;
    int direction;
  }TEC;
  struct{
    float volt2intensity;
    float intensity2current;
    float filterTime;  
  }intensityCorrection;
  struct{
    float temperature2current;
  }temperatureCorrection;
  bool firstWrite;
};

Parameters defaultParameters={
  .DAC={.gain=1,.imin=-200,.imax=200,.frequency=3750},
  .TEC={.P=0.4, .I=0.04, .D=0, .setpoint=23,.imin=-1,.imax=1,.direction=DIRECT},
  .intensityCorrection={.volt2intensity=2.5,.intensity2current=-0.64634,.filterTime=14.},
  .temperatureCorrection={.temperature2current=2.356},
  .firstWrite=false
};

Parameters loadParameters(uint32_t address);
void systemPreset(void);
#endif
