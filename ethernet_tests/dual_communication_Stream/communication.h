#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace Communication
{
template<typename T>
void SerialLoop(Stream* interface, T* executor);

void printer(char* message);

template<typename T>
void writer(T* interface, byte* buffer, int count);

void streamWriter(Stream* interface, byte* buffer, int count);

template<typename T>
void interfaceprinter(T* interface, char* buffer); 
}


#endif
