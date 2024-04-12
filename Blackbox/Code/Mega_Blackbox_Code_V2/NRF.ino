void transmitAndListen() {

  //Listening for sent info
  if (transmitting == false) {
    radio.startListening();                 //switching to receiver mode
    radio.openReadingPipe(0, address);
    if ( radio.available() ) {              //checking for incoming message

      radio.read(&rComm, sizeof(rComm));
      radio.read(&sComm, sizeof(sComm));
    }
  }

  //Transmitting info
  if (transmitting == true) {
    radio.stopListening();                  //switch to transmitter mode
    radio.openWritingPipe(address);
    radio.write(&bComm, sizeof(bComm));     //transmit bComm[] array
  }

  //Switching between receiving and transmitting every x milliseconds
  if ( (currentMillis >= nrfMillis) && (messageReceived == false) ) {
    nrfMillis = currentMillis + 750;       //Define timing here
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
    radio.read(&rComm, sizeof(rComm));
    delay(10);
    radio.read(&sComm, sizeof(sComm));
  }
}

//Non-Interruptive Transmit Functions
void noInterruptTransmit_setup(int t) { //t is the time in milliseconds for which rComm should be transmitted
  getCombinedbComm();
  end_noIntTrans_time = currentMillis + t;
  enableNoIntTran = true;

  radio.stopListening();                  //switch to transmitter mode
  radio.openWritingPipe(address);

  Serial.print("No Interrupt Transmit BEGIN: bComm == {");
  Serial.print(combined_bComm);
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

void justTransmit(int t) {

  nrfMillis = currentMillis + t;

  radio.stopListening();                  //switch to transmitter mode
  radio.openWritingPipe(address);

  while (currentMillis < nrfMillis) {
    currentMillis = millis();
    radio.write(&bComm, sizeof(bComm));     //transmit bComm[] array
  }
}
