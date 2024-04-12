void checkPirSensor1() {
  if ( (digitalRead(pir1) == HIGH) && (pir1State == false) ) {
    digitalWrite(pirLed1, HIGH);
    pir1Led = true;
    pir1State = true;
    alarmLevel = alarmLevel + 1;
    Serial.print("\n");
    Serial.print("PIR 1: Motion Detected");
  }

  if (pir1State == true) {

    if (digitalRead(pir1) == LOW) {
      pir1State = false;
      alarmLevel = alarmLevel - 1;
      Serial.print("\n");
      Serial.print("PIR 1: Motion Stopped");
    }
  }

  if ( (digitalRead(pir1) == LOW) && (pir1State == false) ) {
    digitalWrite(pirLed1, LOW);
    pir1Led = false;
  }
}

void checkPirSensor2() {
  if ( (digitalRead(pir2) == HIGH) && (pir2State == false) ) {
    digitalWrite(pirLed2, HIGH);
    pir2Led = true;
    pir2State = true;
    alarmLevel = alarmLevel + 1;
    Serial.print("\n");
    Serial.print("PIR 2: Motion Detected");
  }

  if (pir2State == true) {

    if (digitalRead(pir2) == LOW) {
      pir2State = false;
      alarmLevel = alarmLevel - 1;
      Serial.print("\n");
      Serial.print("PIR 2: Motion Stopped");
    }
  }

  if ( (digitalRead(pir2) == LOW) && (pir2State == false) ) {
    digitalWrite(pirLed2, LOW);
    pir2Led = false;
  }
}

void checkPirSensor3() {
  if ( (digitalRead(pir3) == HIGH) && (pir3State == false) ) {
    digitalWrite(pirLed3, HIGH);
    pir3Led = true;
    pir3State = true;
    alarmLevel = alarmLevel + 1;
    Serial.print("\n");
    Serial.print("PIR 3: Motion Detected");
  }

  if (pir3State == true) {

    if (digitalRead(pir3) == LOW) {
      pir3State = false;
      alarmLevel = alarmLevel - 1;
      Serial.print("\n");
      Serial.print("PIR 3: Motion Stopped");
    }
  }

  if ( (digitalRead(pir3) == LOW) && (pir3State == false) ) {
    digitalWrite(pirLed3, LOW);
    pir3Led = false;
  }
}

void checkPirSensor4() {
  if ( (digitalRead(pir4) == HIGH) && (pir4State == false) ) {
    digitalWrite(pirLed4, HIGH);
    pir4Led = true;
    pir4State = true;
    alarmLevel = alarmLevel + 1;
    Serial.print("\n");
    Serial.print("PIR 4: Motion Detected");
  }

  if (pir4State == true) {

    if (digitalRead(pir4) == LOW) {
      pir4State = false;
      alarmLevel = alarmLevel - 1;
      Serial.print("\n");
      Serial.print("PIR 4: Motion Stopped");
    }
  }

  if ( (digitalRead(pir4) == LOW) && (pir4State == false) ) {
    digitalWrite(pirLed4, LOW);
    pir4Led = false;
  }
}

void updateExternalPirLeds(){
  //PIR Led 1
  if (pir1Led == true){
    digitalWrite(redLed1, HIGH);
  }

  if (pir1Led == false){
    digitalWrite(redLed1, LOW);
  }

//PIR Led 2
 if (pir2Led == true){
    digitalWrite(redLed2, HIGH);
  }

  if (pir2Led == false){
    digitalWrite(redLed2, LOW);
  }

//PIR Led 3
  if (pir3Led == true){
    digitalWrite(redLed3, HIGH);
  }

  if (pir3Led == false){
    digitalWrite(redLed3, LOW);
  }

//PIR Led 4
  if (pir4Led == true){
    digitalWrite(redLed4, HIGH);
  }

  if (pir4Led == false){
    digitalWrite(redLed4, LOW);
  }
}
