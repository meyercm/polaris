#include "compass.hpp"
#include <Wire.h>
namespace {
  const byte DEVICE_ADDRESS = 0x0E;
  const byte CTRL_REG_1 = 0x10;
  // register 1 options
  const byte ACTIVE=0x01;
  const byte TRIGGER=0x02;
  const byte FAST_READ=0x04;
  const byte OVER_SAMPLE_16 = 0x00;
  const byte OVER_SAMPLE_32 = 0x08;
  const byte OVER_SAMPLE_64 = 0x10;
  const byte OVER_SAMPLE_128 = 0x18;

  const byte CTRL_REG_2 = 0x11;
  // register 2 options
  const byte AUTO_RESET = 0x80;
  const byte RAW = 0x20;
  const byte MANUAL_RESET = 0x10;
}

void Compass::initialize(){
  Wire.begin();
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(CTRL_REG_2);
  Wire.write(AUTO_RESET & RAW);
  Wire.endTransmission();
}

void Compass::request_measurement(){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(CTRL_REG_1);
  Wire.write(OVER_SAMPLE_128 & TRIGGER);
  Wire.endTransmission();
}

void Compass::read(){
  while(Wire.available() > 0){
    Wire.read(); // clear pending reads
  }
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(byte(0x00));
  Wire.endTransmission(false);
  Wire.requestFrom(DEVICE_ADDRESS, 7);
  Wire.read(); // ready byte, must read, but can discard
  byte x1 = Wire.read();
  byte x2 = Wire.read();
  int16_t x = (x1 << 8) | x2;
  this->x = (int) x;
  byte y1 = Wire.read();
  byte y2 = Wire.read();
  int16_t y = (y1 << 8) | y2;
  this->y = (int) y;
  byte z1 = Wire.read();
  byte z2 = Wire.read();
  int16_t z = (z1 << 8) | z2;
  this->z = (int) z;

// FIX:
  Serial.print(" X: ");
  Serial.print(this->x);
  Serial.print(" Y: ");
  Serial.print(this->y);
  Serial.print(" Z: ");
  Serial.print(this->z);
  Serial.print("\r\n");
}
