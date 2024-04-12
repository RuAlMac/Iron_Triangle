//Time Keeper board

//Libraries
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

#include <Keypad.h>

//NRF Code
RF24 radio(7, 8); //CE, CSN
const byte address[6] = "CLOCK";

//Keypad
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'Y'},
  {'4', '5', '6', 'N'},
  {'7', '8', '9', 'w'},
  {'a', '0', 'd', 's'}
};

byte rowPins[ROWS] = {29, 28, 27, 26};
byte colPins[COLS] = {22, 23, 24, 25};

Keypad blackBoxKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//*****Peripherals*****
int tilt = 30;
int rLed = 31;
int gLed = 32;
int bLed = 33;

//*****Clock variables
int day;
int hour[2];
int minute[2];
int second[2];

//clock function variables
int startMillis;
int currentMillis;

//timing variables
int secSendTime; //for determining how long to wait to send seconds info over radio after send command given
int minSendTime; //for determining how long to wait to send minutes info over radio after send command given
int hourSendTime; //for determining how long to wait to send hours info over radio after send command given
int ticks;

//Settings
bool transmit_system_time = true;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.stopListening(); //TRANSMITTER
  
  startMillis = 0;

//SET TIME HERE: MUST BE IN 24-HOUR FORMAT
  hour[0] = 2;
  hour[1] = 3;

  minute[0] = 5;
  minute[1] = 9;

  second[0] = 0;
  second[1] = 0;

}

void loop() {
  runSysClock();
}
