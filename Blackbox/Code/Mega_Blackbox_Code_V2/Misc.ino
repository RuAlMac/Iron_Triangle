int charToInt(int x) { //converts a character to an integer, assuming that the input char is a integer
  int result;
  result = x - '0';
  return result;
}

void reset_rComm() {
  for (i = 0; i < 4; i++) {
    rComm[i] = 0;
  }
  Serial.println("Reset rComm");
}

void reset_bComm() {
  for (i = 0; i < 4; i++) {
    bComm[i] = 0;
  }
  Serial.println("Reset bComm");
}

void reset_sComm() {
  for (i = 0; i < 4; i++) {
    sComm[i] = 0;
  }
  Serial.println("Reset sComm");
}

void reset_all_comm() {
  reset_rComm();
  reset_bComm();
  reset_sComm();
}

void prepGenAck_bComm() { //just sets bComm[] = {1,1,1,1}
  bComm[0] = 1;
  bComm[1] = 1;
  bComm[2] = 1;
  bComm[3] = 1;
}

void getCombinedbComm() { //used for visual purposes, cuts down on program time for displaying bComm[]
  combined_bComm = ( (1000 * bComm[0]) + (100 * bComm[1]) + (10 * bComm[2]) + bComm[3] );
}
