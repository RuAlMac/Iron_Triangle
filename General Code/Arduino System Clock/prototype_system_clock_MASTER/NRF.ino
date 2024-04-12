void transmitSysTime() {

  if ( (ticks >= 7) && (ticks < 10) ) { //sends time info for three seconds every 7 seconds
    radio.write( &second[0], sizeof(second[0]) );
    radio.write( &second[1], sizeof(second[1]) );
    radio.write( &minute[0], sizeof(minute[0]) );
    radio.write( &minute[1], sizeof(minute[1]) );
    radio.write( &hour[0], sizeof(hour[0]) );
    radio.write( &hour[1], sizeof(hour[1]) );
    Serial.println("sent clock data");
  }
  
}
