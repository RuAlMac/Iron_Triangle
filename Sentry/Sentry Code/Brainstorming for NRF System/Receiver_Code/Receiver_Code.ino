/* MEGA Pins:
    CE = 9
    CSN = 8
    SCK = 52
    MOSI = 51
    MISO = 50
    NRF24L01+ Documentation: https://nrf24.github.io/RF24/
*/

//RECEIVER CODE
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

int buttonSelected;
int buttonPressed[1];
const byte address[7] = "SENTRY";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER
}

void loop() {
  if (radio.available()) {
    radio.read(&buttonPressed[0], sizeof(buttonPressed[0]));
    Serial.println(buttonPressed[0]);
    buttonSelected = buttonPressed[0];

    if (buttonPressed[0] == 1) {
      Serial.println("Led 1, ON");
      
    }

    if (buttonPressed[0] == 2) {
      Serial.println("Led 2, ON");
    }

    if (buttonPressed[0] == 3) {
      Serial.println("Led 3, ON");
    }
  }
}
