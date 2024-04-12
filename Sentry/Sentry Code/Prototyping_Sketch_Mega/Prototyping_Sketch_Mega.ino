//Sentry Prototyping Sketch for Mega Board

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); //CE, CSN

int message[1];
const byte address[6] = "ALARM";

int button1 = 2;
int button2 = 3;
int button3 = 4;

int pir1Led = 8;
int pir2Led = 9;
int pir3Led = 11;
int pir4Led = 12;

int relay1 = 23;
int relay2 = 24;

int pir1 = 26;
int pir2 = 27;
int pir3 = 28;
int pir4 = 29;

int redLed1 = 32;
int redLed2 = 33;
int redLed3 = 34;
int redLed4 = 35;

int greenLed1 = 36;
int greenLed2 = 37;
int greenLed3 = 38;
int greenLed4 = 39;

int rgbRed = 40;
int rgbGreen = 41;
int rgbBlue = 42;

int ldrLed1 = 44;
int ldrLed2 = 45;

int ldrButton1 = 48;
int ldrButton2 = 49;

int ldr1 = 54;
int ldr2 = 55;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.stopListening(); //TRANSMITTER

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(pir1Led, OUTPUT);
  pinMode(pir2Led, OUTPUT);
  pinMode(pir3Led, OUTPUT);
  pinMode(pir4Led, OUTPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);

  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);
  pinMode(redLed4, OUTPUT);

  pinMode(greenLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(greenLed3, OUTPUT);
  pinMode(greenLed4, OUTPUT);

  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);

  pinMode(ldrLed1, OUTPUT);
  pinMode(ldrLed2, OUTPUT);

  pinMode(ldrButton1, INPUT_PULLUP);
  pinMode(ldrButton2, INPUT_PULLUP);

  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);

  delay(50);

  lcd.setCursor(0, 0);
  lcd.print("Sentry online");

}

void loop() {
  radio.write(&message[0], sizeof(message[0]));
}
