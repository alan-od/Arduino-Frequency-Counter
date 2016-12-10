//The standard EEPROM read and write functions only enable byte data
//transfers in and out of EEPROM. The following code enables complete
//data structures to be written/read to EEPROM.  You need to be careful
//if you want to write a second structure though, because of EEPROM
//address issues!
//The code was taken from http://playground.arduino.cc/Code/EEPROMWriteAnything
//had a couple of problems with this code as stated in the article, so slightly modified!

//#include <Arduino.h>  // for type definitions
#include <EEPROM.h>

#ifndef EEPROM_STRUCT
#define EEPROM_STRUCT
template <class T> int EEPROM_writeStruct(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readStruct(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}
#endif
