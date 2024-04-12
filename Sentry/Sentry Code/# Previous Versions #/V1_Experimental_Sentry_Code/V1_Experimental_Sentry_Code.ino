//Pin 10 must be left alone for SPI protocol communication to function

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7);
const byte address[7] = "SENTRY";

//#include <SD.h>
//File myFile;

//********************LCD Screen Custom Characters********************
byte fullPixel[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

//********************General System Variables********************
int alarmLevel;
int mode = 0; //Used for determining the mode of the overall system
int activePage = 0;
int index;

//TEMPORARY VARIABLES (for prototyping use only)
int tempButton1 = 2;
int tempButton2 = 3;
int tempButton3 = 4;

int pirLed1 = 8;
int pirLed2 = 9;
int pirLed3 = 11;
int pirLed4 = 12;

//NRF Variables
int buttonSelected;
int buttonPressed[1];

//PIR Sensors
int pir1 = 26;
int pir2 = 27;
int pir3 = 28;
int pir4 = 29;

bool pir1State = false;
bool pir2State = false;
bool pir3State = false;
bool pir4State = false;

bool pir1Led = false;
bool pir2Led = false;
bool pir3Led = false;
bool pir4Led = false;

//Output Variables
int alarmClockRelay = 30;
int beaconLightRelay = 31;

int redLed1 = 32;
int redLed2 = 33;
int redLed3 = 34;
int redLed4 = 35;

int greenLed1 = 36;
int greenLed2 = 37;
int greenLed3 = 38;
int greenLed4 = 39;

int rgbRedLed = 40;
int rgbGreenLed = 41;
int rgbBlueLed = 42;

/*
   Mode 0: config
   Mode 1: ready
   Mode 2: arming
   Mode 3: surveilance
   Mode 4: non-silent alarm
   Mode 5: silent alarm
   Mode 6:
*/

//Settings
int tolerance1 = 50; //LDR #1 tolerance
int tolerance2 = 50; //LDR #2 tolerance
int alarmMode = 1; //1 being "non-silent", 2 being "silent"
int maxAlarmLevel = 3;

//********************LDR Sensor System Variables********************
//**** General Variables ****
int ldrGreenLed = 46;
int maxNumberValues = 10;
bool verboseSerialOutput = false; //This is for prototyping only; change to true to get detailed information about LDR sensor values in the Serial monitor

//**** LDR Sensor 1 Variables ****
int ldrPin1 = A0;
int ldrRedLed1 = 44;
int ldrButton1 = 48;

float newValue1;
float average1 = 0;
int index1;
int values1[110];
int numberValuesInput1 = 0;
int upperBound1 = 0;
int lowerBound1 = 0;
bool ldrAlarm1 = false;

int ldrResetIndex1 = 0;

//**** LDR Sensor 2 Variables ****
int ldrPin2 = A1;
int ldrRedLed2 = 45;
int ldrButton2 = 49;

float newValue2;
float average2 = 0;
int index2;
int values2[110];
int numberValuesInput2 = 0;
int upperBound2 = 0;
int lowerBound2 = 0;
bool ldrAlarm2 = false;

int ldrResetIndex2 = 0;

//********************Backup Function Prototypes********************
//run[Mode] Functions
void runConfig();
void runReady();
void runArming();
void runSurveillance();
void runNSAlarm();
void runSAlarm();

//Output Functions
void activateGreenLeds();
void deactivateGreenLeds();
void activateRedLeds();
void deactivateRedLeds();

//LCD Display Function Backups
void displayConfigInfoPage();
void updateConfigScreen();
void updateReadyScreen();
void displayArmingInfoPage();
void executeArmingCountdown();
void displayAlarmLevel();

//LDR Sensor Function Backups
void scanLightLevel1();
void resetArray1();
void scanLightLevel2();
void resetArray2();
void reportActiveLdr1();
void reportNewValue1();
void reportBounds1();
void reportNumberValuesInput1();
void reportSum1();
void reportNewAverage1();
void reportAverage1();
void reportActiveLdr2();
void reportNewValue2();
void reportBounds2();
void reportNumberValuesInput2();
void reportSum2();
void reportNewAverage2();
void reportAverage2();
void reportAcceptance();
void reportDenial();
void reportArrayCleared();
void startNewSpace();
void reportAlarm();

//PIR Sensor Function Backups
void checkPirSensor1();
void checkPirSensor2();
void checkPirSensor3();
void checkPirSensor4();


void checkLdrSensors();
void resetLdrAlarm1();
void resetLdrAlarm2();

void setup() {
  //***Serial Monitor Initialization***
  Serial.begin(9600);
  while (!Serial) {
    //do nothing, wait for Serial to begin
  }
  Serial.print("\n");
  Serial.println("Initialized");
  startNewSpace();

  //***NRF Initialization***
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); //MIN, LOW, or HIGH
  radio.startListening(); //RECEIVER

  //***LCD Screen Initialization***
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  lcd.createChar(0, fullPixel);
  lcd.setCursor(0, 0);
  lcd.print("initialized");
  delay(20);

  //***SD Card Initialization***
  /*  if (!SD.begin(10)) {
      Serial.println("SD initialization failed!");
    }*/

  //***Sensor Initialization***
  pinMode(ldrPin1, INPUT);
  pinMode(ldrPin2, INPUT);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);

  //***LDR Input/Output Initialization***
  pinMode(ldrRedLed1, OUTPUT);
  pinMode(ldrRedLed2, OUTPUT);
  pinMode(ldrGreenLed, OUTPUT);
  pinMode(ldrButton1, INPUT_PULLUP);
  pinMode(ldrButton2, INPUT_PULLUP);

  //TEMPORARY INITIALIZATION
  pinMode(tempButton1, INPUT_PULLUP);
  pinMode(tempButton2, INPUT_PULLUP);
  pinMode(tempButton3, INPUT_PULLUP);

  pinMode(pirLed1, OUTPUT);
  pinMode(pirLed2, OUTPUT);
  pinMode(pirLed3, OUTPUT);
  pinMode(pirLed4, OUTPUT);

  //OUTPUT INITIALIZATION
  pinMode(alarmClockRelay, OUTPUT);
  pinMode(beaconLightRelay, OUTPUT);

  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);
  pinMode(redLed4, OUTPUT);

  pinMode(greenLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(greenLed3, OUTPUT);
  pinMode(greenLed4, OUTPUT);

  pinMode(rgbRedLed, OUTPUT);
  pinMode(rgbGreenLed, OUTPUT);
  pinMode(rgbBlueLed, OUTPUT);

  //Code to run once
  Serial.println("Mode: Config (0)");
  digitalWrite(alarmClockRelay, HIGH);
  digitalWrite(beaconLightRelay, HIGH);
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

  /*
    if (mode == 0) { //Config
      runConfig();
    }

    if (mode == 1) { //Ready
      runReady();
    }

    if (mode == 2) { //Arming
      runArming();
    }

    if (mode == 3) { //Surveillance
      runSurveillance();
    }

    if (mode == 4) { //Non-Silent Alarm
      runNSAlarm();
    }

    if (mode == 5) { //Silent Alarm
      runSAlarm();
    }

    /*  Serial.print("Mode: ");
      Serial.print(mode);
      Serial.print("\n");

      Serial.print("Active Page: ");
      Serial.print(activePage);
      Serial.print("\n");*/
}
