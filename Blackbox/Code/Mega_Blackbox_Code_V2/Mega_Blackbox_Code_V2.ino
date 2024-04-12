//Iron Triangle Blackbox Code

/*Responsibilities of the Blackbox:
   - Managing the security of the Iron Triangle System (i.e., system pin management)
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

byte bell[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

byte unlocked[] = {
  B01110,
  B10000,
  B10000,
  B10000,
  B11111,
  B11011,
  B11011,
  B11111
};

byte checkmark[] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

//I2C
#include <Wire.h>
volatile int i2c_message = 0;

//NRF
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); //CE, CSN
const byte address[6] = "FETRI";

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
char inputKey;                  // for reading keypad inputs
int mode = 0;
int activeScreen = 0;
bool screenChanged = false;
bool justInitialized = true;
bool blackBoxReady = false;
bool tiltSettingSet = false;

//*****Procedural Variables*****
int index;
int index2;
int i;                          //to be used as an increment in for loops only
int currentColumn;              //to be used to keep track of what column is being typed in on the LCD
int input;
int nrf;                        //procedural variable for nrf purposes only
bool sentryOnline = false;
bool remoteOnline = false;
int end_noIntTrans_time;
int combined_bComm;

//For data logging:
bool arm_process_started = false;
bool arm_process_aborted = false;
bool arm_process_completed = false;
bool sys_disarmed = false;
bool remote_tilt_not_alarm = false;
bool remote_tilt_alarm = false;
bool blackbox_tilt_not_alarm = false;
bool blackbox_tilt_alarm = false;
bool alarm_ctdwn_start = false;
bool alarm_trigger = false;
bool enableNoIntTran = false;

//*****Clock Variables*****
int currentMillis;
int nrfMillis;

//*****NRF Variables*****
bool messageReceived = false;
bool transmitting = false;
int rComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Remote
int bComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Blackbox
int sComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Sentry

//*****Settings*****
int sysPinLength = 6;           //CODE CURRENTLY ONLY SUPPORTS 6
int sysPin[6];

bool tiltAlarmConsideration;    //if FALSE, the tilt switch will not affect the alarm; if TRUE, the tilt switch will affect the alarm

//*****I2C Communication*****
int I2C_value = 0;
int slaveAddress = 9;

//*****Main Code*****
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    //do nothing
  }

  lcd.init();                   //initialize the lcd
  lcd.backlight();              //open the backlight

  lcd.createChar(0, bell);
  lcd.createChar(1, unlocked);
  lcd.createChar(2, checkmark);

  Wire.begin(0xA1); //Initializes I2C protocol; the 0xA1 inside the function designates this board as both a master and slave
  Wire.onReceive(receiveEvent);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); //MIN, LOW, HIGH, or MAX
  radio.startListening(); //RECEIVER

  pinMode(tilt, INPUT_PULLUP);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);

  Serial.println("****Blackbox initialized****");

  lcd.setCursor(3, 0);
  lcd.print("Iron Triangle");

  lcd.setCursor(6, 1);
  lcd.print("Blackbox");

  lcd.setCursor(4, 2);
  lcd.print("Initializing");

  delay(2000);
}

void loop() {
  runSysClock();
  noInterruptTransmit_exe();
  inputKey = blackBoxKeypad.getKey();

  if (justInitialized == true) {
    setNewSecurityCode();
  }

  if (blackBoxReady == false) {
    digitalWrite(rLed, HIGH);
    runBlackBoxPrep();
  }

  if (blackBoxReady == true) {
    runMainMenu();
  }

  if (mode == 1) { //searching for Blackbox and Sentry signal
    searchForDevices();
  }

  if (mode == 2) { //Functioning as Blackbox
    runDataRecording();
    transmitAndListen();
  }
}
