int charToInt(int x) { //converts a character to an integer, assuming that the input char is a integer
  int result;
  result = x - '0';
  return result;
}

void reset_rComm() {
  for (i = 0; i < 4; i++) {
    rComm[i] = 0;
  }
  if (verboseDebugSerial == true) {
    Serial.println("Reset rComm");
  }
}

void reset_bComm() {
  for (i = 0; i < 4; i++) {
    bComm[i] = 0;
  }
  if (verboseDebugSerial == true) {
    Serial.println("Reset bComm");
  }
}

void reset_sComm() {
  for (i = 0; i < 4; i++) {
    sComm[i] = 0;
  }
  if (verboseDebugSerial == true) {
    Serial.println("Reset sComm");
  }
}

void prepGenAck_rComm() { //just sets rComm[] = {1,1,1,1}
  rComm[0] = 1;
  rComm[1] = 1;
  rComm[2] = 1;
  rComm[3] = 1;
}

void reset_all_comm() {
  reset_rComm();
  reset_bComm();
  reset_sComm();
}

void waitForNoPress() {
  while ( inputKey != NO_KEY ) {
    inputKey = remoteKeypad.getKey();
  }
}

void runToggleFeature(char key, int targetSetting, int minAllowableSetting, int topAllowableSetting, int page) {
  if (inputKey == key) {
    sSettings[18] = 1; //indicates that a setting has been changed
    ++sSettings[targetSetting];
    if (sSettings[targetSetting] > topAllowableSetting) {
      sSettings[targetSetting] = minAllowableSetting;
    }
    activeSetting(page); //refreshes the screen
  }
}

void runInputPinFeature() {
  if (inputKey) {

    inputKey_int = charToInt(inputKey);

    if ( (inputKey_int >= 0) && (inputKey_int <= 9) ) { //if a number is input

      lcd.print(inputKey_int);
      input_pin[activeColumn] = inputKey_int;

      activeColumn = activeColumn + 1;

      if (activeColumn > 5) { //runs once the user has reached the end of the input field
        activeColumn = 0;
        num_correct_digits = 0;

        Serial.print("input_pin = ");
        for (int y = 0; y < 6; ++y) {
          Serial.print(input_pin[y]);
        }
        Serial.print("\t");
        Serial.print("sysPin = ");
        for (int y = 0; y < 6; ++y) {
          Serial.print(sysPin[y]);
        }

        for (int y = 0; y < 6; ++y) {
          if ( input_pin[y] == sysPin[y] ) {
            ++num_correct_digits;
          }
        }
        Serial.print("\t\t");
        Serial.print("num_correct_digits = ");
        Serial.print(num_correct_digits);
        Serial.print("\n");

        if (num_correct_digits == 6) { //***!!!This defines what happens when the user inputs the correct code******

          switch (mode) {
            case 6: //Arming mode
              activeSetting(31);

              //The following code is used to prepare for runArmingCountdown*****
              setupArmingCountdown();
              delay(10);
              break;

            case 7: //Lock screen mode
              mode = 4;
              changeScreen(4);
              activeSetting(0);
              Serial.println("Leaving lock screen, returning to Remote unarmed Main Menu");
              break;

            case 8: //System armed
              if (activeSettingPage == 35) {
                mode = 4;
                changeScreen(4);
                activeSetting(0);
                Serial.println("Leaving armed mode, returning to Remote unarmed Main Menu");

                //Broadcase that system is disarmed
                rComm[0] = 7;
                rComm[1] = 7;
                rComm[2] = 7;
                rComm[3] = 7;
                noInterruptTransmit_setup(1000);
              }
              break;
          }
        }
        else {
          lcd.setCursor(2, 3);
          lcd.print("<Incorrect pin>");

          lcd.setCursor(7, 1);
          lcd.print("      ");
        }
      }

      i = activeColumn + 7;
      lcd.setCursor(i, 1);
    }

  }
}

void getCombinedrComm() { //used for visual purposes, cuts down on program time for displaying rComm[]
  combined_rComm = ( (1000 * rComm[0]) + (100 * rComm[1]) + (10 * rComm[2]) + rComm[3] );
}
