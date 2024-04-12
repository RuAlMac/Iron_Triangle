#include <SPI.h>
#include <SD.h>

//SD
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 39;

//TMRpcm Library
#include <TMRpcm.h>
TMRpcm tmrpcm; //crete an object for speaker library

//Communication with Mega
#include <Wire.h>

//*****Variables*****
//Modifiable by I2C
volatile int i2c_message;
volatile int sSettings[21];

//Clock
int currentMillis;

//Procedural
int count;
int mode; //1: receiving settings
bool newMessage = false;
bool settingsReceived = false;

//SD Files
File savedSettings;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //runSdCheck();
  //createMissingFiles();
  //retrieveSavedSettings();

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

  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(5);

  Wire.begin(0xA1); //Initializes I2C protocol; the 0xA1 inside the function designates this board as both a master and slave
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany) { //howMany is always equal to bytes received
  while (Wire.available()) {
    i2c_message = Wire.read();

    if (i2c_message == 241) {
      Serial.println("start receiving settings");
      count = 0;
      mode = 1;
    }

    if (mode == 1) {
      sSettings[count] = i2c_message;
      count = count + 1;
    }

    if (i2c_message == 31) {
      Serial.println("end receiving settings");
      delay(50);
      settingsReceived = true;
      mode = 0;
    }

    //Serial.println(i2c_message);
    delay(20);
  }
}

void loop() {
  /* delay(100);

    if (settingsReceived == true) {
     for (int i = 0; -i <= 21; i++) {
       Serial.print("Settings: sSettings[");
       Serial.print(i);
       Serial.print("] = ");
       Serial.print(sSettings[i]);
       Serial.print("\n");
       settingsReceived = false;
       delay(20);
     }
    }*/
}
