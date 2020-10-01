#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#define ANALOG_WRITE_RESOLUTION (12)  
#include<PID_v1.h>

extern Parameters configuration;

struct TEC
{
  static void init(void);
  static float current(float I);
  static void update(void);
  static PID pid;
  static double output,temperature;
};
double TEC::output,TEC::temperature;
PID TEC::pid(&TEC::temperature, &TEC::output, &configuration.TEC.setpoint,configuration.TEC.P,configuration.TEC.I,configuration.TEC.D, configuration.TEC.direction);
#endif
