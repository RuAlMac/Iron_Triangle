//Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//NRF
RF24 radio(7, 8); //CE, CSN
const byte address[6] = "CLOCK";


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER
}

void loop() {
  // put your main code here, to run repeatedly:

}
