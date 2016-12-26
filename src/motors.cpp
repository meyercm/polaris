#include "motors.hpp"
namespace{
  const int MIN_POWER = 32;
  const int PERIOD = 20;

  const float DIAG_1 = 0.4;
  const float DIAG_2 = 0.72;
  const float Z_OFFSET = 0.59;
  const float X_LINE = 0.84;

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
      if (cell >= power_level) {
        digitalWrite(enable_pin, LOW);
      } else {
        digitalWrite(enable_pin, HIGH);
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

  // Motor num,  -1 for indicies
  const byte POS_U = 6           - 1;
  const byte NEG_U = 2           - 1;
  const byte POS_V = 1           - 1;
  const byte NEG_V = 5           - 1;
  const byte POS_W = 4           - 1;
  const byte NEG_W = 3           - 1;

  const int PULSE_DURATION = 200;
}

void Motors::initialize() {
  for(int i=0; i < 6; i++){
    motors[i]->turn_off();
  }
}

void Motors::set_tones(int x, int y, int z, unsigned long now){
  int u = transform_u(x, y, z);
  int v = transform_v(x, y, z);
  int w = transform_w(x, y, z);

  if (abs(u) > abs(v) && abs(u) > abs (w)){
    if (u > 0) {
      motors[POS_U]->set_tone(u, PULSE_DURATION, now);
    } else {
      motors[NEG_U]->set_tone(abs(u), PULSE_DURATION, now);
    }
  } else if (abs(v) > abs(u) && abs(v) > abs(w)){
    if (v > 0) {
      motors[POS_V]->set_tone(v, PULSE_DURATION, now);
    } else {
      motors[NEG_V]->set_tone(abs(v), PULSE_DURATION, now);
    }
  } else{
    if (w > 0) {
      motors[POS_W]->set_tone(w, PULSE_DURATION, now);
    } else {
      motors[NEG_W]->set_tone(abs(w), PULSE_DURATION, now);
    }
  }
}

void Motors::update_motors(unsigned long now){
  for(int i=0; i < 6; i++){
    motors[i]->update(now);
  }
}

int Motors::transform_u(int x, int y, int z){
  return (int)(DIAG_1 * x + DIAG_2 * y + Z_OFFSET * z);
}
int Motors::transform_v(int x, int y, int z){
  return (int)(-DIAG_1 * x + DIAG_2 * y + -Z_OFFSET * z);
}
int Motors::transform_w(int x, int y, int z){
  return (int)(-X_LINE * x + 0 * y + Z_OFFSET * z);
}
