#include "Arduino.h"
#include <Wire.h>

const int PWM_1 = 5;
const int PWM_2 = 6;
const int PWM_3 = 9;
const int PWM_4 = 10;
const int PWM_5 = 11;
const int PWM_6 = 12;
const int EN_1 = A5;
const int EN_2 = A4;
const int EN_3 = A3;
const int EN_4 = A2;
const int EN_5 = A1;
const int EN_6 = A0;


// the setup function runs once when you press reset or power the board
void setup() {
  Wire.begin();

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
  Serial.print("On 0");
  digitalWrite(EN_1, 1);
  analogWrite(PWM_1, 0);
  delay(1000);
  Serial.print("31 ");
  analogWrite(PWM_1, 31);
  delay(1000);
  Serial.print("63 ");
  analogWrite(PWM_1, 63);
  delay(1000);
  Serial.print("95 ");
  analogWrite(PWM_1, 95);
  delay(1000);
  Serial.print("127 ");
  analogWrite(PWM_1, 127);
  delay(1000);
  Serial.print("159 ");
  analogWrite(PWM_1, 159);
  delay(1000);
  Serial.print("191 ");
  analogWrite(PWM_1, 191);
  delay(1000);
  Serial.print("223 ");
  analogWrite(PWM_1, 223);
  delay(1000);
  Serial.print("255 ");
  analogWrite(PWM_1, 255);
  delay(1000);
  Serial.print("Off\r\n");
  digitalWrite(EN_1, 0);

  delay(1000);
}
