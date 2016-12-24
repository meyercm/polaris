#include "motors.hpp"
namespace{
  const byte MOTOR_EN [] = {EN_1, EN_2, EN_3, EN_4, EN_5, EN_6};
  const byte MOTOR_PWM [] = {PWM_1, PWM_2, PWM_3, PWM_4, PWM_5, PWM_6};

  //indicies into MOTOR_EN and MOTOR_PWM.
  const byte POS_X = 0;
  const byte NEG_X = 1;
  const byte POS_Y = 2;
  const byte NEG_Y = 3;
  const byte POS_Z = 4;
  const byte NEG_Z = 5;
}
void Motors::initialize() {
  for(int i=0; i < 6; i++){
    digitalWrite(MOTOR_EN[i], LOW);
    analogWrite(MOTOR_PWM[i], 0);
  }
}

void Motors::set_tones(int x, int y, int z, unsigned long time){

}

void Motors::update_motors(unsigned long time){

}
