#include "communication.h"

template<typename T>
void Communication::SerialLoop(Stream* interface, T* executor)
{
  if ((*interface).available())
  {
    byte line_buffer[256];
    unsigned char read_length;
    read_length = (*interface).readBytesUntil('\n', line_buffer, 256);

    executor(interface, line_buffer, read_length);
  }
}


void Communication::printer(char* message)
{
  Serial.println(message);
}

template<typename T>
void Communication::writer(T* interface, byte* buffer, int count)
{
  for(int i=0;i<count;i++)
    buffer[i]=toupper(buffer[i]);

  // this just sends the command back to the sender
  (*interface).write(buffer, count);
  (*interface).println();
}

void Communication::streamWriter(Stream* interface, byte* buffer, int count)
{
  for(int i=0;i<count;i++)
    buffer[i]=toupper(buffer[i]);

  // this just sends the command back to the sender
  (*interface).write(buffer, count);
  (*interface).println();
}

template<typename T>
void Communication::interfaceprinter(T* interface, char* buffer)
{
  (*interface).print(buffer);
}
