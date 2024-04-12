void transmitAndListen() {

  //Listening for sent info
  if (transmitting == false) {
    radio.startListening();                 //switching to receiver mode
    radio.openReadingPipe(0, address);
    if ( radio.available() ) {              //checking for incoming message

      radio.read(&rComm, sizeof(rComm));
      delay(10);
      radio.read(&bComm, sizeof(bComm));
    }
  }

  //Transmitting info
  if (transmitting == true) {
    radio.stopListening();                  //switch to transmitter mode
    radio.openWritingPipe(address);
    radio.write(&sComm, sizeof(sComm));     //transmit sComm[] array
  }

  //Switching between receiving and transmitting every x milliseconds
  if ( (currentMillis >= nrfMillis) && (messageReceived == false) ) {
    nrfMillis = currentMillis + 1000;       //Define timing here
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
    radio.read(&bComm, sizeof(bComm));
    delay(10);
    radio.read(&sSettings, sizeof(sSettings));
    delay(10);
  }
}

void justTransmit(int t) {

  nrfMillis = currentMillis + t;

  radio.stopListening();                  //switch to transmitter mode
  radio.openWritingPipe(address);

  while (currentMillis < nrfMillis) {
    currentMillis = millis();
    radio.write(&sComm, sizeof(sComm));     //transmit bComm[] array
  }
}
