void displayConfigInfoPage() {
  lcd.setCursor(0, 0);
  lcd.print("Mode: Config        ");

  lcd.setCursor(0, 1);
  lcd.print("Set system settings ");

  lcd.setCursor(0, 2);
  lcd.print("Navigate w/ Buttons ");

  lcd.setCursor(0, 3);
  lcd.print("              --->  ");
}

void updateConfigScreen() {

  if (activePage == 1) {
    lcd.setCursor(0, 1);
    lcd.print("Set LDR #1 Tolerance");

    lcd.setCursor(0, 2);
    lcd.print("Use knob");

    lcd.setCursor(0, 3);
    lcd.print("[tolerance1 level]  ");
  }

  if (activePage == 2) {
    lcd.setCursor(0, 1);
    lcd.print("Set LDR #2 Tolerance");

    lcd.setCursor(0, 2);
    lcd.print("Use knob");

    lcd.setCursor(0, 3);
    lcd.print("[tolerance2 level]  ");
  }

  if (activePage == 3) {
    lcd.setCursor(0, 1);
    lcd.print("Loud / Silent Alarm ");

    lcd.setCursor(0, 2);
    lcd.print("Use select button   ");

    lcd.setCursor(0, 3);
    lcd.print("[alarm mode]        ");
  }

  if (activePage == 4) {
    lcd.setCursor(0, 1);
    lcd.print("Set alarm tolerance ");

    lcd.setCursor(0, 2);
    lcd.print("Use select button   ");

    lcd.setCursor(0, 3);
    lcd.print("[A tolerance level  ");
  }

  if (activePage == 5) {
    lcd.setCursor(0, 1);
    lcd.print("Press 'Next'        ");

    lcd.setCursor(0, 2);
    lcd.print("To set system to    ");

    lcd.setCursor(0, 3);
    lcd.print("Active              ");
  }
}

void updateReadyScreen() {
  if (activePage == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Mode: Ready       ");

    lcd.setCursor(0, 1);
    lcd.print("To arm, press 'next'");

    lcd.setCursor(0, 2);
    lcd.print("                    ");

    lcd.setCursor(0, 3);
    lcd.print("Arm length 15 sec   ");
  }

  if (activePage == 1) {
    lcd.setCursor(0, 1);
    lcd.print("Press 'Next' to     ");

    lcd.setCursor(0, 2);
    lcd.print("confirm Arming      ");

    lcd.setCursor(0, 3);
    lcd.print("  <---        --->  ");

  }
}

void displayArmingInfoPage() {
  lcd.setCursor(0, 0);
  lcd.print("***SYSTEM**ARMING***");

  lcd.setCursor(0, 1);
  lcd.print("*");

  lcd.setCursor(19, 1);
  lcd.print("*");

  lcd.setCursor(0, 2);
  lcd.print("*");

  lcd.setCursor(19, 2);
  lcd.print("*");

  lcd.setCursor(0, 3);
  lcd.print("********************");
}

void displayNSInfoPage() {
  lcd.setCursor(0, 0);
  lcd.print("Mode: Non-S Surveil ");
}

void displayNSAlarmPage() {
  lcd.setCursor(0, 1);
  lcd.print("       ALARM        ");

  lcd.setCursor(0, 2);
  lcd.print("     TRIGGERED      ");
}

void displayAlarmLevel() {
  setupAlarmLevelDisplay();
  //Updating the displayed alarm level for non-0 alarmLevel values
  if (alarmLevel == 1) {
    lcd.setCursor(14, 3);
    lcd.write(0);
  }

  if (alarmLevel == 2) {
    lcd.setCursor(14, 3);
    lcd.write(0);
    lcd.write(0);
  }

  if (alarmLevel == 3) {
    lcd.setCursor(14, 3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
  }

  if (alarmLevel == 4) {
    lcd.setCursor(14, 3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
  }

  if (alarmLevel == 5) {
    lcd.setCursor(14, 3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
  }
}

void setupAlarmLevelDisplay() {
  if (alarmLevel == 0) {
    lcd.setCursor(0, 3);
    lcd.print("Alarm Level:        ");
  }

  //Setting up the Alarm Level display for non-0 alarmLevel values
  if (alarmLevel != 0) {
    lcd.setCursor(0, 3);
    lcd.print("Alarm Level: (");

    if (maxAlarmLevel == 2) {
      lcd.setCursor(16, 3);
      lcd.print(")");
    }

    if (maxAlarmLevel == 3) {
      lcd.setCursor(17, 3);
      lcd.print(")");
    }

    if (maxAlarmLevel == 4) {
      lcd.setCursor(18, 3);
      lcd.print(")");
    }

    if (maxAlarmLevel == 5) {
      lcd.setCursor(19, 3);
      lcd.print(")");
    }
  }
}
