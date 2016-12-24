#ifndef COMPASS_H
#define COMPASS_H

#include "arduino.h"

class Compass {
public:
  void initialize();
  void request_measurement();
  void read();
  int get_x();
  int get_y();
  int get_z();

//private:
  void update_min_max(int x, int y, int z);
  int16_t x;
  int16_t y;
  int16_t z;
  int min_x = -4743;
  int max_x = -3815;
  int min_y = 3049;
  int max_y = 3893;
  int min_z = 783;
  int max_z = 1658;

};
#endif
