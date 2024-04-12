#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
#include <Wire.h>

#define SD_ChipSelectPin 4

TMRpcm tmrpcm; //crete an object for speaker library

volatile int i2c_message = 0;
int currentMillis;

File eventLog;

void setup() {
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  initializeSD();

  tmrpcm.setVolume(5);

  Wire.begin(0xA1); //Initializes I2C protocol; the 0xA1 inside the function designates this board as both a master and slave
  Wire.onReceive(receiveEvent);

  writeToSD(12);
}

void receiveEvent() {
  i2c_message = Wire.read();
  Serial.println(i2c_message);
}

void loop() {
  currentMillis = millis();
  writeToSD(i2c_message);
}

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

void writeToSD(int y) {

  if (y != 0) {

    eventLog = SD.open("log.txt", FILE_WRITE);
    eventLog.print(currentMillis);
    eventLog.print("\t");
    switch (y) {
      case 1:
        eventLog.print("Remote: Arming process started.");
        break;
      case 2:
        eventLog.println("Remote: Arming process aborted.");
        break;
      case 3:
        eventLog.println("Remote: Arming process completed; system armed.");
        break;
      case 4:
        eventLog.println("Remote: System disarmed.");
        break;
      case 5:
        eventLog.println("Remote: Tilt switch trip: alarmed.");
        break;
      case 6:
        eventLog.println("Remote: Tilt switch trip: not alarmed.");
        break;
      case 7:
        eventLog.println("Blackbox: Tilt switch trip: alarmed.");
        break;
      case 8:
        eventLog.println("Blackbox: Tilt switch trip: not alarmed.");
        break;
      case 9:
        eventLog.println("Sentry: sufficient sensor trip; countdown started.");
        break;
      case 10:
        eventLog.println("Arming process started.");
        break;
      case 11:
        eventLog.println("Remote and Sentry connection confirmed. System activated.");
        break;
      case 12:
        eventLog.println("*************");
        eventLog.println("Blackbox initialized.");
        break;
    }
    eventLog.print("\n");
    eventLog.close();
    i2c_message = 0;
  }

  delay(20);
}
