//Clock Functions

//This function uses the millis() function to determine when different features should start and stop.
void runSysClock() {
  currentMillis = millis();

  if ( (currentMillis >= end_noIntTrans_time) && (enableNoIntTran == true)) { //for no interrupt transmit feature
    enableNoIntTran = false; //Stops the no interrupt transmit feature
    
    radio.startListening();  //switching to receiver mode
    radio.openReadingPipe(0, address);

    Serial.print("No Interrupt Transmit END: rComm == {");
    Serial.print(combined_bComm);
    Serial.print("}\n");
  }
}
