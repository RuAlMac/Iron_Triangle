//Iron Triangle Remote Code

/* Responsibilities of the Remote:
   - Controlling the Sentry
   - Functioning as the primary interface for the user to operate the Iron Triangle system
   - Establishing what mode the system should be in (e.g., ready, armed, alarm, etc.)
   - Receiving updates from the Blackbox for maintaining and displaying system time
   - Sending updates to the Blackbox for data recording
*/

//*****Libraries & Initialization*****
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte upArrow[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte downArrow[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

byte leftArrow[] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00000,
  B00000
};

/*byte rightArrow[] = { //this icon is unused, commented to leave space for another custom character
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
  };*/

byte padlock[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111
};

byte hourglass[] = {
  B11111,
  B10001,
  B01010,
  B00100,
  B00100,
  B01010,
  B10001,
  B11111
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

byte speaker[] = {
  B00001,
  B00011,
  B11111,
  B11111,
  B11111,
  B11111,
  B00011,
  B00001
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
#include <SPI.h>
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

Keypad remoteKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//*****Peripherals*****
int tilt = 30;
int rLed = 31;
int gLed = 32;
int bLed = 33;

//*****System Variables*****
char inputKey;                  // for reading keypad inputs
bool transmitting = false;
int activeScreen = 0;
int mode = 0;
int activeSettingPage = 0;      // used so that individual Sentry settings don't need a whole new mode for themselves
int activeColumn = 0;           // for using LCD display to display input numbers
int inputKey_int;               // used when converting a keypad char value to an integer
int lastSetting = 0;            // used for convenience when switching between settings that fit in 2+ categories

//*****Procedural Variables*****
int nrf = 0; //to be used for NRF-related counting for avoiding delay() commands
int i;
int likelihood_special_alarm = 0;
int input_pin[6];
int num_correct_digits; //used for comparing the input_pin and sysPin arrays and counting how many input digits in input_pin match sysPin
float percentDone; //used for fancy LCD countdown animation
int combined_rComm; //used for display purposes only, just for displaying all of rComm[] without having to use a for loop each time
bool firstRun = true;
bool enableNoIntTran = false; //used for no interrupt transmit feature
int end_noIntTrans_time; //used for no interrupt transmit feature
int transmitArray[2] = {0, 0}; //an array used for transmitting settings; term 1: setting number, term 2: setting data
bool interruptSettTrans = false;

//*****Clock variables*****
int currentMillis;
int ticks = 0;
int clockMillis;      //used by tick counter
int nrfMillis;        //to be used by NRF commands when sending messages to other devices
int nrfMillis2;
int i2cMillis;        //for use in sending messages over I2C
int countdownTime;    //used for the arming countdown
int startMillis;      //used for the arming countdown
int nrfMillis_2 = 0;  //used for noInterruptTransmit functions

//*****NRF Variables*****
bool messageReceived = false;
int rComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Remote
int bComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Blackbox
int sComm[4] = {0, 0, 0, 0}; //This array is the communication (non-alarm) array for messages originating from the Sentry

//*****Settings*****
int sSettings[21] = {0, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 5, 50}; //Sentry settings array, default values
int customLdrTol[5] = {0, 0, 0, 0, 0}; //5th term is only for storing the computed custom LDR tolerance, which is from the 1st four terms
int sysPin[6] = {1, 1, 1, 1, 1, 1}; //TEMPORARY
//The settings below can only be changed in code, not by the user
bool verboseDebugSerial = false;  //use for debugging, prints specific details about activity to the Serial Monitor
int armingCountdownDuration = 15; //use to set the duration of the arming countdown, in seconds, must be 0 < x < 100
int alarmCountdownDuration = 15; //time in seconds that user has to input sys pin before alarm is triggered

//*****I2C Communication*****
int I2C_value = 0;
int slaveAddress = 9;

//*****Main Code*****
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    //do nothing until Serial Monitor ready
  }
  Serial.print("\n");
  Serial.println("****Remote initialized****");
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, leftArrow);
  //lcd.createChar(3, rightArrow); unused
  lcd.createChar(4, padlock);
  lcd.createChar(5, hourglass);
  lcd.createChar(6, unlocked);
  lcd.createChar(7, speaker);
  lcd.createChar(8, checkmark);

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

  lcd.setCursor(3, 0);
  lcd.print("Iron Triangle");

  lcd.setCursor(7, 1);
  lcd.print("Remote");

  lcd.setCursor(3, 2);
  lcd.print("Initializing");

  delay(2000);

  mode = 1;

  rComm[0] = 2;
  rComm[1] = 1;
  rComm[2] = 2;
  rComm[3] = 1;

  changeScreen(1);
}

void receiveEvent(int howMany) { //howMany is always equal to bytes received
  while (Wire.available()) {
    byte c = Wire.read();
    Serial.print(c, HEX);
    Serial.print("\t");
  }
}

void loop() {
  runSysClock();
  inputKey = remoteKeypad.getKey();
  noInterruptTransmit_exe();

  if (mode == 1) {
    runSearchForBlackbox();
  }

  if (mode == 4) { //Main menu mode

    if (inputKey) {
      switch (inputKey) {
        case '1': //Sentry settings
          mode = 5;
          changeScreen(5);
          break;

        case '2': //Lock screen
          mode = 7;
          activeSetting(34);
          break;

        case '3': //Arming menu
          mode = 6;
          activeSetting(29); //Arming menu main page
          break;
      }
      waitForNoPress();
    }
  }

  if (mode == 5) { //Sentry settings mode
    runSentrySettingsMenu();
  }

  if (mode == 6) { //Arming menu
    runArmingMenu();
  }

  if (mode == 7) { //Locked mode, active if user selects "Lock System" on main menu
    runLockScreen();
  }

  if (mode == 8) { //Armed mode
    runArmedRemote();
  }
}
