void runSearchForBlackbox() {
  Serial.println("Mode 1: Searching for blackbox");
  transmitAndListen();

  if ( (bComm[0] == 3) && (bComm[1] == 3) && (bComm[2] == 3) && (bComm[3] == 3) ) { //bComm[] == {3,3,3,3}
    reset_rComm();
    reset_bComm();

    mode = 4;
    changeScreen(4);
  }
}

void runSentrySettingsMenu() {
  //***The code below is for basic navigation between different pages of the Sentry menu***
  if (inputKey) {
    run_basic_ui_navigation();
  }

  //***The code below is for logic for what happens on each screen of the Sentry settings menu***
  PIR_pages_logic();
  LDR_pages_logic();
  light_setting_pages_logic();
  alarm_pages_logic();
  annunciator_pages_logic();
  debug_features_pages_logic();
}

void run_basic_ui_navigation() {

  if (mode == 5) { //code for Sentry Settings only
    if (activeSettingPage == 0) {
      inputKey_int = charToInt(inputKey);

      if ( (inputKey_int >= 1) && (inputKey_int <= 9) ) {
        activeSetting(inputKey_int);
        waitForNoPress();
      }

      if (inputKey_int == 0) {
        activeSetting(38);
      }
    }

    if ( (inputKey == 's') && (activeScreen == 5) ) {
      changeScreen(6);
      waitForNoPress();
    }

    if ( (inputKey == 'w') && (activeScreen == 6) ) {
      changeScreen(5);
      waitForNoPress();
    }
  }

  if (mode == 6) { //code for Arming menu only
  }

  //Code for all UI pages past the overall Main Menu (mode == 4)
  if (inputKey == 'a') {
    switch (activeSettingPage) {
      case 0: //no setting selected; Sentry settings main menu
        mode = 4;
        changeScreen(4);
        Serial.println("Main menu selected");
        break;
      case 1: //PIR sensor enable/disable
        changeScreen(5);
        activeSetting(0);
        break;
      case 2: //LDR sensor enable/disable
        changeScreen(5);
        activeSetting(0);
        break;
      case 3: //Light settings main page
        changeScreen(5);
        activeSetting(0);
        break;
      case 4: //Alarms settings main page
        changeScreen(5);
        activeSetting(0);
        break;
      case 5: //Annunciator settings main page
        changeScreen(6);
        activeSetting(0);
        break;
      case 6: //Debug features settings main page
        changeScreen(6);
        activeSetting(0);
        break;
      case 7: //LDR sensor preset sensitivities
        activeSetting(2);
        break;
      case 8: //LDR sensor custom sensitivity
        break;
      case 10: //Indicator Light settings (armed or unarmed)
        activeSetting(3);
        break;
      case 11: //LCD settings (armed or unarmed) selection
        activeSetting(3);
        break;
      case 12: //Exterior lights page
        activeSetting(3);
        break;
      case 13: //LEDs/LCD illumination settings (unarmed)
        activeSetting(lastSetting); //used because the user can get to this setting two different ways
        break;
      case 14: //Indicator Light settings (armed)
        activeSetting(10);
        break;
      case 15: //LCD light settings (armed)
        activeSetting(11);
        break;
      case 16: //Alarm type
        activeSetting(4);
        break;
      case 17: //Active alarm devices
        activeSetting(4);
        break;
      case 18: //Sensor tolerance
        activeSetting(4);
        break;
      case 19: //Active alarm devices >> Annunciator
        activeSetting(lastSetting); //used because the user can get to this setting two different ways
        break;
      case 20: //Active alarm devices >> Alarm clock
        activeSetting(17);
        break;
      case 21: //Active alarm devices >> Beacon light
        activeSetting(17);
        break;

      //setting #22 / screen #28 is now UNUSED (10/24/2023)

      case 23: //Annunciator >> Functions page 1
        activeSetting(5);
        break;
      case 24: //Annunciator >> Functions page 2
        activeSetting(5);
        break;
      case 25: //Annunciator >> Functions >> Arming countdown
        activeSetting(23);
        break;
      case 26: //Annunciator >> Functions >> Trip alert
        activeSetting(23);
        break;
      case 27: //Annunciator >> Functions >> Misc alerts
        activeSetting(24);
        break;
      case 28: //Annunciator >> Functions >> Special alarm
        activeSetting(24);
        break;
      case 29: //Arming menu main page
        mode = 4;
        changeScreen(4);
        activeSetting(0);
        Serial.println("Leaving arming menu, returning to Remote Main Menu");
        break;
      case 30: //Confirm arming
        activeSetting(29);
        break;
      case 35: //Disarm system - alarm not triggered
        activeSetting(33);
        break;

      /* The following settings do not use this function:
          9: LDR sensor custom sensitivity - confirmation
         31: Arming countdown
         32: Arming complete
         33: Armed menu
         34: Lock screen
         44: Transmit Sentry settings
      */

      default:
        Serial.print("Error: have not yet defined a setting for parameter [");
        Serial.print(activeSettingPage);
        Serial.print("] in activeSetting() function. yOu HaVeN't PrOgRaMmEd ThIs FeAtUrE fOr tHiS pAgE iN yEt :(");
        Serial.print("\n");
        break;
    }
    lastSetting = 0;
    waitForNoPress();
  }

  //Transmit settings page
  if ( (mode == 5) && (activeSettingPage == 38) ) {
    if (inputKey) {
      switch (inputKey) {
        case '1':

          if (sSettings[18] == 1) { //if any setting in sSettings has been changed since initiation
            printHourglass(17, 1);
            settingsTransmitProcedure();
            lcd.setCursor(17, 1);
            lcd.print("<");
            lcd.write(8);
            lcd.print(">");
          }

          else {
            lcd.setCursor(14, 1);
            lcd.print("Error ");
          }
          break;

        case '2':
          //save settings to SD
          activeSetting(39);

          Wire.beginTransmission(0xA1); //addressing device 0xA1
          Serial.println("i2c");
          Wire.write(241);
          Wire.endTransmission();

          delay(250);

          Wire.beginTransmission(0xA1);
 
          for (int y; y <= 20; y++) {
            Wire.write(sSettings[y]);
            Serial.println(sSettings[y]);
            delay(10);
          }

          Wire.endTransmission();

          delay(250);

          Wire.beginTransmission(0xA1);
          Wire.write(287);
          Wire.endTransmission();

          /*
                    //then transmit settings
                    delay(500);
                    settingsTransmitProcedure();*/

          //then go back to transmit settings page
          activeSetting(38);
          break;

        case '3':
          changeScreen(6);
          activeSetting(0);
          break;
      }
    }
  }
  //*************************

}

void PIR_pages_logic() {
  //activeSettingPage == 1
  if (activeSettingPage == 1) {
    runToggleFeature('1', 1, 0, 1, 1);
  }
}

void LDR_pages_logic() {
  //activeSettingPage == 2
  if (activeSettingPage == 2) {
    switch (inputKey) {
      case '1': //Toggle whether or not LDR sensors are active

        runToggleFeature('1', 2, 0, 1, 2);
        break;

      case '2':
        activeSetting(7);
        waitForNoPress();
        break;
    }
  }

  //activeSettingPage == 7
  if (activeSettingPage == 7) { //switching to LDR custom sensitivities page
    switch (inputKey) {
      case '2':
        activeSetting(8);
        activeColumn = 0;
        break;
    }
  }

  //activeSettingPage == 8, LDR custom sensitivities page (activeScreen == 14, activeSettingPage == 8)
  while (activeSettingPage == 8) {
    inputKey = remoteKeypad.getKey();

    if (inputKey) {
      if (inputKey == 'N') {  //switching back to LDR preset sensitivity page
        activeSetting(7);
      }

      if (inputKey == 'Y') {
        //Calculate actual custom LDR tolerance:
        customLdrTol[4] = (customLdrTol[0] * 1000) + (customLdrTol[1] * 100) + (customLdrTol[2] * 10) + (customLdrTol[3]);

        waitForNoPress();
        activeSetting(9);
      }

      inputKey_int = charToInt(inputKey);

      if ( (inputKey_int >= 0) && (inputKey_int <= 9) ) {
        //start setting custom LDR sensitivity

        customLdrTol[activeColumn] = inputKey_int;
        Serial.print("ldrCustomTol[");
        Serial.print(activeColumn);
        Serial.print("] = ");
        Serial.print(customLdrTol[activeColumn]);
        Serial.print("\n");

        lcd.print(inputKey_int);

        ++activeColumn;

        if (activeColumn > 3) {
          activeColumn = 0;
        }

        i = 12 + (activeColumn);
        lcd.setCursor(i , 1);
      }
    }
  }

  //activeSettingPage == 9
  if (activeSettingPage == 9) {
    switch (inputKey) {
      case 'Y':
        sSettings[3] = customLdrTol[4];
        sSettings[18] = 1;
        Serial.print("sSettings[3] = ");
        Serial.print(sSettings[3]);
        Serial.print("\t");
        Serial.print("customLdrTol[4] = ");
        Serial.print(customLdrTol[4]);
        Serial.print("\n");
        activeSetting(0);
        changeScreen(5);
        break;

      case 'N':
        activeSetting(8);
        break;
    }
  }
}

void light_setting_pages_logic() {
  if (activeSettingPage == 3) {
    switch (inputKey) {
      case '1': //switching to Indicator LED page
        activeSetting(10);
        waitForNoPress();
        break;

      case '2': //switching to LCD display page
        activeSetting(11);
        waitForNoPress();
        break;

      case '3': //switching to Exterior lights page
        activeSetting(12);
        waitForNoPress();
        break;
    }
  }

  if (activeSettingPage == 10) { //Indicator lights: go to settings for (1)armed or (2)unarmed?
    switch (inputKey) {
      case '1':
        lastSetting = 10;
        activeSetting(13);
        break;

      case '2':
        activeSetting(14);
        break;
    }
    waitForNoPress();
  }

  if (activeSettingPage == 11) { //LCD: go to settings for (1)armed or (2)unarmed?
    switch (inputKey) {
      case '1':
        lastSetting = 11;
        activeSetting(13);
        break;

      case '2':
        activeSetting(15);
        break;
    }
    waitForNoPress();
  }

  if (activeSettingPage == 12) { //Exterior lights settings
    runToggleFeature('1', 7, 0, 2, 12);

  }


  if (activeSettingPage == 13) { //LEDs/LCD illumination settings (unarmed)
    runToggleFeature('1', 6, 0, 1, 13);
  }

  if (activeSettingPage == 14) { //Indicator LED settings (armed)
    runToggleFeature('1', 4, 0, 2, 14);
  }

  if (activeSettingPage == 15) { //LCD illumination settings (armed)
    runToggleFeature('1', 5, 0, 2, 15);
  }
}

void alarm_pages_logic() {
  if (activeSettingPage == 4) { //Alarms settings main page
    if (inputKey) {
      switch (inputKey) {
        case '1':
          activeSetting(16); //Alarm type
          break;
        case '2':
          activeSetting(17); //Active alarm devices
          break;
        case '3':
          activeSetting(18); //Sensor alarm tolerance
          break;
      }
      waitForNoPress();
    }
  }

  if (activeSettingPage == 16) { //Alarm type
    runToggleFeature('1', 8, 0, 1, 16);
  }

  if (activeSettingPage == 17) { //Active alarm devices
    if (inputKey) {
      switch (inputKey) {
        case '1':
          lastSetting = 17;
          activeSetting(19); //Active alarm devices >> Annunciator
          break;
        case '2':
          activeSetting(20); //Active alarm devices >> Alarm clock
          break;
        case '3':
          activeSetting(21); //Active alarm devices >> Beacon light
          break;
      }
      waitForNoPress();
    }
  }

  if (activeSettingPage == 18) { //Sensor alarm tolerance
    runToggleFeature('1', 0, 1, 6, 18);
  }

  if (activeSettingPage == 19) { //Active alarm devices >> Annunciator
    runToggleFeature('1', 9, 0, 1, 19);
  }

  if (activeSettingPage == 20) { //Active alarm devices >> Alarm clock
    runToggleFeature('1', 10, 0, 1, 20);
  }

  if (activeSettingPage == 21) { //Active alarm devices >> Beacon light
    runToggleFeature('1', 11, 0, 1, 21);
  }
}

void annunciator_pages_logic() {
  if (activeSettingPage == 5) { //Annunciator settings main page
    runToggleFeature('1', 12, 0, 1, 5);

    if (inputKey == '2') {
      activeSetting(23); //Annunciator >> Functions page 1
      waitForNoPress();
    }
  }

  if (activeSettingPage == 22) {
    runToggleFeature('1', 12, 0, 1, 5);
  }

  if ( (activeSettingPage == 23) || (activeSettingPage == 24) ) { //Annunciator >> Functions page 1 OR 2
    if (inputKey) {
      switch (inputKey) {
        case '1':
          lastSetting = 23;
          activeSetting(19); //Annunciator >> Functions >> Active alarm devices (annunciator)
          break;
        case '2':
          activeSetting(25); //Annunciator >> Functions >> Arming alerts
          break;
        case '3':
          activeSetting(26); //Annunciator >> Functions >> Trip alert
          break;
        case '4':
          activeSetting(27); //Annunciator >> Functions >> Misc alerts
          break;
        case '5':
          activeSetting(28); //Annunciator >> Functions >> Special alarm
          break;
        case 's':
          if (activeSettingPage != 24) {
            activeSetting(24); //Annunciator >> Functions page 2
          }
          break;
        case 'w':
          if (activeSettingPage != 23) {
            activeSetting(23); //Annunciator >> Functions page 1
          }
          break;
      }
      waitForNoPress();
    }
  }

  if (activeSettingPage == 25) { //Annunciator >> Functions >> Arming countdown
    runToggleFeature('1', 15, 0, 1, 25);
  }

  if (activeSettingPage == 26) { //Annunciator >> Functions >> Trip alert
    runToggleFeature('1', 16, 0, 1, 26);
  }

  if (activeSettingPage == 27) { //Annunciator >> Functions >> Misc alerts
    runToggleFeature('1', 17, 0, 1, 27);
  }

  if (activeSettingPage == 28) { //Annunciator >> Functions >> Special alarm
    runToggleFeature('1', 13, 0, 10, 28);
  }
}

void debug_features_pages_logic() {
  if (activeSettingPage == 6) { //Debug features (main settings page)
    runToggleFeature('1', 14, 0, 1, 6);
  }
}

void runLockScreen() {
  runInputPinFeature();
}

void runArmingMenu() {

  if (inputKey) {
    run_basic_ui_navigation();
  }

  if (activeSettingPage == 29) { //Arming menu main page
    if (inputKey == '1') {
      activeSetting(30);
      activeColumn = 0;
      waitForNoPress();
    }
  }

  if (activeSettingPage == 30) { //Confirm arming page
    runInputPinFeature();
  }

  if (activeSettingPage == 31) { //Arming countdown page
    runArmingCountdown();

    if (inputKey == 'N') {
      digitalWrite(bLed, LOW);
      Serial.println(">> Arming countdown aborted <<");
      activeSetting(29);

      rComm[0] = 5;
      rComm[1] = 2;
      rComm[2] = 5;
      rComm[3] = 2;

      noInterruptTransmit_setup(1000);
      //just transmit without interruption
    }
  }

  if (activeSettingPage == 32) { //Arming complete page
    digitalWrite(bLed, LOW);

    rComm[0] = 5;
    rComm[1] = 3;
    rComm[2] = 5;
    rComm[3] = 3;

    noInterruptTransmit_setup(2000);
    activeSetting(33);
    mode = 8; //switching to Armed mode
  }
}

void setupArmingCountdown() { ////armingCountdownDuration is set in code only under "Settings" before setup(), is the total length of the arming countdown
  countdownTime = armingCountdownDuration + 1; //add one b/c the countdown starts by subtracting one, making it seem like the countdown is a second short
  startMillis == currentMillis + 1000;

  //Transmit that the arming process has started
  rComm[0] = 5;
  rComm[1] = 5;
  rComm[2] = 5;
  rComm[3] = 5;
  getCombinedrComm();

  noInterruptTransmit_setup(1000);
  //just transmit without interruption
}

void runArmingCountdown() {

  //Main countdown device -- countdownTime is the time left in the countdown
  if (currentMillis >= startMillis) {
    startMillis = currentMillis + 1000;
    --countdownTime; //subtract one from countdownTime

    Serial.print("Time remaining == ");
    Serial.print(countdownTime);
    Serial.print("\n");

    lcd.setCursor(16, 1);
    if (countdownTime > 9) {
      lcd.print(countdownTime);
    }
    else {
      lcd.print(" ");
      lcd.print(countdownTime);
    }


    if (countdownTime <= 0) { //what happens when the countdown reaches 0
      activeSetting(32);
    }
  }

  //Cosmetic countdown devices
  if ( (countdownTime % 2) == 0 ) {
    digitalWrite(bLed, HIGH);
  }
  else {
    digitalWrite(bLed, LOW);
  }
}

/*//shows percent remaining of a countdown, works but unused for this program
    percentDone = ((float)countdownTime / (armingCountdownDuration + 1) ) * 100;
    Serial.print("Percent done == ");
    Serial.print(percentDone, 2); //print to 2 digits after the decimal point
    Serial.print("\n");*/
