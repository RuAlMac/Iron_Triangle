void runBlackBoxPrep() {
  inputKey = blackBoxKeypad.getKey();

  if ( (inputKey == '1') && (activeScreen != 3) ) {
    inputKey = 0;

    activeScreen = 3;
    changeScreen();
  }

  if ( (activeScreen == 3) && (inputKey == '1') ) {
    runTiltSettingSetUp();
  }

  if ( (activeScreen == 3) && (inputKey == '2') ) {
    currentColumn = 1;
    runClockSetUp();
  }

  if ( (activeScreen == 3) && (tiltSettingSet == true) && (sysClockSet == true) ) {
    blackBoxReady = true;
    inputKey = 'z';
    activeScreen = 0;
    changeScreen();
    digitalWrite(rLed, LOW);
    digitalWrite(gLed, HIGH);

    delay(1000);
    digitalWrite(gLed, LOW);
  }
}

void runMainMenu() {
  inputKey = blackBoxKeypad.getKey();

  if (inputKey == '1') {
    armingMode = true;
    activeScreen = 6;
    changeScreen();
    digitalWrite(bLed, HIGH);
  }

  if (inputKey == '2') {
    runTiltSettingSetUp();
  }

  if (inputKey == '3') {
    sysClockSet = false;
    runClockSetUp();
  }
}

void runReadyToArm() {
  inputKey = blackBoxKeypad.getKey();
  if (inputKey == 'N') {
    armingMode = false;
    digitalWrite(bLed, LOW);

    activeScreen = 0;
    changeScreen();
  }
//*************************************************Testing I2C code, remove before using Iron Triangle system in regular function
  if (inputKey == '2') {
    I2C_value = 2;
    Wire.beginTransmission(slaveAddress); // transmit to slave device
    Wire.write(I2C_value);              // sends x
    Wire.endTransmission();    // stop transmitting
  }

  if (inputKey == '3') {
    I2C_value = 3;
    Wire.beginTransmission(slaveAddress); // transmit to slave device
    Wire.write(I2C_value);              // sends x
    Wire.endTransmission();    // stop transmitting
  }
}
