void initializeSD() {
  Serial.println("Initializing SD card...");
  pinMode(SD_ChipSelectPin, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  }
  else {
    Serial.println("SD card initialization failed");
    return;
  }
}

void createMissingFiles() {
  if (!SD.exists("savedSettings.txt")) {
    savedSettings = SD.open("savedSettings.txt", FILE_WRITE);

    //Pre-set defaults: sSettings[21] = {0, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 5, 50};
    savedSettings.println("0");   //sSettings[0]
    savedSettings.println("1");   //sSettings[1]
    savedSettings.println("1");   //sSettings[2]
    savedSettings.println("0");   //sSettings[3]
    savedSettings.println("1");   //sSettings[4]
    savedSettings.println("2");   //sSettings[5]
    savedSettings.println("1");   //sSettings[6]
    savedSettings.println("1");   //sSettings[7]
    savedSettings.println("1");   //sSettings[8]
    savedSettings.println("1");   //sSettings[9]
    savedSettings.println("1");   //sSettings[10]
    savedSettings.println("1");   //sSettings[11]
    savedSettings.println("1");   //sSettings[12]
    savedSettings.println("0");   //sSettings[13]
    savedSettings.println("0");   //sSettings[14]
    savedSettings.println("1");   //sSettings[15]
    savedSettings.println("1");   //sSettings[16]
    savedSettings.println("1");   //sSettings[17]
    savedSettings.println("0");   //sSettings[18]
    savedSettings.println("5");   //sSettings[19]
    savedSettings.println("50");  //sSettings[20]

    savedSettings.close();
    Serial.println("Created file: savedSettings.txt, used programmed sSettings presets");
  }
}

void saveSettingsToSd() {
  SD.remove("savedSettings.txt"); //deleting existing saved_settings file
  delay(250);

  savedSettings = SD.open("savedSettings.txt", FILE_WRITE);

  for (int i; i <= 20; i++) {
    savedSettings.println(sSettings[i]);
  }

  savedSettings.close();
}


void retrieveSavedSettings() {
  savedSettings = SD.open("savedSettings.txt", FILE_READ); //opening saved settings for read only

  while (savedSettings.available()) {
    Serial.write(savedSettings.read());
  }
  // close the file:
  savedSettings.close();
}
