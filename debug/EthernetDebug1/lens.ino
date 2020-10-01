#include"lens.h"

void LENS::init(void)
{
  Wire.begin();
  Wire.setClock(50000);
  //set OPT temperature sensor precision to 0.0625C
  Wire.beginTransmission(B00011000); 
  Wire.write(byte(B00001000));
  Wire.write(byte(B00000011));
  Wire.endTransmission();  

  //prepare OPT temperature sensor for reading
  Wire.beginTransmission(B00011000); 
  Wire.write(byte(B00000101));
  Wire.endTransmission();
  getTemperature();
}


float LENS::getTemperature(void)
{
  //ask OPT temperature sensor to send value
  Wire.requestFrom(B00011000,2); 
  unsigned char c1 = Wire.read(); 
  unsigned char c2 = Wire.read(); 
  unsigned int tmp=(c1 & B00001111)*256+c2; 
  float T=tmp*0.0625*((c1&B00010000)?(-1):(+1));
  temperature=T;
  TEC::temperature=T;
  DAC::write(DAC::targetCurrent);
  return T;
}
