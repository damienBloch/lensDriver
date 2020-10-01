#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//#ifndef SerialInterface
//#define SerialInterface Serial  //fallback?
//#endif

namespace Communication
{
#ifdef SerialInterface
static Stream* StreamInterface = &SerialInterface;
#else
static Stream* StreamInterface = &SerialUSB;
#endif

template<typename T>
void SerialLoop(Stream* interface, T* executor);

void printer(char* message);

void writer(Stream* interface, byte* buffer, int count);

void interfaceprinter(Stream* interface, char* buffer);
}


#endif
