void runSysClock() {
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

  transmitSysTime();

  if (ticks == 10) {
    ticks = 0;
    Serial.println("ticks = 10");
  }
}
