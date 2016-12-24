#include "Arduino.h"
#include <Wire.h>

#include "main.hpp"
#include "compass.hpp"
#include "motors.hpp"

namespace{
  Compass compass;
  Motors motors;
  unsigned long last_measure;
  const long MEASURE_TIME = 1000L;
  bool new_measurement = false;
}

// the setup function runs once when you press reset or power the board
void setup() {
  setup_pins();
  attachInterrupt(INT_1, interrupt_handler, RISING);

  compass.initialize();
  last_measure = millis();
}

void loop() {
  unsigned long now = millis();
  //Serial.write("loop\r\n");
  if (now > last_measure + MEASURE_TIME) {
    compass.request_measurement();
    last_measure = now;
  }
  if (new_measurement) {
    new_measurement = false;
    compass.read();
    motors.set_tones(compass.getX(), compass.getY(), compass.getZ(), now);
  }
  motors.update_motors(now);
  handle_serial();
}

void handle_serial(){

}

void interrupt_handler(void) {
  new_measurement = true;
}


void setup_pins(){
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  pinMode(EN_3, OUTPUT);
  pinMode(EN_4, OUTPUT);
  pinMode(EN_5, OUTPUT);
  pinMode(EN_6, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(PWM_4, OUTPUT);
  pinMode(PWM_5, OUTPUT);
  pinMode(PWM_6, OUTPUT);
  pinMode(INT_1, OUTPUT);
}
