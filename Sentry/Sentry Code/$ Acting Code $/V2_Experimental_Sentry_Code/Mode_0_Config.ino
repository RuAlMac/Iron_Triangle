void runConfig() {
  deactivateGreenLeds();
  
  if (activePage == 0 && activePage != 6) {
    displayConfigInfoPage();
  }

  if ( (digitalRead(tempButton1) == LOW || (buttonSelected == 1) ) && activePage != 0) {
    activePage = activePage - 1;
    resetButtonSelect(); //(reset of selected button for NRF functionality
    while (digitalRead(tempButton1) == LOW) {
      //do nothing
    }
    updateConfigScreen();
  }

  if ( (digitalRead(tempButton3) == LOW) || (buttonSelected == 3) ) {
    activePage = activePage + 1;
    resetButtonSelect(); //(reset of selected button for NRF functionality
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
    Serial.print("\n");
    Serial.print("Mode: Ready (1)");
  }
}
