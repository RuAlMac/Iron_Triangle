//Iron Triangle System Organizer Code

/*Responsibilities of the System Organizer:
   - Maintaining the system clock
   - Transmitting the system time over regular intervals for proper data logging by the Iron Triangle system
*/

/*Functions:
   - Setting system time
   - Transmitting system time regularly
*/

//*****Libraries & Initialization*****
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//NRF
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); //CE, CSN

/*//Keypad
  #include <Keypad.h>
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

  Keypad sysClockKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
*/

//*****System variables*****
char inputKey;    // for reading keypad inputs
int activeScreen; // for setting which screen is to be displayed on LCD
int currentColumn; //to be used to keep track of what column is being typed in on the LCD
bool sysClockSet = false;

//*****Clock variables*****
int day;
int hour[2];
int minute[2];
int second[2];
int checkTimeInput[2]; //this array stores the current hour in checkTimeInput[0] and stores the current minute in checkTimeInput[1]. This is mainly used for verifying that input time is valid.

//clock function variables
int startMillis;
int currentMillis;
int ticks;
bool firstRun = true;
int combinedTime[7];

//*****Settings*****
//Radio address
const byte address[6] = "CLOCK";

//*****Main Code*****
void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  radio.begin();
  //radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); //MIN, LOW, or HIGH
  radio.stopListening(); //TRANSMITTER

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  /*pinMode(tilt, INPUT_PULLUP);
    pinMode(rLed, OUTPUT);
    pinMode(gLed, OUTPUT);
    pinMode(bLed, OUTPUT);*/

  lcd.setCursor(0, 0);
  lcd.print("   Iron Triangle");

  lcd.setCursor(0, 1);
  lcd.print("  System Organizer  ");

  lcd.setCursor(0, 2);
  lcd.print("     Initiating");

  //Manually setting time (debugging)
  hour[0] = 1;
  hour[1] = 0;
  minute[0] = 0;
  minute[1] = 4;
  second[0] = 0;
  second[1] = 0;
  sysClockSet = true;

  delay(2000);

  Serial.println("System initialized");
  lcd.clear();
}

void loop() {
  runSysClock();
}
