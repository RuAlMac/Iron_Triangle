void changeScreen(int y) {
  lcd.clear();
  lcd.noBlink();
  activeScreen = y;

  switch (y) {
    case 1:
      lcd.print(">>System Inactive <<");

      lcd.setCursor(6, 1);
      lcd.print("<Remote>");

      lcd.setCursor(4, 2);
      lcd.print("Use Blackbox");

      lcd.setCursor(5, 3);
      lcd.print("for setup.");
      break;

    case 4:
      lcd.print(" Main Menu || XX:XX ");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Sentry Settings");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Lock System");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Arm System");
      break;

    case 5:
      lcd.print("**Sentry Settings **");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Motion sensors");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Light sensors");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Lights");

      lcd.setCursor(14, 3);
      lcd.print("[");
      lcd.write(2); //prints a left arrow
      lcd.print("][");
      lcd.write(1); //prints a down arrow
      lcd.print("]");
      break;

    case 6:
      lcd.print("[4]: Alarm");

      lcd.setCursor(0, 1);
      lcd.print("[5]: Annunciator");

      lcd.setCursor(0, 2);
      lcd.print("[6]: Debug features");

      lcd.setCursor(0, 3);
      lcd.print("[0]: TRANSMIT");

      lcd.setCursor(14, 3);
      lcd.print("[");
      lcd.write(2); //prints a left arrow
      lcd.print("][");
      lcd.write(0); //prints an up arrow
      lcd.print("]");
      break;

    case 7:
      lcd.print(">> Motion Sensors <<");

      switch (sSettings[1]) {
        case 0:
          lcd.setCursor(5, 1);
          lcd.print("[Inactive]");
          break;

        case 1:
          lcd.setCursor(6, 1);
          lcd.print("[Active]");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 8:
      lcd.print(">> Light Sensors  <<");

      if (sSettings[2] == 1) {
        lcd.setCursor(6, 1);
        lcd.print("[Active]");
      }
      else {
        lcd.setCursor(5, 1);
        lcd.print("[Inactive]");
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      lcd.setCursor(0, 3);
      lcd.print("[2]: Sensitivity");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 9:
      lcd.print(">>     Lights     <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Indicator LEDs");

      lcd.setCursor(0, 2);
      lcd.print("[2]: LCD Display");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Ext lights");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 10:
      lcd.print(">>     Alarms     <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Alarm mode");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Alarm devices");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Sensor tols");

      printLeftArrow(17);
      break;

    case 11:
      lcd.print(">>   Annunciator  <<");

      switch (sSettings[12]) {
        case 0:
          lcd.setCursor(5, 1);
          lcd.print("[Inactive]");
          break;

        case 1:
          lcd.setCursor(6, 1);
          lcd.print("[Active]");
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      lcd.setCursor(0, 3);
      lcd.print("[2]: Functions");

      printLeftArrow(17);
      break;

    case 12:
      lcd.print(">> Debug Features <<");

      lcd.setCursor(5, 1);
      switch (sSettings[14]) {
        case 0:
          lcd.print("[Disabled]");
          break;

        case 1:
          lcd.print("[Enabled] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 13:
      lcd.print(">> LDR Tolerances <<");

      lcd.setCursor(3, 1);
      lcd.print("Tolerance: ");
      lcd.print(sSettings[3]);

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle presets");

      lcd.setCursor(0, 3);
      lcd.print("[2]: Custom");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 14:
      lcd.print(">> Custom LDR Tol <<");

      lcd.setCursor(0, 1); // (                    )
      lcd.print("   Custom: [    ]");

      if (customLdrTol[4] != 0) {
        lcd.setCursor(12, 1);

        for (i = 0; i < 4; i++) {
          lcd.print(customLdrTol[i]);
        }
      }

      lcd.setCursor(0, 2);
      lcd.print("[Y]: Accept");

      lcd.setCursor(0, 3);
      lcd.print("[N]: Cancel");

      lcd.setCursor(12, 1);
      lcd.blink();
      break;

    case 15:
      lcd.print(">> Custom LDR Tol <<");

      lcd.setCursor(0, 1);
      lcd.print("   Custom: [");
      for (i = 0; i < 4; i++) {
        lcd.print(customLdrTol[i]);
      }
      lcd.print("]");

      if ( (customLdrTol[4] < 50) || (customLdrTol[4] > 200) ) {
        lcd.setCursor(0, 2);
        lcd.print(" Ideal range 50-200 ");
      }

      lcd.setCursor(0, 3);
      lcd.print(" [Y]/[N]: Confirm?");
      break;

    case 16:
      lcd.print(">> Indicator LEDs <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: When unarmed");

      lcd.setCursor(0, 2);
      lcd.print("[2]: When armed (NS)");

      printLeftArrow(17);
      break;

    case 17:
      lcd.print(">>      LCD       <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: When unarmed");

      lcd.setCursor(0, 2);
      lcd.print("[2]: When armed (NS)");

      printLeftArrow(17);
      break;

    case 18:
      lcd.print(">>Exterior Lights <<");

      lcd.setCursor(1, 1);
      lcd.print("Mode: [");

      switch (sSettings[7]) {
        case 0:
          lcd.print("Off]      ");
          break;

        case 1:
          lcd.print("NS Alarm] ");
          break;

        case 2:
          lcd.print("Always on]");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 19:
      lcd.print(">>LEDs/LCD Unarmed<<");

      lcd.setCursor(5, 1);
      lcd.print("Mode: [");

      if (sSettings[6] == 0) {
        lcd.print("Off]");
      }
      else {
        lcd.print("On] ");
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 20:
      lcd.print(">> Ind LEDs Armed <<");

      lcd.setCursor(3, 1);
      lcd.print("Mode: [");

      switch (sSettings[4]) {
        case 0:
          lcd.print("Off]");
          break;

        case 1:
          lcd.print("On] ");
          break;

        case 2:
          lcd.print("Sensor]  ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17); //prints a left arrow at (col=17,row=3) on the LCD
      break;

    case 21:
      lcd.print(">>   LCD Armed    <<");
      lcd.setCursor(3, 1);
      lcd.print("Display: [");

      switch (sSettings[5]) {
        case 0:
          lcd.print("Off]");
          break;

        default: //for sSetting[5] == 1 or 2
          lcd.print("On] ");
          break;
      }

      lcd.setCursor(2, 2);
      lcd.print("Backlight: [");

      switch (sSettings[5]) {
        default:
          lcd.print("Off]");
          break;

        case 2: //for sSetting[5] == 2
          lcd.print("On] ");
          break;
      }

      lcd.setCursor(0, 3);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 22:
      lcd.print(">>   Alarm Type   <<");

      lcd.setCursor(1, 1);
      lcd.print("Mode: [");

      switch (sSettings[8]) {
        case 0:
          lcd.print("Silent]");
          break;

        case 1:
          lcd.print("Non-Silent]");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 23:
      lcd.print(">> Alarm Devices  <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Annunciator");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Beacon light");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Alarm clock");

      printLeftArrow(17);
      break;

    case 24:
      lcd.print(">>   Sensor Tol   <<");

      lcd.setCursor(3, 1);
      lcd.print("Tolerance: [");
      lcd.print(sSettings[0]);
      lcd.print("]");

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 25:
      lcd.print(">>  Annun Alarm   <<");

      lcd.setCursor(3, 1);
      lcd.print("Mode: [");

      switch (sSettings[9]) {
        case 0:
          lcd.print("Off]");
          break;

        case 1:
          lcd.print("On] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 26:
      lcd.print(">>Alarm Cloc Alarm<<");

      lcd.setCursor(3, 1);
      lcd.print("Mode: [");

      switch (sSettings[10]) {
        case 0:
          lcd.print("Off]");
          break;

        case 1:
          lcd.print("On] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 27:
      lcd.print(">>Beacon Lig Alarm<<");

      lcd.setCursor(3, 1);
      lcd.print("Mode: [");

      switch (sSettings[11]) {
        case 0:
          lcd.print("Off]");
          break;

        case 1:
          lcd.print("On] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    //screen #28 / setting #22 is now UNUSED (10/24/2023)

    case 29:
      lcd.print(">>Annun Functions <<");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Alarm");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Arming Cntdwn");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Trip Alrt");

      lcd.print("[");
      lcd.write(2); //prints a left arrow
      lcd.print("][");
      lcd.write(1); //prints a down arrow
      lcd.print("]");
      break;

    case 30:
      lcd.print("[4]: Misc Alerts");

      lcd.setCursor(0, 1);
      lcd.print("[5]: Special Alarm");

      lcd.setCursor(15, 3);
      lcd.write(2); //prints a left arrow
      lcd.print("][");
      lcd.write(0); //prints an up arrow
      lcd.print("]");
      break;

    case 31:
      lcd.print(">> Arming Cntdwn  <<");

      lcd.setCursor(5, 1);
      switch (sSettings[15]) {
        case 0:
          lcd.print("[Disabled]");
          break;

        case 1:
          lcd.print("[Enabled] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 32:
      lcd.print(">>   Trip Alert   <<");

      lcd.setCursor(5, 1);
      switch (sSettings[16]) {
        case 0:
          lcd.print("[Disabled]");
          break;

        case 1:
          lcd.print("[Enabled] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 33:
      lcd.print(">>  Misc Alerts   <<");

      switch (sSettings[17]) {
        case 0:
          lcd.setCursor(5, 1);
          lcd.print("[Disabled]");
          break;

        case 1:
          lcd.setCursor(5, 1);
          lcd.print("[Enabled] ");
          break;
      }

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 34:
      lcd.print(">> Special Alarm  <<");

      lcd.setCursor(2, 1);
      lcd.print("Likelihood:");

      likelihood_special_alarm = (sSettings[13] * 10);

      if ( (likelihood_special_alarm > 0) && (likelihood_special_alarm < 99) ) {
        lcd.setCursor(15, 1);
      }
      else if (likelihood_special_alarm == 0) {
        lcd.setCursor(16, 1);
      }
      else {
        lcd.setCursor(14, 1);
      }

      lcd.print(likelihood_special_alarm);
      lcd.print("%");

      lcd.setCursor(0, 2);
      lcd.print("[1]: Toggle");

      printLeftArrow(17);
      break;

    case 35: //Arming menu
      lcd.print("**  Arming Menu   **");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Arm system");

      lcd.setCursor(0, 3);

      switch (sSettings[8]) {
        case 0:
          lcd.print("Silent");
          break;

        case 1:
          lcd.print("Non-Silent");
          break;
      }

      lcd.setCursor(11, 3);
      lcd.print("<");
      lcd.print(sSettings[0]);
      lcd.print(">");

      printLeftArrow(17);
      break;

    case 36: //Confirm arming
      lcd.print(">> Confirm arming <<");

      lcd.setCursor(6, 1);
      lcd.print("[      ]");

      lcd.setCursor(2, 2);
      lcd.print("Input system pin");

      printLeftArrow(17);

      lcd.setCursor(7, 1);
      lcd.blink();
      break;

    case 37: //Arming countdown
      lcd.print("*******ARMING*******");

      lcd.setCursor(0, 1);
      lcd.print("Time Remaining: ");

      lcd.setCursor(4, 3);
      lcd.print("[N]: Cancel");
      break;

    case 38: //Arming complete
      lcd.print("**Arming Complete **");

      lcd.setCursor(3, 1);
      lcd.print("Switching to");

      lcd.setCursor(3, 2);
      lcd.print("Armed menu.");
      break;

    case 39: //Armed menu
      lcd.print("**   Armed Menu   **");

      lcd.setCursor(0, 1);
      lcd.print("Status: <Normal>");

      lcd.setCursor(0, 2);
      lcd.print("[1]: Disarm system");
      break;

    case 40: //Lock screen
      lcd.write(4); //prints a padlock

      lcd.setCursor(3, 0);
      lcd.print("System Locked");

      lcd.setCursor(19, 0);
      lcd.write(4);

      lcd.setCursor(6, 1);
      lcd.print("[      ]");

      lcd.setCursor(2, 2);
      lcd.print("Input system pin");

      lcd.setCursor(0, 3);
      lcd.write(4);

      lcd.setCursor(19, 3);
      lcd.write(4);

      lcd.setCursor(7, 1);
      lcd.blink();
      break;
    case 41: //Disarm system - alarm not tripped
      lcd.print(">> Disarm System  <<");

      lcd.setCursor(0, 1);
      lcd.write(6);
      lcd.write(6);

      lcd.setCursor(18, 1);
      lcd.write(6);
      lcd.write(6);

      lcd.setCursor(6, 1);
      lcd.print("[      ]");

      lcd.setCursor(2, 2);
      lcd.print("Input system pin");

      printLeftArrow(17);

      lcd.setCursor(7, 1);
      lcd.blink();
      break;
    case 42: //Disarm system - alarm tripped
      lcd.print("!! SYSTEM TRIPPED !!");

      lcd.setCursor(6, 1);
      lcd.print("[      ]");

      lcd.setCursor(2, 2);
      lcd.print("Input system pin");

      lcd.setCursor(0, 3);
      lcd.print("Time Left: ");
      break;
    case 44: //Transmit Sentry settings
      lcd.print("TRANSMIT SENTRY SETT");

      lcd.setCursor(0, 1);
      lcd.print("[1]: Transmit");

      lcd.setCursor(0, 2);
      lcd.print("[2]: Make default");

      lcd.setCursor(0, 3);
      lcd.print("[3]: Cancel");
      break;

    case 45: //Set new default settings (send settings to SD card)
      lcd.print(">>Setting Defaults<<");

      lcd.setCursor(1, 1);
      lcd.print("Saving setts to SD");

      lcd.setCursor(0, 2);
      lcd.print("Will transmit setts");

      lcd.setCursor(0, 3);
      lcd.print("Status: [");
      lcd.write(5);
      lcd.print("]");
      break;

    default: //input parameter does not have a setting assigned to it; error
      lcd.print("Error: Unknown input");

      lcd.setCursor(0, 1);
      lcd.print("[");
      lcd.print(y);
      lcd.print("]");

      lcd.setCursor(0, 2);
      lcd.print("in changeScreen()");

      Serial.print("Error: have not yet defined a setting for parameter [");
      Serial.print(y);
      Serial.print("] in changeScreen() function.");
      Serial.print("\n");
      break;
  }

  if (verboseDebugSerial == true) {
    Serial.print("Active screen == ");
    Serial.print(activeScreen);
    Serial.print("\n");
  }
}

void activeSetting(int y) { //used in pair with the variable "activeSettingPage", used to simplify code, used only to switch between different pages, not for if statements
  activeSettingPage = y;
  switch (y) {
    case 0: //no setting actively selected
      //do nothing
      break;
    case 1: //PIR sensor enable/disable
      changeScreen(7);
      break;
    case 2: //LDR sensor enable/disable
      changeScreen(8);
      break;
    case 3: //Light settings
      changeScreen(9);
      break;
    case 4: //Alarm settings
      changeScreen(10);
      break;
    case 5: //Annunciator settings
      changeScreen(11);
      break;
    case 6: //Debug feature settings
      changeScreen(12);
      break;
    case 7: //LDR sensor preset sensitivity settings
      changeScreen(13);
      break;
    case 8: //LDR sensor custom sensitivity settings
      changeScreen(14);
      break;
    case 9: //LDR sensor custom sensitivity confirmation page
      changeScreen(15);
      break;
    case 10: //Indicator light settings: select which settings to go to (armed or unarmed)
      changeScreen(16);
      break;
    case 11: //LCD: select which settings to go to (armed or unarmed)
      changeScreen(17);
      break;
    case 12: //Exterior lights settings
      changeScreen(18);
      break;
    case 13: //LED & LCD illumination settings for when unarmed
      changeScreen(19);
      break;
    case 14: //Indicator light settings for when armed
      changeScreen(20);
      break;
    case 15: //LCD light settings for when armed
      changeScreen(21);
      break;
    case 16: //Alarm type
      changeScreen(22);
      break;
    case 17: //Active alarm devices
      changeScreen(23);
      break;
    case 18: //Sensor tolerance
      changeScreen(24);
      break;
    case 19: //Active alarm devices >> Annunciator
      changeScreen(25);
      break;
    case 20: //Active alarm devices >> Alarm clock
      changeScreen(26);
      break;
    case 21: //Active alarm devices >> Beacon light
      changeScreen(27);
      break;

    //setting #22 / screen #28 is now UNUSED (10/24/2023)

    case 23: //Annunciator >> Functions page 1
      changeScreen(29);
      break;
    case 24: //Annunciator >> Functions page 2
      changeScreen(30);
      break;
    case 25: //Annunciator >> Functions >> Arming alerts
      changeScreen(31);
      break;
    case 26: //Annunciator >> Functions >> Trip alert
      changeScreen(32);
      break;
    case 27: //Annunciator >> Functions >> Misc alerts
      changeScreen(33);
      break;
    case 28: //Annunciator >> Functions >> Special alarm
      changeScreen(34);
      break;
    case 29: //Arming menu
      changeScreen(35);
      break;
    case 30: //Confirm arming
      changeScreen(36);
      break;
    case 31: //Arming countdown
      changeScreen(37);
      break;
    case 32: //Arming complete
      changeScreen(38);
      break;
    case 33: //Armed menu
      changeScreen(39);
      break;
    case 34: //Lock screen
      changeScreen(40);
      break;
    case 35: //Disarm system - alarm not triggered
      changeScreen(41);
      break;
    case 36: //Disarm system - alarm tripped
      changeScreen(42);
      break;
    case 37: //Alarm triggered
      changeScreen(43);
      break;
    case 38: //Transmit Sentry settings
      changeScreen(44);
      break;
    case 39: //Set new default settings (send settings to SD card)
      changeScreen(45);
      break;
    default: //input parameter does not have a setting assigned to it; error
      Serial.print("Error: have not yet defined a setting for parameter [");
      Serial.print(y);
      Serial.print("] in activeSetting() function.");
      Serial.print("\n");
      break;
  }

  if (verboseDebugSerial == true) {
    Serial.print("activeSettingPage == ");
    Serial.print(activeSettingPage);
    Serial.print("\n");
  }
}

void printLeftArrow(int y) { //prints a left arrow surrounded by brackets on row 3 at column y of the LCD
  lcd.setCursor(y, 3);
  lcd.print("[");
  lcd.write(2); //prints a left arrow
  lcd.print("]");
}

void printHourglass(int col, int row) { //prints "<hourglass>" starting at lcd.setCursor(col, row)
  lcd.setCursor(col, row);
  lcd.print("<");
  lcd.write(5); //prints an hourglass
  lcd.print(">");
}
