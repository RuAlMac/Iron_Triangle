void setNewSecurityCode() {
  changeScreen(1);

  index = 0;

  while ( (index) != sysPinLength) {      //this section of code iterates until the number of input chars equals the set length of the system pin length
    inputKey = blackBoxKeypad.getKey();

    if (inputKey) {
      sysPin[index] = charToInt(inputKey); //inputKey is a char variable; need to input an integer to sysPin[], so the charToInt function I created is used
      lcd.print(inputKey);
      ++index;
    }
  }

  Serial.print("System pin set: ");
  for ( i = 0; i < index; i++) {
    Serial.print(sysPin[i]);
  }
  Serial.print("\n");

  changeScreen(2);
  index = 0;

  delay(3000);

  justInitialized = false;

  changeScreen(0);
}

void runTiltSettingSetUp() {
  changeScreen(4);

  while ( (inputKey != 'Y') && (inputKey != 'N') ) {
    inputKey = blackBoxKeypad.getKey();
  }

  if (inputKey == 'Y') {
    tiltAlarmConsideration = true;
    tiltSettingSet = true;
    Serial.println("Tilt switch WILL trigger alarm");
  }

  if (inputKey == 'N') {
    tiltAlarmConsideration = false;
    tiltSettingSet = true;
    Serial.println("Tilt switch WILL NOT trigger alarm");
  }

  if (blackBoxReady == true) {
    changeScreen(0);
  }
  else {
    changeScreen(3);
  }
}
