//Remote Uno Code

//*****Initialization*****
//SD
#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 4

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
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  tmrpcm.speakerPin = 9;
  initializeSD();

  tmrpcm.setVolume(5);

  Wire.begin(0xA1); //Initializes I2C protocol; the 0xA1 inside the function designates this board as both a master and slave
  Wire.onReceive(receiveEvent);

  if (!SD.exists("savedSettings.txt")) {
    Serial.println("arduino.txt doesn't exist on SD Card");
  }
  else {
    Serial.println("arduino.txt exists on SD Card");
  }



delay(100);
createMissingFiles();
delay(100);

retrieveSavedSettings();
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
  delay(100);

  if (settingsReceived == true) {
    for (int i = 0; i <= 21; i++) {
      Serial.print("Settings: sSettings[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(sSettings[i]);
      Serial.print("\n");
      settingsReceived = false;
      delay(20);
    }
  }
}
