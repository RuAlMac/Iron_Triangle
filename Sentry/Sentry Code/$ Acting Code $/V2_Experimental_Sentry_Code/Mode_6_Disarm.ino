void runDisarm() {
  deactivateRedLeds();
  digitalWrite(alarmClockRelay, HIGH);
  digitalWrite(beaconLightRelay, HIGH);
  digitalWrite(rgbRedLed, LOW);
  digitalWrite(rgbGreenLed, HIGH);

  displayDisarmPage();

  delay(5000);

  mode = 1;
  activePage = 0;
  digitalWrite(rgbGreenLed, LOW);
  lcd.clear();
  Serial.print("\n");
  Serial.print("Mode: Ready (1)");
}
