void runSurveillance() {

  if (alarmMode == 1) {
    updateNonSilentDisplay();
  }

  if (alarmMode == 2) {
    updateSilentDisplay();
  }

  checkLdrSensors();
  checkPirSensors();

  checkAlarmLevel();


}



void updateNonSilentDisplay() {
  displayNSInfoPage();
  displayAlarmLevel();

  updateExternalPirLeds();
}

void updateSilentDisplay() {
  lcd.noBacklight();
}

void checkLdrSensors() {
  //LDR Sensor #1
  if (ldrAlarm1 == false) {
    scanLightLevel1();
  }

  if (ldrAlarm1 == true) {
    incrementResetIndex1();

    if (digitalRead(ldrButton1) == LOW) {
      resetLdrAlarm1();
      while (digitalRead(ldrButton1) == LOW) {
        //do nothing
      }
    }
  }

  //LDR Sensor #2
  if (ldrAlarm2 == false) {
    scanLightLevel2();
  }

  if (ldrAlarm2 == true) {
    incrementResetIndex2();

    if (digitalRead(ldrButton2) == LOW) {
      resetLdrAlarm2();
      while (digitalRead(ldrButton2) == LOW) {
        //do nothing
      }
    }
  }

  if (ldrAlarm1 == true && ldrAlarm2 == true) {
    digitalWrite(ldrGreenLed, HIGH);
    delay(20);
  }
}


void checkPirSensors() {
  checkPirSensor1();
  checkPirSensor2();
  checkPirSensor3();
  checkPirSensor4();
}


void checkAlarmLevel() {
  if (alarmLevel >= maxAlarmLevel) {

    if (alarmMode == 1) {
      mode = 4; //non-silent alarm
      activePage = 0;
      lcd.clear();
      Serial.println("Mode: Non-Silent Alarm (4)");
    }

    if (alarmMode == 2) {
      mode = 5; //silent alarm
      activePage = 0;
      lcd.clear();
      Serial.println("Mode: Silent Alarm (5)");
    }
  }
}
