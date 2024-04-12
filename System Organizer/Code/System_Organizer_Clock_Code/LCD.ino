/* LiquidCrystal Library Commands
   lcd.setCursor([col], [row]);
   lcd.print();
   lcd.clear();
   lcd.noBlink();
   lcd.blink();
*/

void changeScreen() {
  lcd.clear();
  lcd.noBlink();

  if (activeScreen == 0) {

  }

  if (activeScreen == 1) {

  }

  if (activeScreen == 2) {

  }

  if (activeScreen == 3) {

  }

  if (activeScreen == 4) {

  }

  if (activeScreen == 5) {

  }

  if (activeScreen == 6) {

  }
}

void lcdPrintTime() {
  lcd.setCursor(0, 3);
  lcd.print(hour[0]);
  lcd.print(hour[1]);

  lcd.setCursor(3, 3);
  lcd.print(minute[0]);
  lcd.print(minute[1]);

  lcd.setCursor(6, 3);
  lcd.print(second[0]);
  lcd.print(second[1]);

  if (ticks % 2 == 0) {
    lcd.setCursor(2, 3);
    lcd.print(":");
    lcd.setCursor(5, 3);
    lcd.print(":");
  }
  else {
    lcd.setCursor(2, 3);
    lcd.print(" ");
    lcd.setCursor(5, 3);
    lcd.print(" ");
  }
}
