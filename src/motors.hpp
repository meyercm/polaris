#ifndef MOTORS_H
#define MOTORS_H

#include "pins.hpp"

class Motors {
public:
  void initialize();
  void set_tones(int x, int y, int z, unsigned long time);
  void update_motors(unsigned long time);
  int transform_u(int x, int y, int z);
  int transform_v(int x, int y, int z);
  int transform_w(int x, int y, int z);
};

#endif
