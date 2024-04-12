void runConfig() {
  if (activePage == 0 && activePage != 6) {
    displayConfigInfoPage();
  }

  if ((digitalRead(tempButton1) == LOW) && activePage != 0) {
    activePage = activePage - 1;
    while (digitalRead(tempButton1) == LOW) {
      //do nothing
    }
    updateConfigScreen();
  }

  if (digitalRead(tempButton3) == LOW) {
    activePage = activePage + 1;
    while (digitalRead(tempButton3) == LOW) {
      //do nothing
    }
    updateConfigScreen();
  }

  delay(20);

  if (activePage == 6) { //Change Mode to Ready (1)
    mode = 1;
    activePage = 0;
    lcd.clear();
    Serial.println("Mode: Ready (1)");
  }
}
