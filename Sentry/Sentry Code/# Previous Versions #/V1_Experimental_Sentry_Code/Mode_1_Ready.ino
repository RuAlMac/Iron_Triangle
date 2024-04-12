void runReady() {
  activateGreenLeds();
  
  if (activePage == 0) {
    updateReadyScreen();
  }

  if ((digitalRead(tempButton1) == LOW) && activePage != 0) {
    activePage = activePage - 1;
    while (digitalRead(tempButton1) == LOW) {
      //do nothing
    }
    updateReadyScreen();
  }

  if (digitalRead(tempButton3) == LOW) {
    activePage = activePage + 1;
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
    Serial.println("Mode: Arming (2)"); //REVERT TO CORRECT MESSAGE AFTER PROTOTYPING
  }
}
