void debugReadKeypad() {
  inputKey = blackBoxKeypad.getKey();

  if (inputKey) {
    Serial.println(inputKey);
  }
}
