#include "main.h"

using namespace Communication;

// use SerialUSB if uploading to Arduino Due via native port
// otherwise use Serial
#define SerialInterface SerialUSB

void setup() {
  // Open serial communications and wait for port to open:
  SerialInterface.begin(9600);
  while (!SerialInterface) 
  {}  // wait for serial port to connect. Needed for native USB port only
  // Initialise Ethernet communication
  EthernetN::init();
}

void loop() {
  EthernetN::loop(writer<EthernetClient>);
  SerialLoop(&SerialInterface, writer<typeof(SerialInterface)>);
}
