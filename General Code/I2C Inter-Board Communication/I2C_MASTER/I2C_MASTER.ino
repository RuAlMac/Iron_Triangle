//Master code for a set of Arduino boards communicating over I2C
//Credit: https://www.instructables.com/I2C-between-Arduinos/

#include <Wire.h>

int x = 0;

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(x);              // sends x
  Wire.endTransmission();    // stop transmitting
  x++; // Increment x
  if (x > 5) x = 0; // `reset x once it gets 6
  delay(500);
}
