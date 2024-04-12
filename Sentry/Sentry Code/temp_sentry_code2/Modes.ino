void runSearchForBlackbox() {
  transmitAndListen();

  if ( (bComm[0] == 3) && (bComm[1] == 3) && (bComm[2] == 3) && (bComm[3] == 3) ) { //bComm[] == {3,3,3,3}
    mode = 2;
    activeSetting(2);
    Serial.println("Sentry ready; received bComm[] == {3,3,3,3}");
  }
}

void listenToComms() {
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

  //*********Blackbox Updates *********
  //Blackbox tilt switch trip - alarm
  if ( (bComm[0] == 3) && (bComm[1] == 2) && (bComm[2] == 3) && (bComm[3] == 2) ) { //bComm[] == {3,2,3,2}
    newEvent(7);
  }

  //Blackbox tilt switch trip - non-alarm
  if ( (bComm[0] == 1) && (bComm[1] == 2) && (bComm[2] == 1) && (bComm[3] == 2) ) { //bComm[] == {1,2,1,2}
    newEvent(8);
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

  if (y != 12) {
    newSettings = false;
  }
  //*******************

  //Send updates to log and LCD display
  switch (y) {
    case 1: //arm_process_started

      if (arm_process_started == false) {
        Serial.println("Arming process started");
        lcd.setCursor(9, 1);
        lcd.print("[Arming]   ");
      }
      arm_process_started = true;
      break;

    case 2: //arm_process_aborted

      if (arm_process_aborted == false) {
        Serial.println("Arming process aborted");
        lcd.setCursor(9, 1);
        lcd.print("[Unarmed]  ");
      }
      arm_process_aborted = true;
      break;

    case 3: //arm_process_completed

      if (arm_process_completed == false) {
        Serial.println("Arming process completed");
        lcd.setCursor(9, 1);
        lcd.print("[Armed]    ");
      }
      arm_process_completed = true;
      break;

    case 4: //sys_disarmed

      if (sys_disarmed == false) {
        Serial.println("System disarmed");
        lcd.setCursor(9, 1);
        lcd.print("[Unarmed]  ");
      }
      sys_disarmed = true;
      break;

    case 5: //remote_tilt_alarm

      if (remote_tilt_alarm == false) {
        Serial.println("Remote tilt switch trip - alarm");
      }
      remote_tilt_alarm = true;
      break;

    case 6: //remote_tilt_not_alarm

      if (remote_tilt_not_alarm == false) {
        Serial.println("Remote tilt switch trip - not alarm");
      }
      remote_tilt_not_alarm = true;
      break;

    case 7: //blackbox_tilt_alarm

      if (blackbox_tilt_alarm == false) {
        Serial.println("Blackbox tilt switch trip - alarm");
      }
      blackbox_tilt_alarm = true;
      break;

    case 8: //blackbox_tilt_not_alarm

      if (blackbox_tilt_not_alarm == false) {
        Serial.println("Blackbox tilt switch trip - not alarm");
      }
      blackbox_tilt_not_alarm = true;
      break;

    case 9: //alarm_ctdwn_start

      if (alarm_ctdwn_start == false) {
        Serial.println("Alarm countdown start");
        lcd.print("<!! Cntdwn Start !!>");
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
      }
      alarm_trigger = true;
      break;

    case 12: //new Settings
      if (newSettings == false) {
        mode = 3;
        changeScreen(3);
      }
      newSettings = true;
      break;
  }
  //*******************
  reset_all_comm();
}
