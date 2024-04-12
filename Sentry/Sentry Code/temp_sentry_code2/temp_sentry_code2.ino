//temporary Sentry code, needs to be incorporated into existing Sentry code

//*****Libraries & Initialization*****
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

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

byte communication[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
}

//NRF
#include <SPI.h> //2.0 Additions (Libraries)
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); //CE, CSN   ************************************************REVERT BACK TO 6,7 FOR ACTUAL SENTRY
const byte address[6] = "FETRI";

//*****System Variables*****
char inputKey;                  // for reading keypad inputs
int mode = 0;
int activeSettingPage;

//*****Procedural Variables*****
int index;
int i;                          //to be used as an increment in for loops only
int currentColumn;              //to be used to keep track of what column is being typed in on the LCD
int input;
int nrf;                        //procedural variable for nrf purposes only

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
bool newSettings = false;


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
int sSettings[19] = {5, 1, 1, 50, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}; //Sentry settings array, default values

//*****Main Code*****
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    //do nothing
  }

  lcd.init();                   //initialize the lcd
  lcd.backlight();              //open the backlight

  lcd.createChar(0, hourglass);
  lcd.createChar(1, communication);
  lcd.createChar(2, checkmark);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); //MIN, LOW, or HIGH
  radio.startListening();         //RECEIVER

  Serial.println("****Sentry initialized****");

  lcd.setCursor(0, 0);
  lcd.print("   Iron Triangle");

  lcd.setCursor(0, 1);
  lcd.print("       Sentry");

  lcd.setCursor(0, 2);
  lcd.print("    Initializing");

  delay(2000);

  mode = 1;

  sComm[0] = 6;
  sComm[1] = 1;
  sComm[2] = 6;
  sComm[3] = 1;

  activeSetting(1);
}

void loop() {
  currentMillis = millis();

  if (mode == 1) {
    runSearchForBlackbox();
  }

  if (mode == 2) {
    justListen();
    listenToComms(); //Listens for any incoming communications and runs code for appropriate communications
  }

  if (mode == 3) { //Sentry receiving settings update from Remote
    justListen();

    if (sSettings[18] == 1) {
      sSettings[18] = 0;
      lcd.setCursor(13, 2);
      lcd.write(2);

      prepGenAck_sComm();
      justTransmit(1000);
      
      reset_all_comm();
      mode = 2;
    }
  }
}
