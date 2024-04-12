//Code for transmitting system time to rest of system

void transmitSysTime() {

  combinedTime[0] = hour[0];
  combinedTime[1] = hour[1];
  combinedTime[2] = minute[0];
  combinedTime[3] = minute[1];
  combinedTime[4] = second[0];
  combinedTime[5] = second[1];

  radio.write( &combinedTime, sizeof(combinedTime) );

  Serial.println("Data transmitted");
}
