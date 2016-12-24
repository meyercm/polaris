#ifndef COMPASS_H
#define COMPASS_H

#include "arduino.h"

class Compass {
public:
  void initialize();
  void request_measurement();
  void read();
  int getX() {return (int)x;}
  int getY() {return (int)y;}
  int getZ() {return (int)z;}

//private:
  int16_t x;
  int16_t y;
  int16_t z;
};
#endif
