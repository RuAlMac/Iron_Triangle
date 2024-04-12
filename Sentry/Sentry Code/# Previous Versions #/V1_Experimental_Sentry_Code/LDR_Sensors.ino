//********** LDR Sensor 1 **********
void scanLightLevel1() {
  reportActiveLdr1();

  upperBound1 = average1 + tolerance1;
  lowerBound1 = average1 - tolerance1;
  newValue1 = analogRead(ldrPin1);

  reportNewValue1();

  if (numberValuesInput1 == 0) {
    upperBound1 = newValue1 + tolerance1;
    lowerBound1 = newValue1 - tolerance1;
    average1 = newValue1;
  }

  reportBounds1(); //SERIAL REPORT

  if ( newValue1 == average1 || (newValue1 <= upperBound1 && newValue1 >= lowerBound1) ) { //If ACCEPTED
    //Adding newValue to the values[] array if it is accepted
    reportAcceptance(); //SERIAL REPORT

    values1[numberValuesInput1] = newValue1;

    ++numberValuesInput1;

    reportNumberValuesInput1(); //SERIAL REPORT

    average1 = 0;

    //Computing new average with all values in values[]
    for (index1 = 0; index1 <= numberValuesInput1; ++index1) {
      average1 = values1[index1] + average1;
    }

    reportSum1();

    average1 = average1 / numberValuesInput1;

    reportNewAverage1(); //SERIAL REPORT
  }
  else { //If DENIED
    reportDenial();
    digitalWrite(ldrRedLed1, HIGH);
    reportAverage1();
    ldrAlarm1 = true;
    alarmLevel = alarmLevel + 1;
  }

  if (numberValuesInput1 == maxNumberValues) { //Reset array
    resetArray1();
  }
  startNewSpace();
}

void resetArray1() {
  for (index1 = 0; index1 < maxNumberValues; ++index1) {
    values1[index1] = 0;
  }
  numberValuesInput1 = 0;
  average1 = 0.00;

  reportArrayCleared();
}

//********** LDR Sensor 2 **********
void scanLightLevel2() {
  reportActiveLdr2();

  upperBound2 = average2 + tolerance2;
  lowerBound2 = average2 - tolerance2;
  newValue2 = analogRead(ldrPin2);

  reportNewValue2();

  if (numberValuesInput2 == 0) {
    upperBound2 = newValue2 + tolerance2;
    lowerBound2 = newValue2 - tolerance2;
    average2 = newValue2;
  }

  reportBounds2(); //SERIAL REPORT

  if ( newValue2 == average2 || (newValue2 <= upperBound2 && newValue2 >= lowerBound2) ) { //If ACCEPTED
    //Adding newValue to the values[] array if it is accepted
    reportAcceptance(); //SERIAL REPORT

    values2[numberValuesInput2] = newValue2;

    ++numberValuesInput2;

    reportNumberValuesInput2(); //SERIAL REPORT

    average2 = 0;

    //Computing new average with all values in values[]
    for (index2 = 0; index2 <= numberValuesInput2; ++index2) {
      average2 = values2[index2] + average2;
    }

    reportSum2();

    average2 = average2 / numberValuesInput2;

    reportNewAverage2(); //SERIAL REPORT
  }
  else { //If DENIED
    reportDenial();
    digitalWrite(ldrRedLed2, HIGH);
    reportAverage2();
    ldrAlarm2 = true;
    alarmLevel = alarmLevel + 1;
  }

  if (numberValuesInput2 == maxNumberValues) { //Reset array
    resetArray2();
  }
  startNewSpace();
}

void resetArray2() {
  for (index2 = 0; index2 < maxNumberValues; ++index2) {
    values2[index2] = 0;
  }
  numberValuesInput2 = 0;
  average2 = 0.00;

  reportArrayCleared();
}

//********** Serial Display for LDR 1 **********
void reportActiveLdr1() {
  if (verboseSerialOutput == true) {
    Serial.print("ACTIVE LDR: #1");
    Serial.print("\n");
  }
}

void reportNewValue1() {
  if (verboseSerialOutput == true) {
    Serial.print("New Value: ");
    Serial.print(newValue1);
    Serial.print("\n");
  }
}

void reportBounds1() {
  if (verboseSerialOutput == true) {
    Serial.print("Upper Bound: ");
    Serial.print(upperBound1);
    Serial.print("\n");

    Serial.print("Lower Bound: ");
    Serial.print(lowerBound1);
    Serial.print("\n");
  }
}

void reportNumberValuesInput1() {
  if (verboseSerialOutput == true) {
    Serial.print("Number of Values Input: ");
    Serial.print(numberValuesInput1);
    Serial.print("\n");
  }
}

void reportSum1() {
  if (verboseSerialOutput == true) {
    Serial.print("Sum: ");
    Serial.print(average1);
    Serial.print("\n");
  }
}

void reportNewAverage1() {
  if (verboseSerialOutput == true) {
    Serial.print("New Average: ");
    Serial.print(average1);
    Serial.print("\n");
  }
}

void reportAverage1() {
  if (verboseSerialOutput == true) {
    Serial.print("Average: ");
    Serial.print(average1);
    Serial.print("\n");
  }
}

//********** Serial Display for LDR 2 **********
void reportActiveLdr2() {
  if (verboseSerialOutput == true) {
    Serial.print("ACTIVE LDR: #2");
    Serial.print("\n");
  }
}

void reportNewValue2() {
  if (verboseSerialOutput == true) {
    Serial.print("New Value: ");
    Serial.print(newValue2);
    Serial.print("\n");
  }
}

void reportBounds2() {
  if (verboseSerialOutput == true) {
    Serial.print("Upper Bound: ");
    Serial.print(upperBound2);
    Serial.print("\n");

    Serial.print("Lower Bound: ");
    Serial.print(lowerBound2);
    Serial.print("\n");
  }
}

void reportNumberValuesInput2() {
  if (verboseSerialOutput == true) {
    Serial.print("Number of Values Input: ");
    Serial.print(numberValuesInput2);
    Serial.print("\n");
  }
}

void reportSum2() {
  if (verboseSerialOutput == true) {
    Serial.print("Sum: ");
    Serial.print(average2);
    Serial.print("\n");
  }
}

void reportNewAverage2() {
  if (verboseSerialOutput == true) {
    Serial.print("New Average: ");
    Serial.print(average2);
    Serial.print("\n");
  }
}

void reportAverage2() {
  if (verboseSerialOutput == true) {
    Serial.print("Average: ");
    Serial.print(average2);
    Serial.print("\n");
  }
}
//********** General Serial Display **********
void reportAcceptance() {
  if (verboseSerialOutput == true) {
    Serial.print("New Value ACCEPTED");
    Serial.print("\n");
  }
}

void reportDenial() {
  if (verboseSerialOutput == true) {
    Serial.print("New Value DENIED");
    Serial.print("\n");
  }
}

void reportArrayCleared() {
  if (verboseSerialOutput == true) {
    Serial.print("***ARRAY CLEARED***");
    Serial.print("\n");
  }
}

void startNewSpace() {
  if (verboseSerialOutput == true) {
    Serial.print("***************");
    Serial.print("\n");
  }
}

/*void reportAlarm() {
  Serial.print("***ALARM TRIGGERED***");
  Serial.print("\n");
  }*/


void incrementResetIndex1() {
  ldrResetIndex1 = ++ldrResetIndex1;

  if (ldrResetIndex1 == 50) {
    resetLdrAlarm1();
    ldrResetIndex1 = 0;
  }
}

void incrementResetIndex2() {
  ldrResetIndex2 = ++ldrResetIndex2;

  if (ldrResetIndex2 == 50) {
    resetLdrAlarm2();
    ldrResetIndex2 = 0;
  }
}


void resetLdrAlarm1() {
  ldrAlarm1 = false;
  digitalWrite(ldrRedLed1, LOW);
  digitalWrite(ldrGreenLed, LOW);
  resetArray1();
  Serial.println("LDR 1: Light change detected, sensor reset");
  alarmLevel = alarmLevel - 1;
}

void resetLdrAlarm2() {
  ldrAlarm2 = false;
  digitalWrite(ldrRedLed2, LOW);
  digitalWrite(ldrGreenLed, LOW);
  resetArray2();
  Serial.println("LDR 2: Light change detected, sensor reset");
  alarmLevel = alarmLevel - 1;
}
