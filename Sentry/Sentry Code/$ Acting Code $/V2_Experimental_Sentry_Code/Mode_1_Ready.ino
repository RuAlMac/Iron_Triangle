void runReady() {
  activateGreenLeds();

  if (activePage == 0) {
    updateReadyScreen();
  }

  if ( ( (digitalRead(tempButton1) == LOW) || (buttonSelected == 1) ) && activePage == 0) { //To return to the Config pages
    mode = 0;
    activePage = 0;
    lcd.clear();
    Serial.print("\n");
    Serial.print("Mode: Config (0)");
  }

  if ( ( (digitalRead(tempButton1) == LOW) || (buttonSelected == 1) ) && activePage != 0) {
    activePage = activePage - 1;
    resetButtonSelect();
    while (digitalRead(tempButton1) == LOW) {
      //do nothing
    }
    updateReadyScreen();
  }

  if ( (digitalRead(tempButton3) == LOW) || (buttonSelected == 3) ) {
    activePage = activePage + 1;
    resetButtonSelect();
    while (digitalRead(tempButton3) == LOW) {
      //do nothing
    }
    updateReadyScreen();
  }

  delay(20);

  if (activePage == 2) { //Change Mode to Ready (1)
    mode = 2;
    activePage = 0;
    lcd.clear();
    Serial.print("\n");
    Serial.print("Mode: Arming (2)");
  }
}
