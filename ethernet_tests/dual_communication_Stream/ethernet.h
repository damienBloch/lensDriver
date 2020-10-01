#ifndef ETHERNET_H
#define ETHERNET_H

#include <SPI.h>
#include <Ethernet.h>

#define CHAT_REPEATER false

namespace EthernetN
{

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);

// telnet defaults to port 23
EthernetServer server(23);

EthernetClient clients[8];

static void init();

template <typename T>
static void runLoop(T*);
static void blank(...);
static void loop();
template <typename T>
void loop(T* executor);
static void addNewClients();
static void stopDisconnectedClients();
template <typename T>
void checkClientMessages(T* executor);
}


#endif
