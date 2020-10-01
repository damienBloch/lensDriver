#include"DAC.h"

extern Parameters configuration;

void DAC::init(void)
{
  //initialise ADum1410 disable pin to be blocking.
  INSL_DSBL_PORT->PIO_PER |= INSL_DSBL_MSK;
  INSL_DSBL_PORT->PIO_OER |= INSL_DSBL_MSK;
  INSL_DSBL_PORT->PIO_SODR |= INSL_DSBL_MSK;
  //initialise AD5542 LDACX pin. With this the code is converted to voltage only when LDACX is set to low.
  DAC_LDACX_PORT->PIO_PER |= DAC_LDACX_MSK;
  DAC_LDACX_PORT->PIO_OER |= DAC_LDACX_MSK;
  DAC_LDACX_PORT->PIO_SODR |= DAC_LDACX_MSK;
  //initialise AD5542 CSX pin to unselect the DAC for now.
  DAC_CSX_PORT->PIO_PER |= DAC_CSX_MSK;
  DAC_CSX_PORT->PIO_OER |= DAC_CSX_MSK;
  DAC_CSX_PORT->PIO_SODR |= DAC_CSX_MSK; 
  //initialise gain to its initial value.
  DAC_GAIN_PORT->PIO_PER |= DAC_GAIN_MSK;
  DAC_GAIN_PORT->PIO_OER |= DAC_GAIN_MSK;
  (configuration.DAC.gain==1)?(DAC_GAIN_PORT->PIO_CODR |= DAC_GAIN_MSK):(DAC_GAIN_PORT->PIO_SODR |= DAC_GAIN_MSK);  
  
  //create an empty array that will contain the current ramp
  arr=NULL;pos=0;len=0;
  SPI.usingInterrupt(TC0_IRQn); 
  intensityCorrection=false;
  temperatureCorrection=true;
  mode=CONSTANT;
  Timer0.attachInterrupt(DAC::update).setFrequency(configuration.DAC.frequency);
}

void DAC::clearArray(void)
{
  if(arr!=NULL)
    delete arr;
  arr=NULL;
  len=0;pos=0;
}

void DAC::update()
{   //this function is called at every tick of the DAC clock and will run through the sequence array
    TC_GetStatus(TC0, 0);    
    pos++;
    pos=min(pos,len-1);
    write(codeToCurrent(getWordAt(DAC::pos)));
}

unsigned int DAC::_write(int value)
{  
   value=constrain(value,0,(1<<16)-1);
   //the isolator is opened to let the signal through
   INSL_DSBL_PORT->PIO_CODR |= INSL_DSBL_MSK;
   delayMicroseconds(2);
   
   //the 16bits encoding the current are sent to the DAC
   SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
   DAC_CSX_PORT->PIO_CODR |= DAC_CSX_MSK;
   SPI.transfer16(value);   
   DAC_CSX_PORT->PIO_SODR |= DAC_CSX_MSK;
   SPI.endTransaction();

   //latch the DAC value
   delayMicroseconds(1);
   DAC_LDACX_PORT->PIO_CODR |= DAC_LDACX_MSK;
   delayMicroseconds(1);
   DAC_LDACX_PORT->PIO_SODR |= DAC_LDACX_MSK;

   //close isolator to prevent noise on the bus to be transmitted to the DAC
   INSL_DSBL_PORT->PIO_SODR |= INSL_DSBL_MSK;

   current=codeToCurrent(value);   
   return value;
}

unsigned int DAC::currentToCode(float I)
{
    return (65536.*(I/configuration.DAC.gain+250.)/500.);
}

float DAC::codeToCurrent(unsigned int value)
{
    return (value/65536.*500.-250.)*configuration.DAC.gain;
}

float DAC::write(float I)
{  
   targetCurrent=I;
   if(intensityCorrection)
      I-=A2DC::_filteredIntensity*configuration.intensityCorrection.intensity2current;
    
   if(temperatureCorrection)
      I-=(LENS::temperature-23.)*configuration.temperatureCorrection.temperature2current;
      
   I=constrain(I,configuration.DAC.imin,configuration.DAC.imax);
   int value=currentToCode(I); 
   return codeToCurrent(_write(value));
}

int DAC::getWordAt(int index)
{
  return (arr[index/2] & (0xFFFF << (16*(index%2))))>>(16*(index%2));
}
