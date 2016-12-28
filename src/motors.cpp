#include "motors.hpp"
namespace{
  const float MIN_POWER = 0.5;
  const int PERIOD = 20;

  class Motor {
  public:
    Motor(byte p_enable_pin, byte p_pwm_pin, float x, float y, float z){
      enable_pin = p_enable_pin;
      pwm_pin = p_pwm_pin;
      x_coord = x;
      y_coord = y;
      z_coord = z;
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

    void set_tone(int x, int y, int z, int duration, unsigned long now){
      y = y+1;
      z = z+1;
      // dot product, result is cos(theta) * magnitude:  0.0-255.0
      float power = (y * y_coord) + (z * z_coord);
      float power2 = (power*power) / (y*y+z*z);
      if (power2 > MIN_POWER && power > 0){
        turn_off_time = now + duration;
        //normalize to PERIOD
        power_level = (int)((power2 / (1.0)) * PERIOD);
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
    float x_coord;
    float y_coord;
    float z_coord;
  };

  Motor *motors[] = {
    new Motor(EN_1, PWM_1, 0, 0.8, 0.5), //120
    new Motor(EN_2, PWM_2, 0, -0.8, 0.5), //240
    new Motor(EN_3, PWM_3, 0, 0.0, 0.94), //180
    new Motor(EN_4, PWM_4, 0, 0.0, -0.94), //0
    new Motor(EN_5, PWM_5, 0, -0.8, -0.5), // 300
    new Motor(EN_6, PWM_6, 0, 0.8, -0.5), //60
  };
  int num_motors = 6;

  const int PULSE_DURATION = 100;
}

void Motors::initialize() {
  for(int i=0; i < num_motors; i++){
    motors[i]->turn_off();
  }
}

void Motors::set_tones(int x, int y, int z, unsigned long now){
  for(int i=0; i < num_motors; i++){
    motors[i]->set_tone(x, y, z, PULSE_DURATION, now);
  }
}

void Motors::update_motors(unsigned long now){
  for(int i=0; i < num_motors; i++){
    motors[i]->update(now);
  }
}
