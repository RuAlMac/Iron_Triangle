/* MEGA Pins:
    CE = 9
    CSN = 8
    SCK = 52
    MOSI = 51
    MISO = 50
    NRF24L01+ Documentation: https://nrf24.github.io/RF24/
*/

//REMOTE Code
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); //CE, CSN

int button1 = 2;
int button2 = 3;
int button3 = 4;

int buttonPressed[1];
const byte address[7] = "SENTRY";

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);


  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.startListening(); //TRANSMITTER
}

void loop() {

  if (digitalRead(button1) == LOW) {
    buttonPressed[0] = 1;
    Serial.println("Button 1");

    //Switching to Transmitter Mode //**************************
    radio.openWritingPipe(address);
    radio.stopListening();
    radio.write(&buttonPressed[0], sizeof(buttonPressed[0]));

    while (digitalRead(button1) == LOW) {
      //do nothing
    }

    //Returning to Receiver Mode //**************************
    radio.startListening();

    delay(50);
  }

  if (digitalRead(button2) == LOW) {
    buttonPressed[0] = 2;
    Serial.println("Button 2");

    //Switching to Transmitter Mode //**************************
    radio.openWritingPipe(address);
    radio.stopListening();
    radio.write(&buttonPressed[0], sizeof(buttonPressed[0]));

    //Returning to Receiver Mode //**************************
    radio.startListening();

    while (digitalRead(button2) == LOW) {
      //do nothing
    }

    delay(50);
  }



  if (digitalRead(button3) == LOW) {
    buttonPressed[0] = 3;
    Serial.println("Button 3");

    //Switching to Transmitter Mode //**************************
    radio.openWritingPipe(address);
    radio.stopListening();
    radio.write(&buttonPressed[0], sizeof(buttonPressed[0]));

    //Returning to Receiver Mode //**************************
    radio.startListening();

    while (digitalRead(button3) == LOW) {
      //do nothing
    }

    delay(50);
  }

//  Serial.println(buttonPressed[0]);

  // delay(250);
}
