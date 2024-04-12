void activateRedLeds() {
  digitalWrite(redLed1, HIGH);
  digitalWrite(redLed2, HIGH);
  digitalWrite(redLed3, HIGH);
  digitalWrite(redLed4, HIGH);
}

void deactivateRedLeds() {
  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
  digitalWrite(redLed3, LOW);
  digitalWrite(redLed4, LOW);
}

void activateGreenLeds() {
  digitalWrite(greenLed1, HIGH);
  digitalWrite(greenLed2, HIGH);
  digitalWrite(greenLed3, HIGH);
  digitalWrite(greenLed4, HIGH);
}

void deactivateGreenLeds() {
  digitalWrite(greenLed1, LOW);
  digitalWrite(greenLed2, LOW);
  digitalWrite(greenLed3, LOW);
  digitalWrite(greenLed4, LOW);
}

void deactivatePrototypeLeds() {
  digitalWrite(pirLed1, LOW);
  digitalWrite(pirLed2, LOW);
  digitalWrite(pirLed3, LOW);
  digitalWrite(pirLed4, LOW);

  digitalWrite(ldrRedLed1, LOW);
  digitalWrite(ldrRedLed2, LOW);
}
