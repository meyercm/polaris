#ifndef MOTORS_H
#define MOTORS_H

#include "pins.hpp"

class Motors {
public:
  void initialize();
  void set_tones(int x, int y, int z, unsigned long time);
  void update_motors(unsigned long time);
};

#endif
