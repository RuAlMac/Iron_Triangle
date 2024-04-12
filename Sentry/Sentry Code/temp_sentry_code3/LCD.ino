void changeScreen(int activeScreen) {
  lcd.clear();
  lcd.noBlink();

  switch (activeScreen) {
    case 1: //Searching for Blackbox
      lcd.print(">>System Inactive <<");

      lcd.setCursor(6, 1);
      lcd.print("<Sentry>");

      lcd.setCursor(4, 2);
      lcd.print("Use Blackbox");

      lcd.setCursor(5, 3);
      lcd.print("for setup.");
      break;

    case 2:
      lcd.print("**  Sentry Ready  **");

      lcd.setCursor(1, 1);
      lcd.print("Status: [Unarmed]");

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
      lcd.print(sSettings[19]);
      lcd.print(">");

      lcd.setCursor(15, 3);
      lcd.print("XX:XX");
      break;

    case 3:
      lcd.print(">>  New Settings  <<");

      lcd.setCursor(0, 1);
      lcd.print(" Getting updates... ");

      lcd.setCursor(4, 2);
      lcd.print("Status: [");
      lcd.write(0);
      lcd.print("]");

      lcd.setCursor(0, 3);
      lcd.print("   Setting:   /20   ");
      break;
  }
}

void activeSetting(int y) {
  activeSettingPage = y;
  switch (y) {
    case 1:
      changeScreen(1);
      break;
    case 2:
      changeScreen(2);
      break;
    case 3:
      changeScreen(3);
      break;
  }
}
