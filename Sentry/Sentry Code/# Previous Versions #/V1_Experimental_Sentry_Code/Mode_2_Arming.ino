void runArming() {
  displayArmingInfoPage();
  delay(1000);

  executeArmingCountdown();
  delay(2000);

  mode = 3; //surveillance
  activePage = 0;
  lcd.clear();
  Serial.println("Mode: Surveillance (3)");
}


void executeArmingCountdown() {
  lcd.setCursor(1, 1);
  lcd.print("[");

  lcd.setCursor(18, 1);
  lcd.print("]");

  lcd.setCursor(2, 1);

  for (index = 0; index <= 15; ++index) {
    lcd.write(0);
    if (index % 2 == 0) { //Using a modulo operator to determine if index is even
      activateGreenLeds();
    }
    if (index % 2 != 0) {
      deactivateGreenLeds();
    }
    delay(1000);
  }

  lcd.setCursor(7, 2);
  lcd.print("ARMED");
}
