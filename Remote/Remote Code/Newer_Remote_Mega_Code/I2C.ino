void receiveEvent() {
  i2c_message = Wire.read();
}

void send_i2c_message(int y) {
  Wire.beginTransmission(0xA1); // transmit to device 0xA1
  Wire.write(y);
  Wire.endTransmission();
}
