#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace Communication
{
template<typename T1, typename T2>
void SerialLoop(T1* interface, T2 executor);

void printer(char* message);

template<typename T>
void writer(T* interface, byte* buffer, int count);

template<typename T>
void interfaceprinter(T* interface, char* buffer); 
}


#endif
