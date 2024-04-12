void runSdCheck() { //taken straight from https://docs.arduino.cc/learn/programming/sd-guide
  Serial.print("\nInitializing SD card...");
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  }
  else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32

  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());
  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume

  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);
  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size

  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
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
    savedSettings.println("1");   //sSettings[10]a
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
