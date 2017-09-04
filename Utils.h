#ifndef _Utils_h
#define _Utils_h

#include <EEPROM.h>

class Utils {
public:

  static void eepromWriteLong(int start,unsigned long v) {
    EEPROM.write(start,(v & 0xff));
    EEPROM.write(start+1,((v >> 8) & 0xff));
    EEPROM.write(start+2,((v >> 16) & 0xff));
    EEPROM.write(start+3,((v >> 24) & 0xff));
  }

  static unsigned long eepromReadLong(int start) {
    unsigned long r = 0;
    unsigned long b;
    b = EEPROM.read(start);
    r = r | b;
    b = EEPROM.read(start+1);
    b <<= 8;
    r = r | b;
    b = EEPROM.read(start+2);
    b <<= 16;
    r = r | b;
    b = EEPROM.read(start+3);
    b <<= 24;
    r = r | b;
    return r;
  }
};

#endif
