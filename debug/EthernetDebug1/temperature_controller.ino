#include"temperature_controller.h"

void TEC::init(void)
{
   output=0;
   analogWriteResolution(ANALOG_WRITE_RESOLUTION);   
   pid=PID(&TEC::temperature, &TEC::output, &configuration.TEC.setpoint,configuration.TEC.P,configuration.TEC.I,configuration.TEC.D, configuration.TEC.direction);
   pid.SetTunings(configuration.TEC.P,configuration.TEC.I,configuration.TEC.D);
   pid.SetMode(AUTOMATIC);
   pid.SetOutputLimits(configuration.TEC.imin, configuration.TEC.imax);
   pid.SetSampleTime(100);
   TEC::current(output);  
}

float TEC::current(float I)
{
  float v1=-I/(1.+10./12.);
  float v2=v1+3.3/2;
  float code=(v2-3.3/6.)*1.5/3.3;
  int outDAC=(1<<ANALOG_WRITE_RESOLUTION)*code;
  outDAC=constrain(outDAC,0,(1<<ANALOG_WRITE_RESOLUTION)-1);
  analogWrite(DAC0, outDAC);
  return outDAC;
}

void TEC::update(void)
{
  pid.Compute();
  current(output);
}
