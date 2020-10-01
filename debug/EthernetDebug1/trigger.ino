#include"trigger.h"

void TRIG::init(void)
{
  pinMode(A5,INPUT);  
  attachInterrupt(59, TRIG::change,CHANGE); 
}

void TRIG::startSequence(void)
{
  if(DAC::len>0)
  {
    DAC::pos=0;
    Timer0.start();
  }
}

void TRIG::stopSequence(void)
{
    Timer0.stop();
    if(DAC::len>0)
    {
      DAC::pos=0;
      if(DAC::mode==ARBITRARY)DAC::write(DAC::codeToCurrent(DAC::getWordAt(DAC::pos)));
    }
}

void TRIG::change(void)
{
  //the optocoupler reverses the trigger value
  state=!digitalRead(A5);
  if(DAC::mode==ARBITRARY)
  {
    if(state)startSequence();
    else stopSequence();
  }  
}
