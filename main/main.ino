#include"main.h"

// use SerialUSB if uploading to Arduino Due via native port
// otherwise use Serial
#define SerialInterface SerialUSB

// disable this to debug code on an Arduino without the lens driver hardware (except Ethernet shield)
#define LENS_DRIVER_BOX true

extern Parameters configuration;

void setup() {
  Parameters parameters = loadParameters();
  if (parameters.firstWrite)
  {
    storeParameters(defaultParameters);
    configuration = defaultParameters;
  }
  else configuration = parameters;

  SerialInterface.begin(115200);
  //  SerialInterface.setTimeout(10000);
  SerialInterface.println("Setup");
  SPI.begin();
  delay(100);

#if LENS_DRIVER_BOX
  DAC::init();
  TRIG::init();
  LENS::init();
  TEC::init();
  A2DC::init();
  DAC::write((configuration.DAC.imin + configuration.DAC.imax) / 2);
#endif
  EthernetN::init();
  SCPI::init();
}

// This function is called by the Ethernet and Serial communication handlers. 
// It interprets the command received from the user and executes it.
// If appropriate, it also responds to the interface from which the command was sent.
scpi_error_t executor(Stream* interface, byte* line_buffer, int read_length)
{
  //set the correct communication interface so that SCPI writes back to the requester
  Communication::StreamInterface = interface;
  for (int i = 0; i < read_length; i++)
    line_buffer[i] = toupper(line_buffer[i]);
  return scpi_execute_command(&SCPI::ctx, (const char*) line_buffer, read_length);
}

void loop() {
#if LENS_DRIVER_BOX
  LENS::getTemperature();
  TEC::update();
#endif
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

  // Ethernet and Serial communication handlers
  EthernetN::loop(executor);
  Communication::SerialLoop(&SerialInterface, executor);
  // The two lines above do conceptually the same as the commented out code below, except they work over both Ethernet and SerialUSB
  //  char line_buffer[256];
  //  unsigned char read_length;
  //  read_length = SerialUSB.readBytesUntil('\n', line_buffer, 256);
  //  for (int i = 0; i < read_length; i++)
  //    line_buffer[i] = toupper(line_buffer[i]);
  //  if (read_length > 0)scpi_execute_command(&SCPI::ctx, line_buffer, read_length);
  delay(10);
}
