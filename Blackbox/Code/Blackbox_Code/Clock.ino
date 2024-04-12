void runClockSetUp() {
  inputKey = 'z';
  activeScreen = 5;
  changeScreen();

  while (sysClockSet == false) {

    inputKey = blackBoxKeypad.getKey();

    if (inputKey) {

      if ( (inputKey == '1') ||  (inputKey == '2') || (inputKey == '3') || (inputKey == '4') || (inputKey == '5') || (inputKey == '6') || (inputKey == '7') || (inputKey == '8') || (inputKey == '9') || (inputKey == '0') ) {

        if (currentColumn == 5) {
          minute[1] = charToInt(inputKey);
          lcd.print(inputKey);
          currentColumn++;
        }

        if (currentColumn == 4) {
          minute[0] = charToInt(inputKey);
          lcd.print(inputKey);
          currentColumn++;
        }

        if (currentColumn == 2) {
          hour[1] = charToInt(inputKey);
          lcd.print(inputKey);
          lcd.setCursor(4, 1);
          currentColumn = 4;
        }

        if (currentColumn == 1) {
          hour[0] = charToInt(inputKey);
          lcd.print(inputKey);
          currentColumn++;
        }
      }

      if (currentColumn == 6) {
        resetClockCursor();
      }

      if (inputKey == 'Y') { //check to make sure input time is valid
        computedTime[0] = ( (hour[0] * 10) + hour[1] );
        computedTime[1] = ( (minute[0] * 10) + minute[1] );

        Serial.println(computedTime[0]);
        Serial.println(computedTime[1]);

        if ( (computedTime[0] >= 0) && (computedTime[0] < 24) && (computedTime[1] >= 0) && (computedTime[1] < 60) ) {
          sysClockSet = true;
        }
        else {
          lcd.setCursor(11, 1);
          lcd.print("Invalid");
          resetClockCursor();
        }
      }
    }
  }

  if (blackBoxReady == true) {
    activeScreen = 0;
  }
  else {
    activeScreen = 3;
  }

  changeScreen();
}

void resetClockCursor() {
  currentColumn = 1;
  lcd.setCursor(1, 1);
}

void runSysClock() {
  if (sysClockSet == true) {
    currentMillis = millis();

    if (currentMillis == startMillis + 1000) {
      startMillis = currentMillis;
      second[1] = second[1] + 1;

      if (second[1] > 9) { //00:00:10
        second[1] = 0;
        second[0] = second[0] + 1;
      }

      if (second[0] > 5) { //00:01:00
        second[0] = 0;
        minute[1] = minute[1] + 1;
      }

      if (minute[1] > 9) { //00:10:00
        minute[1] = 0;
        minute[0] = minute[0] + 1;
      }

      if (minute[0] > 5) { //01:00:00
        minute[0] = 0;
        hour[1] = hour[1] + 1;
      }

      if (hour[1] > 9) { //10:00:00
        hour[1] = 0;
        hour[0] = hour[0] + 1;
      }

      if ( (hour[0] == 2) && (hour[1] == 4) ) {
        day = day + 1;
        setTimeToZero(); //reset clock, start from midnight
      }

      printCurrentTime();
      indicateClockUpdate(); //used for code that should run every x seconds
    }
  }
}

void setTimeToZero() {
  second[1] = 0;
  second[0] = 0;
  minute[1] = 0;
  minute[0] = 0;
  hour[1] = 0;
  hour[0] = 0;
}

void printCurrentTime() {
  Serial.print("The current time is: ");
  Serial.print(hour[0]);
  Serial.print(hour[1]);
  Serial.print(":");
  Serial.print(minute[0]);
  Serial.print(minute[1]);
  Serial.print(":");
  Serial.print(second[0]);
  Serial.print(second[1]);

  Serial.print("\n");
}

void indicateClockUpdate() {
  ticks = ticks + 1;

  //  transmitSysTime();

  if (ticks == 10) {
    ticks = 0;
    Serial.println("ticks = 10");
  }
}
