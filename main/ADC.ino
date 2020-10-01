#include"ADC.h"

extern Parameters configuration;

void A2DC::init(void)
{
   //initialise AD7732 chip select pin 
   ADC_CSX_PORT->PIO_PER |= ADC_CSX_MSK;
   ADC_CSX_PORT->PIO_OER |= ADC_CSX_MSK;
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK; 
   
   //reset AD7732
   ADC_RSTX_PORT->PIO_PER |= ADC_RSTX_MSK;
   ADC_RSTX_PORT->PIO_OER |= ADC_RSTX_MSK;
   ADC_RSTX_PORT->PIO_CODR |= ADC_RSTX_MSK;
   delayMicroseconds(10);
   ADC_RSTX_PORT->PIO_SODR |= ADC_RSTX_MSK;
   delayMicroseconds(10);

   //initialise AD7732 RDY output pin 
   ADC_RDYX_PORT->PIO_PER |= ADC_RDYX_MSK;
   ADC_RDYX_PORT->PIO_ODR |= ADC_RDYX_MSK;

   //set conversion time to 2.75ms
   SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x30);
   SPI.transfer(0xFF);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();

   //auto-calibrate zero 
   /*SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x38);
   SPI.transfer(0x81);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();
   while(ADC_RDYX_PORT->PIO_PDSR&ADC_RDYX_MSK);*/

   //set reading range to 0V +10V
   SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x28);
   SPI.transfer(0x01);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();   

   initReading();
   while(ADC_RDYX_PORT->PIO_PDSR&ADC_RDYX_MSK);
   readValue=read();
   _filteredIntensity=codeToIntensity(readValue);
   _previousTime=micros();
   initReading();
   SPI.usingInterrupt(TC1_IRQn); 
   Timer1.attachInterrupt(A2DC::update).setPeriod(5000).start();
   /*SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x38);
   SPI.transfer(0xE0);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();
   while(ADC_RDYX_PORT->PIO_PDSR&ADC_RDYX_MSK);*/
}

void A2DC::update(void)
{
  if(!(ADC_RDYX_PORT->PIO_PDSR&ADC_RDYX_MSK))
  {
   readValue=read();
   initReading(); 
  }
  double intensity=codeToIntensity(readValue);
  unsigned int currentTime=micros();
  _filteredIntensity+=((double)(currentTime-_previousTime))*1e-6*(intensity-_filteredIntensity)/configuration.intensityCorrection.filterTime;
  _previousTime=currentTime; 
  DAC::write(DAC::targetCurrent);  
}

float A2DC::codeToIntensity(int value)
{
  return value/19067.0*2.0 *configuration.intensityCorrection.volt2intensity;
}

void A2DC::initReading(void)
{
   SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x38);
   SPI.transfer(0x41);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();
}

unsigned int A2DC::read(void)
{
   unsigned int value=0;
   SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x48);
   value=SPI.transfer16(0);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();
   return value;
}
