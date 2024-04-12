void setNewSecurityCode() {
  activeScreen = 1;
  changeScreen();

  index = 0;

  while ( (index) != sysPinLength) {      //this section of code iterates until the number of input chars equals the set length of the system pin length
    inputKey = blackBoxKeypad.getKey();

    if (inputKey) {
      sysPin[index] = charToInt(inputKey); //inputKey is a char variable; need to input an integer to sysPin[], so the charToInt function I created is used
      lcd.print(inputKey);
      ++index;
    }
  }

  activeScreen = 2;
  changeScreen();

  delay(3000);

  if (justInitialized = true) { //if the Blackbox has just been initialized, the comm pin will equal the sys pin. The user can later separately change the comm pin if desired.
    for (i = 0; i < index; i++) {
      commPin[i] = sysPin[i];
    }
  }

  justInitialized = false;

  activeScreen = 0;
  changeScreen();
}

void runTiltSettingSetUp() {
  activeScreen = 4;
  changeScreen();

  while ( (inputKey != 'Y') && (inputKey != 'N') ) {
    inputKey = blackBoxKeypad.getKey();
  }

  if (inputKey == 'Y') {
    tiltAlarmConsideration = true;
    tiltSettingSet = true;
  }

  if (inputKey == 'N') {
    tiltAlarmConsideration = false;
    tiltSettingSet = true;
  }

  Serial.println(tiltAlarmConsideration);

  if (blackBoxReady == true) {
    activeScreen = 0;
  }
  else {
    activeScreen = 3;
  }

  changeScreen();
}
