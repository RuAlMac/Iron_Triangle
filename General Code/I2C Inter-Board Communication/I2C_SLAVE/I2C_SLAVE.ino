//Slave code for a set of Arduino boards communicating over I2C
//Credit: https://www.instructables.com/I2C-between-Arduinos/

#include <Wire.h>

int x = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes){
  x = Wire.read();
}

void loop() {
  Serial.println(x);
}
