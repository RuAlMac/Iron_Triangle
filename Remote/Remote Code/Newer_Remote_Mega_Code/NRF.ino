//NRF Functions

//General Purpose
void transmitAndListen() {

  //Listening for sent info
  if (transmitting == false) {
    radio.startListening();                 //switching to receiver mode
    radio.openReadingPipe(0, address);
    if ( radio.available() ) {              //checking for incoming message

      radio.read(&bComm, sizeof(bComm));
      radio.read(&sComm, sizeof(sComm));
    }
  }

  //Transmitting info
  if (transmitting == true) {
    radio.stopListening();                  //switch to transmitter mode
    radio.openWritingPipe(address);
    radio.write(&rComm, sizeof(rComm));     //transmit rComm[] array
  }

  //Switching between receiving and transmitting every x milliseconds
  if ( (currentMillis >= nrfMillis) && (messageReceived == false) ) {
    nrfMillis = currentMillis + 500;       //Define timing here
    nrf = nrf + 1;

    if ( (nrf % 2) == 0 ) {
      transmitting = false;
      Serial.println("Listening");          //print status to serial monitor
    }
    else {
      transmitting = true;
      Serial.println("Transmitting");       //print status to serial monitor
    }
  }
}

void justListen() {
  radio.startListening();                 //switching to receiver mode
  radio.openReadingPipe(0, address);
  if ( radio.available() ) {              //checking for incoming message
    radio.read(&bComm, sizeof(bComm));
    radio.read(&sComm, sizeof(sComm));
  }
}
//***************************


//Transmitting other data (not Comm arrays)
void settingsTransmitProcedure() { //this is the function called in main code for transmitting Settings. The transmitSettings() function is used by this function ONLY.
  digitalWrite(bLed, HIGH);
  delay(500);

  if (interruptSettTrans == false) {
    transmitSettings(1500);
    delay(500);
    transmitSettings(1500); //run twice for redundancy, the nrf chip is a little goofy sometimes
  }

  interruptSettTrans = false;
  digitalWrite(bLed, LOW);
}

void transmitSettings(int t) { //t: duration of time for each setting to be transmitted

  Serial.print(">>> Transmit Settings function starting <<<\n");
  Serial.print("Transmitting rComm[] = {3,7,2,8}\n");

  rComm[0] = 3; //indicating that new settings are about to be transmitted
  rComm[1] = 7;
  rComm[2] = 2;
  rComm[3] = 8;

  justTransmit(1000);

  Serial.print("Transmitting settings, each for ");
  Serial.print(t);
  Serial.print(" milliseconds\n");
  delay(100);

  if (interruptSettTrans == false) {

    for (int y = 0; y <= 20; y++) {
      nrfMillis2 = (currentMillis + t);

      transmitArray[0] = y;
      transmitArray[1] = sSettings[y];

      Serial.print("transmitArray[");
      Serial.print(transmitArray[0]);
      Serial.print("] = ");
      Serial.print(transmitArray[1]);
      Serial.print("\n");

      delay(100);

      radio.stopListening();                  //switch to transmitter mode
      radio.openWritingPipe(address);

      delay(100);

      while (currentMillis < nrfMillis2) {
        currentMillis = millis();
        radio.write(&transmitArray, sizeof(transmitArray));     //transmit rComm[] array
        inputKey = remoteKeypad.getKey();

        if (inputKey == '3') {
          interruptSettTrans = true;
          break;
        }
      }
      if (inputKey == '3') {
        break;
      }
    }
  }

  Serial.println("Finished transmitting settings");
  rComm[0] = 1;
  rComm[1] = 1;
  rComm[2] = 1;
  rComm[3] = 1;

  justTransmit(3000);
}
//***************************




//Non-Interruptive Transmit Functions
void noInterruptTransmit_setup(int t) { //t is the time in milliseconds for which rComm should be transmitted
  getCombinedrComm();
  end_noIntTrans_time = currentMillis + t;
  enableNoIntTran = true;

  radio.stopListening();                  //switch to transmitter mode
  radio.openWritingPipe(address);

  Serial.print("No Interrupt Transmit BEGIN: rComm == {");
  Serial.print(combined_rComm);
  Serial.print("}\tDuration: ");
  Serial.print(t);
  Serial.print(" milliseconds\n");
}

void noInterruptTransmit_exe() {

  if (enableNoIntTran == true) {
    radio.write(&rComm, sizeof(rComm));     //transmit rComm[] array data
  }
}
//***************************



//Interruptive Transmit Functions
void justTransmit(int t) { //interruptive, functions as a delay() function while transmitting
  delay(20);

  getCombinedrComm();
  Serial.print("Transmitting (interruptive) - rComm[] = {");
  Serial.print(combined_rComm);
  Serial.print("}\n");

  radio.stopListening();                  //switch to transmitter mode
  radio.openWritingPipe(address);

  nrfMillis = (currentMillis + t);

  while (currentMillis < nrfMillis) {
    currentMillis = millis();
    radio.write(&rComm, sizeof(rComm));     //transmit rComm[] array
  }

  Serial.println("Stopped transmitting (interruptive)");
}
//***************************
