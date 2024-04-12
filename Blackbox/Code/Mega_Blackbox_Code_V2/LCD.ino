void changeScreen(int y) {
  activeScreen = y;
  lcd.clear();
  lcd.noBlink();

  switch (activeScreen) {
    case 0:
      lcd.print("*****Main  Menu*****");

      if (blackBoxReady == false) {
        lcd.setCursor(0, 1);
        lcd.print("Blackbox NOT READY");

        lcd.setCursor(0, 2);
        lcd.print("[1]: View remaining");

        lcd.setCursor(5, 3);
        lcd.print("tasks");
      }

      if (blackBoxReady == true) {
        lcd.setCursor(0, 1);
        lcd.print("[1]: Activate system");

        lcd.setCursor(0, 2);
        lcd.print("[2]: Tilt setting");
      }
      break;

    case 1:
      lcd.print("Set new system pin:");

      lcd.setCursor(0, 1);
      lcd.print("[");

      lcd.setCursor(1 + sysPinLength, 1);
      lcd.print("]");

      lcd.setCursor(1, 1);
      lcd.blink();
      break;
    case 2:
      lcd.print("New system pin set:");

      lcd.setCursor(0, 1);
      lcd.print("[");

      for (i = 0; i < index; i++) {
        lcd.print(sysPin[i]);
      }

      lcd.print("]");
      break;
    case 3:
      if (tiltSettingSet == false) {
        lcd.setCursor(0, 0);
        lcd.print("[1] Set tilt setting");
      }
      break;
    case 4:
      lcd.print("Should Blackbox tilt");

      lcd.setCursor(0, 1);
      lcd.print("switch trip alarm?");

      lcd.setCursor(0, 3);
      lcd.print("Yes: [Y]  No: [N]");
      break;
    case 5: //Searching for Blackbox and Sentry page
      lcd.print("**Checking Devices**");

      lcd.setCursor(0, 1);
      lcd.print("Remote: <X>");

      lcd.setCursor(0, 2);
      lcd.print("Sentry: <X>");

      lcd.setCursor(0, 3);
      lcd.print("[N]: Cancel");
      break;

    case 6:
      lcd.print("**    Blackbox    **");

      lcd.setCursor(0, 1);
      lcd.print("Data Recording Mode");

      lcd.setCursor(0, 3);
      lcd.print("[0]: R.U.D.");
      break;
  }
}
