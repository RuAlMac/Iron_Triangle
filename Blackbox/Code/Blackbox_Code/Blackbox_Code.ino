//Iron Triangle Blackbox Code

/*Responsibilities of the Blackbox:
   - Managing the security of the Iron Triangle System (i.e., system pin management)
   - Maintaining real time clock
   - Recording events logged by the system
*/

/*Functions:
   - Setting new system code (any number chars)
   - Setting length of system code
   - Inputting system code to unlock functionality
   - Setting communication code (5 chars max)
   - Option to make system code same as communication code (overwrite sys code with comm code)
*/

//*****Libraries & Initialization*****
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Keypad
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

Keypad blackBoxKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//*****Peripherals*****
int tilt = 30;
int rLed = 31;
int gLed = 32;
int bLed = 33;

//*****System Variables*****
char inputKey;    // for reading keypad inputs
int activeScreen; // for setting which screen is to be displayed on LCD
bool screenChanged = false;
bool justInitialized = true;
bool blackBoxReady = false;
bool tiltSettingSet = false;
bool sysClockSet = false;
bool armingMode = false;

//*****Procedural Variables*****
int index;
int i;     //to be used as an increment in for loops only
int currentColumn; //to be used to keep track of what column is being typed in on the LCD
int input;
int tempTimeVariable;

//*****Clock variables*****
int day;
int hour[2];
int minute[2];
int second[2];
int computedTime[2]; //this array stores the current hour in computedTime[0] and stores the current minute in computedTime[1]. This is mainly used for verifying that input time is valid.

//clock function variables
int startMillis;
int currentMillis;

//timing variables
int secSendTime; //for determining how long to wait to send seconds info over radio after send command given
int minSendTime; //for determining how long to wait to send minutes info over radio after send command given
int hourSendTime; //for determining how long to wait to send hours info over radio after send command given
int ticks;

//Clock settings (do not change, this variable will be changed during normal operation)
bool transmit_system_time = true;

//*****Settings*****
int sysPinLength = 5; //CODE CURRENTLY ONLY SUPPORTS 5; default length, max length is 15, min length is 4
int sysPin[5];
int commPin[5];

bool tiltAlarmConsideration; //if FALSE, the tilt switch will not affect the alarm; if TRUE, the tilt switch will affect the alarm

//*****I2C Communication*****
int I2C_value = 0;
int slaveAddress = 9;

//*****Main Code*****
void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  pinMode(tilt, INPUT_PULLUP);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("   Iron Triangle");

  lcd.setCursor(0, 1);
  lcd.print("      Blackbox");

  lcd.setCursor(0, 2);
  lcd.print("     Initiating");

  delay(2000);
}

void loop() {
  if (justInitialized == true) {
    setNewSecurityCode();
    runSysClock();
  }

  if (blackBoxReady == false) {
    digitalWrite(rLed, HIGH);
    runBlackBoxPrep();
    runSysClock();
  }

  if ( (blackBoxReady == true) && (armingMode == false) ) {
    runMainMenu();
    runSysClock();
  }

  if (armingMode == true) {
    runReadyToArm();
    runSysClock();
  }
}
