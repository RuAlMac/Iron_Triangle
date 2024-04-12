void changeScreen() {
  lcd.clear();
  lcd.noBlink();

  if (activeScreen == 0) {
    lcd.print("*****Main  Menu*****");

    if (blackBoxReady == false){
      lcd.setCursor(0,1);
      lcd.print("Blackbox NOT READY");

      lcd.setCursor(0,2);
      lcd.print("[1]: View remaining");

      lcd.setCursor(5,3);
      lcd.print("tasks");
    }

    if (blackBoxReady == true){
      lcd.setCursor(0,1);
      lcd.print("[1] Prep for arming");

      lcd.setCursor(0,2);
      lcd.print("[2] Tilt setting");

      lcd.setCursor(0,3);
      lcd.print("[3] Set clock");
    }
  }

  if (activeScreen == 1) {
    lcd.print("Set new system pin:");

    lcd.setCursor(0, 1);
    lcd.print("[");

    lcd.setCursor(1 + sysPinLength, 1);
    lcd.print("]");

    lcd.setCursor(1, 1);
    lcd.blink();
  }

  if (activeScreen == 2) {
    lcd.noBlink();
    lcd.print("New system pin set:");

    lcd.setCursor(0, 1);
    lcd.print("[");

    for (i = 0; i < index; i++) {
      lcd.print(sysPin[i]);
    }

    lcd.print("]");

    if (justInitialized == true) {
      lcd.setCursor(0, 2);
      lcd.print("By default, comm pin");

      lcd.setCursor(0, 3);
      lcd.print("currently = sys pin");
    }
  }

  if (activeScreen == 3){
    if (tiltSettingSet == false){
      lcd.setCursor(0,0);
      lcd.print("[1] Set tilt setting");
    }

    if (sysClockSet == false){
      lcd.setCursor(0,1);
      lcd.print("[2] Set sys clock");
    }
  }

  if (activeScreen == 4){
    lcd.print("Should Blackbox tilt");

    lcd.setCursor(0,1);
    lcd.print("switch trip alarm?");

    lcd.setCursor(0,3);
    lcd.print("Yes: [Y]  No: [N]");
  }

  if (activeScreen == 5){
    lcd.print("Set current time:");

    lcd.setCursor(0,1);
    lcd.print("[");

    lcd.setCursor(3,1);
    lcd.print(":");

    lcd.setCursor(6,1);
    lcd.print("]");

    lcd.setCursor(0,2);
    lcd.print("Use 24-hr time,");

    lcd.setCursor(0,3);
    lcd.print("press [Y] to set");

    lcd.setCursor(1,1);
    lcd.blink();
  }

  if (activeScreen == 6){
    lcd.print("Searching for");

    lcd.setCursor(0,1);
    lcd.print("Remote...");

    lcd.setCursor(0,3);
    lcd.print("[N] Go back");
  }
}
