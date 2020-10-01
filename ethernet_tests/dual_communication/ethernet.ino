#include "ethernet.h"

void EthernetN::init()
{

#if defined(ARDUINO_SAM_DUE)
  Ethernet.init(77); // on the optotune driver
#else
  Ethernet.init(10);  // Most Arduino shields
#endif


  // initialize the Ethernet device
  Ethernet.begin(mac, ip); //, myDns, gateway, subnet);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    SerialInterface.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    SerialInterface.println("Ethernet cable is not connected.");
  }

  // start listening for clients
  server.begin();

  SerialInterface.print("Chat server address:");
  SerialInterface.println(Ethernet.localIP());

}

void EthernetN::addNewClients() {
  // check for any new client connecting, and say hello (before any incoming data)
  EthernetClient newClient = server.accept();
  if (newClient) {
    for (byte i = 0; i < 8; i++) {
      if (!clients[i]) {
        SerialInterface.print("We have a new client #");
        SerialInterface.println(i);
        newClient.print("Hello, client number: ");
        newClient.println(i);
        // Once we "accept", the client is no longer tracked by EthernetServer
        // so we must store it into our list of clients
        clients[i] = newClient;
        break;
      }
    }
  }
}

void EthernetN::stopDisconnectedClients() {
  // stop any clients which disconnect
  for (byte i = 0; i < 8; i++) {
    if (clients[i] && !clients[i].connected()) {
      SerialInterface.print("disconnect client #");
      SerialInterface.println(i);
      clients[i].stop();
    }
  }
}

template <typename T>
void EthernetN::checkClientMessages(T* executor) {
  // check for incoming data from all clients
  for (byte i = 0; i < 8; i++) {
    if (clients[i] && clients[i].available() > 0) {
      // read bytes from a client
      byte buffer[256];
      int count = clients[i].readBytesUntil('\n', buffer, 256);



      //executor(clients + i, buffer, count);
      executor(&(clients[i]), buffer, count);
      //executor(Serial, buffer, count);

      if (CHAT_REPEATER)
      {
        SerialInterface.print("Client ");
        SerialInterface.print(i);
        SerialInterface.print(": ");
        SerialInterface.write(buffer, count);
        SerialInterface.println();
        // write the bytes to all other connected clients
        for (byte j = 0; j < 8; j++) {
          if (j != i && clients[j].connected()) {
            clients[j].print("Client ");
            clients[j].print(i);
            clients[j].print(": ");
            clients[j].write(buffer, count);
            clients[j].println();
          }
        }
      }
    }
  }
}

template <typename T>
void EthernetN::runLoop(T* executor) {
  addNewClients();
  checkClientMessages(executor);
  stopDisconnectedClients();
}

void EthernetN::blank(...)
{}

void EthernetN::loop()
{
  runLoop(blank);
}

template <typename T>
void EthernetN::loop(T* executor)
{
  runLoop(executor);
}
