#include "motors.hpp"
namespace{
  const int MIN_POWER = 32;
  const int PERIOD = 20;

  class Motor {
  public:
    Motor(byte p_enable_pin, byte p_pwm_pin){
      enable_pin = p_enable_pin;
      pwm_pin = p_pwm_pin;
    }

    void update(unsigned long now){
      if (now >= turn_off_time){ turn_off(); }
      if (is_off){ return; }
      int cell = (now - start_time) % PERIOD;
      // Serial.print("update ");
      // Serial.print(cell);
      // Serial.print("\r\n");
      if (cell == 0) {
        // Serial.print("power up ");
        // Serial.print(pwm_pin);
        // Serial.print("\r\n");
        digitalWrite(enable_pin, HIGH);
      } else if (cell == power_level) {
        // Serial.print("power down ");
        // Serial.print(pwm_pin);
        // Serial.print("\r\n")
        digitalWrite(enable_pin, LOW);
      }
    }

    void set_tone(int power, int duration, unsigned long now){
      // This is temporary, and mostly driven by the fuckup with pin 9 / PWM_3
      // whereby we can't really do pwm with that motor, so we fake it through the
      // enable pin.
      if (power > MIN_POWER){
        turn_off_time = now + duration;
        power_level = (int)((power / 255.0) * PERIOD);
        start_time = now;
        is_off = false;
      } else {
        turn_off();
      }
    }

    void turn_off(){
      digitalWrite(enable_pin, LOW);
      analogWrite(pwm_pin, 0);
      is_off = true;
    }
  private:
    byte enable_pin;
    byte pwm_pin;
    unsigned long turn_off_time;
    unsigned long start_time;
    int power_level;
    bool is_off = false;
  };

  Motor *motors[] = {
    new Motor(EN_1, PWM_1),
    new Motor(EN_2, PWM_2),
    new Motor(EN_3, PWM_3),
    new Motor(EN_4, PWM_4),
    new Motor(EN_5, PWM_5),
    new Motor(EN_6, PWM_6),
  };

  //indicies into Motors.
  const byte POS_X = 0;
  const byte NEG_X = 1;
  const byte POS_Y = 2;
  const byte NEG_Y = 3;
  const byte POS_Z = 4;
  const byte NEG_Z = 5;

  const int PULSE_DURATION = 200;
}

void Motors::initialize() {
  for(int i=0; i < 6; i++){
    motors[i]->turn_off();
  }
}

void Motors::set_tones(int x, int y, int z, unsigned long now){
  if (x > 0) {
    motors[POS_X]->set_tone(x, PULSE_DURATION, now);
  } else {
    motors[NEG_X]->set_tone(abs(x), PULSE_DURATION, now);
  }
  if (y > 0) {
    motors[POS_Y]->set_tone(y, PULSE_DURATION, now);
  } else {
    motors[NEG_Y]->set_tone(abs(y), PULSE_DURATION, now);
  }
  if (z > 0) {
    motors[POS_Z]->set_tone(z, PULSE_DURATION, now);
  } else {
    motors[NEG_Z]->set_tone(abs(z), PULSE_DURATION, now);
  }
}

void Motors::update_motors(unsigned long now){
  for(int i=0; i < 6; i++){
    motors[i]->update(now);
  }
}
