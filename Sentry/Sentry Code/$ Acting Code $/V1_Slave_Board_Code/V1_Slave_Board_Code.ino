#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

int signalReceiver = A0;
int signalVal = 0;

#define SD_ChipSelectPin 3

TMRpcm tmrpcm; //crete an object for speaker library

void setup()
{
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  initializeSD();
  tmrpcm.setVolume(5);

  pinMode(signalReceiver, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  signalVal = analogRead(signalReceiver);

  if (signalVal >= 740) { //If the signal from the Master Board is HIGH
    digitalWrite(LED_BUILTIN, HIGH);

    if (!tmrpcm.isPlaying()) {
      tmrpcm.play("alarm1.wav");
    }
  }
  else { //If the signal from the Master Board is LOW
    digitalWrite(LED_BUILTIN, LOW);
    tmrpcm.stopPlayback();
  }
}


void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(SD_ChipSelectPin, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}
