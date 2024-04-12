void runBlackBoxPrep() {

  if ( (inputKey == '1') && (activeScreen != 3) ) {
    inputKey = 0;

    changeScreen(3);
  }

  if ( (activeScreen == 3) && (inputKey == '1') ) {
    runTiltSettingSetUp();
  }


  if ( (activeScreen == 3) && (tiltSettingSet == true)) {
    blackBoxReady = true;
    inputKey = 'z';
    changeScreen(0);
    digitalWrite(rLed, LOW);
    digitalWrite(gLed, HIGH);

    delay(1000);
    digitalWrite(gLed, LOW);
  }
}

void runMainMenu() {

  if (inputKey == '1') {
    mode = 1; //waiting for signal from Sentry and Blackbox
    changeScreen(5);
    digitalWrite(bLed, HIGH);
    index = 0;
    index2 = 0;
    reset_all_comm();
  }

  if (inputKey == '2') {
    runTiltSettingSetUp();
  }

}

void searchForDevices() {
  justListen();

  if ( (rComm[0] == 2) && (rComm[1] == 1) && (rComm[2] == 2) && (rComm[3] == 1) ) { //rComm[] == {2,1,2,1}

    if (index == 0) { //index is a preexisting procedural variable; using it to reduce # of variables in code
      remoteOnline = true;
      index = 1;
      lcd.setCursor(9, 1);
      lcd.write(2);
      Serial.println("Remote online");
    }
  }

  delay(20);

  if ( (sComm[0] == 6) && (sComm[1] == 1) && (sComm[2] == 6) && (sComm[3] == 1) ) { //sComm[] == {2,1,2,1}

    if (index2 == 0) { //i is a preexisting procedural variable; using it to reduce # of variables in code
      sentryOnline = true;
      index2 = 1;
      lcd.setCursor(9, 2);
      lcd.write(2);
      Serial.println("Sentry online");
    }
  }

  if ( (remoteOnline == true) && (sentryOnline == true) ) {
    delay(1000);
    index = 0;
    i = 0;
    sendLogUpdate(11);

    bComm[0] = 3;
    bComm[1] = 3;
    bComm[2] = 3;
    bComm[3] = 3;
    noInterruptTransmit_setup(2000);

    digitalWrite(bLed, LOW);
    mode = 2;
    changeScreen(6);
  }
}

void runDataRecording() {
  //*********Remote Updates*********
  //Arming process started
  if ( (rComm[0] == 5) && (rComm[1] == 5) && (rComm[2] == 5) && (rComm[3] == 5) ) { //rComm[] == {5,5,5,5}
    newEvent(1);
  }

  //Arming process aborted
  if ( (rComm[0] == 5) && (rComm[1] == 2) && (rComm[2] == 5) && (rComm[3] == 2) ) { //rComm[] == {5,2,5,2}
    newEvent(2);
  }

  //Arming process complete; system armed
  if ( (rComm[0] == 5) && (rComm[1] == 3) && (rComm[2] == 5) && (rComm[3] == 3) ) { //rComm[] == {5,3,5,3}
    newEvent(3);
  }

  //System disarmed
  if ( (rComm[0] == 7) && (rComm[1] == 7) && (rComm[2] == 7) && (rComm[3] == 7) ) { //rComm[] == {7,7,7,7}
    newEvent(4);
  }

  //Remote tilt switch trip - alarm
  if ( (rComm[0] == 3) && (rComm[1] == 2) && (rComm[2] == 3) && (rComm[3] == 2) ) { //rComm[] == {3,2,3,2}
    newEvent(5);
  }

  //Remote tilt switch trip - non-alarm
  if ( (rComm[0] == 1) && (rComm[1] == 2) && (rComm[2] == 1) && (rComm[3] == 2) ) { //rComm[] == {1,2,1,2}
    newEvent(6);
  }

  //Remote sending new settings to Sentry
  if ( (rComm[0] == 10) && (rComm[1] == 1) && (rComm[2] == 10) && (rComm[3] == 1) ) { //rComm[] == {10,1,10,1}
    newEvent(12);
  }



  //*********Sentry Updates *********
  //Sufficient sensor trip; alarm countdown started
  if ( (sComm[0] == 8) && (sComm[1] == 5) && (sComm[2] == 8) && (sComm[3] == 5) ) { //sComm[] == {8,5,8,5}
    newEvent(9);
  }

  //Alarm triggered
  if ( (sComm[0] == 9) && (sComm[1] == 9) && (sComm[2] == 9) && (sComm[3] == 9) ) { //sComm[] == {9,9,9,9}
    newEvent(10);
  }
}


void newEvent(int y) {

  //Reset booleans
  if (y != 1) {
    arm_process_started = false;
  }

  if (y != 2) {
    arm_process_aborted = false;
  }

  if (y != 3) {
    arm_process_completed = false;
  }

  if (y != 4) {
    sys_disarmed = false;
  }

  if (y != 5) {
    remote_tilt_alarm = false;
  }

  if (y != 6) {
    remote_tilt_not_alarm = false;
  }

  if (y != 7) {
    blackbox_tilt_not_alarm = false;
  }

  if (y != 8) {
    blackbox_tilt_alarm = false;
  }

  if (y != 9) {
    alarm_ctdwn_start = false;
  }

  if (y != 10) {
    alarm_trigger = false;
  }
  //*******************

  //Send updates to log and LCD display
  lcd.setCursor(0, 2);
  switch (y) {
    case 1: //arm_process_started

      if (arm_process_started == false) {
        Serial.println("Arming process started");
        lcd.print("  <System Arming>   ");
        sendLogUpdate(y);
      }
      arm_process_started = true;
      break;

    case 2: //arm_process_aborted

      if (arm_process_aborted == false) {
        Serial.println("Arming process aborted");
        lcd.print("   <Arming Abort>   ");
        sendLogUpdate(y);
      }
      arm_process_aborted = true;
      break;

    case 3: //arm_process_completed

      if (arm_process_completed == false) {
        Serial.println("Arming process completed");
        lcd.print(" <Arming Complete>  ");
        sendLogUpdate(y);
      }
      arm_process_completed = true;
      break;

    case 4: //sys_disarmed

      if (sys_disarmed == false) {
        Serial.println("System disarmed");
        lcd.print(" <System Disarmed>  ");
        sendLogUpdate(y);
      }
      sys_disarmed = true;
      break;

    case 5: //remote_tilt_alarm

      if (remote_tilt_alarm == false) {
        Serial.println("Remote tilt switch trip - alarm");
        lcd.print("  <Remote Tilt  >   ");
        lcd.setCursor(15, 2);
        lcd.write(0); //prints a bell
        sendLogUpdate(y);
      }
      remote_tilt_alarm = true;
      break;

    case 6: //remote_tilt_not_alarm

      if (remote_tilt_not_alarm == false) {
        Serial.println("Remote tilt switch trip - not alarm");
        lcd.print("  <Remote Tilt  >   ");
        lcd.setCursor(15, 2);
        lcd.write(1); //prints unlocked padlock
        sendLogUpdate(y);
      }
      remote_tilt_not_alarm = true;
      break;

    case 7: //blackbox_tilt_alarm

      if (blackbox_tilt_alarm == false) {
        Serial.println("Blackbox tilt switch trip - alarm");
        lcd.print(" <Blackbox Tilt  >  ");
        lcd.setCursor(16, 2);
        lcd.write(0); //prints bell
        sendLogUpdate(y);
      }
      blackbox_tilt_alarm = true;
      break;

    case 8: //blackbox_tilt_not_alarm

      if (blackbox_tilt_not_alarm == false) {
        Serial.println("Blackbox tilt switch trip - not alarm");
        lcd.print(" <Blackbox Tilt  >  ");
        lcd.setCursor(16, 2);
        lcd.write(1); //prints unlocked padlock
        sendLogUpdate(y);
      }
      blackbox_tilt_not_alarm = true;
      break;

    case 9: //alarm_ctdwn_start

      if (alarm_ctdwn_start == false) {
        Serial.println("Alarm countdown start");
        lcd.print("<!! Cntdwn Start !!>");
        sendLogUpdate(y);
      }
      alarm_ctdwn_start = true;
      break;

    case 10: //alarm_trigger

      if (alarm_trigger == false) {
        Serial.println("Alarm trigger");
        lcd.print("<  Alarm Trigger  > ");
        lcd.setCursor(1, 2);
        lcd.print(0);
        lcd.setCursor(17, 2);
        lcd.print(0);
        sendLogUpdate(y);
      }
      alarm_trigger = true;
      break;
  }
  //*******************

  reset_all_comm();
}
