#include"main.h"

#include <SPI.h>
#include <Ethernet.h>

extern Parameters configuration;

void setup() {
  Parameters parameters=loadParameters();
  if(parameters.firstWrite)
  {
    storeParameters(defaultParameters);
    configuration=defaultParameters;    
  }
  else configuration=parameters; 
   
  SerialUSB.begin(115200);
  SerialUSB.setTimeout(10000);
  SPI.begin();
  delay(100);

  DAC::init();
  TRIG::init();  
  //Ethernet::init();  
  LENS::init(); 
  TEC::init();
  SCPI::init();
  A2DC::init();
  DAC::write((configuration.DAC.imin+configuration.DAC.imax)/2);   

  Ethernet.init(77);  // Most Arduino shields
  
}

void floop()
{
  digitalWrite(10, HIGH);
  delay(5);
  SerialUSB.println(digitalRead(10));
  delay(100);
  digitalWrite(10, LOW);
  SerialUSB.println(digitalRead(10));
  delay(500);
}

void loop()
{
  auto link = Ethernet.linkStatus();
  SerialUSB.print("Link status: ");
  switch (link) {
    case Unknown:
      SerialUSB.println("Unknown");
      break;
    case LinkON:
      SerialUSB.println("ON");
      break;
    case LinkOFF:
      SerialUSB.println("OFF");
      break;
  }
  delay(1000);
}

void old_loop(){  
  LENS::getTemperature();  
  TEC::update();  
   /*SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE3));
   ADC_CSX_PORT->PIO_CODR |= ADC_CSX_MSK;
   SPI.transfer(0x18 & (1<<6));
   unsigned int value1=SPI.transfer(0x0);
   unsigned int value2=SPI.transfer(0x0);
   unsigned int value3=SPI.transfer(0x0);
   ADC_CSX_PORT->PIO_SODR |= ADC_CSX_MSK;
   SPI.endTransaction();
   SerialUSB.print(value1);
   SerialUSB.print(" ");
   SerialUSB.print(value2);
   SerialUSB.print(" ");
   SerialUSB.print(value3);
   SerialUSB.println("");*/
  char line_buffer[256];
  unsigned char read_length;
  read_length = SerialUSB.readBytesUntil('\n', line_buffer, 256);
  for(int i=0;i<read_length;i++)
    line_buffer[i]=toupper(line_buffer[i]);
  if(read_length > 0)scpi_execute_command(&SCPI::ctx, line_buffer, read_length);
  delay(10);
}
