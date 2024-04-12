void runNSAlarm() {
  deactivatePrototypeLeds();
  activateRedLeds();
  displayNSAlarmPage();
  digitalWrite(rgbRedLed, HIGH);
  digitalWrite(alarmClockRelay, LOW);
  digitalWrite(beaconLightRelay, LOW);

  if ( (digitalRead(tempButton2) == LOW) || (buttonSelected == 2) ){
    resetButtonSelect();
    mode = 6;
    activePage = 0;
    lcd.clear();
    Serial.print("\n");
    Serial.print("Mode: Disarming (6)");
  }
}
