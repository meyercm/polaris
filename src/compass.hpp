#ifndef COMPASS_H
#define COMPASS_H

#include "arduino.h"

class Compass {
public:
  void initialize();
  void request_measurement();
  void read();
  int getX() {return x;}
  int getY() {return y;}
  int getZ() {return z;}

private:
  int x, y, z;
};
#endif
