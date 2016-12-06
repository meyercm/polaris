#include "Arduino.h"
#include <Wire.h>


void interrupt_handler(void) {
  while(Wire.available() > 0){
    Wire.read(); // clear pending reads
  }
  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x00));
  Wire.endTransmission(false);
  Wire.requestFrom(0x0E, 15);
  byte ready = Wire.read();
  byte x1 = Wire.read();
  byte x2 = Wire.read();
  byte y1 = Wire.read();
  byte y2 = Wire.read();
  byte z1 = Wire.read();
  byte z2 = Wire.read();

  Wire.read(); //discard
  Wire.read(); //discard

  byte offset_x1 = Wire.read();
  byte offset_x2 = Wire.read();
  byte offset_y1 = Wire.read();
  byte offset_y2 = Wire.read();
  byte offset_z1 = Wire.read();
  byte offset_z2 = Wire.read();

  Serial.print(ready);

  Serial.print(" X: ");
  Serial.print(x1*256 + x2);
  Serial.print(" Y: ");
  Serial.print(y1*256 + y2);
  Serial.print(" Z: ");
  Serial.print(z1*256 + z2);

  Serial.print(" Xo: ");
  Serial.print(offset_x1*256 + offset_x2);
  Serial.print(" Yo: ");
  Serial.print(offset_y1*256 + offset_y2);
  Serial.print(" Zo: ");
  Serial.print(offset_z1*256 + offset_z2);

  Serial.print("\r\n");
}

// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();
  //Wire.setClock(100000L);
  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x11)); //ctrl reg 2
  Wire.write(byte(0x80)); // enable
  Wire.endTransmission();
  Wire.beginTransmission(0x0E);
  //Wire.write(byte(0x10)); //ctrl reg 1
  //Wire.write(byte(0x0)); // disable
  Wire.write(byte(0x10)); //ctrl reg 1
  Wire.write(byte(0xC9)); // set 0.63 hz reporting rate
  //Wire.write(byte(0x59)); // set 10 hz reporting rate
  Wire.endTransmission();
  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x00));
  Wire.endTransmission(false);
  Wire.requestFrom(0x0E, 7);

  Wire.read(); // read and discard
  byte x1 = Wire.read();
  byte x2 = Wire.read();
  byte y1 = Wire.read();
  byte y2 = Wire.read();
  byte z1 = Wire.read();
  byte z2 = Wire.read();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x09));
  Wire.write(x1);
  Wire.endTransmission();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x0A));
  Wire.write(x2);
  Wire.endTransmission();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x0B));
  Wire.write(y1);
  Wire.endTransmission();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x0C));
  Wire.write(y2);
  Wire.endTransmission();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x0D));
  Wire.write(z1);
  Wire.endTransmission();

  Wire.beginTransmission(0x0E);
  Wire.write(byte(0x0E));
  Wire.write(z2);
  Wire.endTransmission();

  // initialize digital pin 13 as an output.
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(A0, interrupt_handler, RISING);
  //analogWrite(A0, 63);
}

void pulse(int length){
  // analogWrite(A0, 0);
  // delay(10);
  analogWrite(A0, 63);
  delay(length);// - 20);
  // analogWrite(A0, 255);
  // delay(10);
  analogWrite(A0, 127);
}

const int DIT = 100;
const int DAH = 300;

void play_n(){
  pulse(DAH);
  delay(DIT);
  pulse(DIT);
}

void play_a(){
  pulse(DIT);
  delay(DIT);
  pulse(DAH);
}

void play_e(){
  pulse(DIT);
}

void slew(int delayTime){
  for (int i = 0; i < 256; i++) {
    analogWrite(A0, i);
    delay(delayTime);
  }
}

// the loop function runs over and over again forever
void loop() {
  //Serial.print("loop top\r\n");
  digitalWrite(13, HIGH);
  delay(100);

  digitalWrite(13, LOW);
  // slew(50);
  // play_n();
  // delay(1000);
  // play_a();
  // delay(1000);
  // play_e();
  delay(1900);
  // analogWrite(A0, 0);
  // delay(1000);
  // analogWrite(A0, 31);
  // delay(1000);
  // analogWrite(A0, 63);
  // delay(1000);
  // analogWrite(A0, 95);
  // delay(1000);
  // analogWrite(A0, 127);
  // delay(1000);
  // analogWrite(A0, 159);
  // delay(1000);
  // analogWrite(A0, 191);
  // delay(1000);
  // analogWrite(A0, 223);
  // delay(1000);
  // analogWrite(A0, 255);
  // delay(1000);
}
