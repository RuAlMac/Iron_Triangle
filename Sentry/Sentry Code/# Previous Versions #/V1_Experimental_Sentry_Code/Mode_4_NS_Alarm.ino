void runNSAlarm() {
  deactivatePrototypeLeds();
  activateRedLeds();
  displayNSAlarmPage();
  digitalWrite(rgbRedLed, HIGH);
  digitalWrite(alarmClockRelay, LOW);
  digitalWrite(beaconLightRelay, LOW);
}
