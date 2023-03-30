// This function checks if the MAX6675 sensors are working correctly
bool checkSensors() {
  if (isnan(thermocouple.readCelsius()) || isnan(protein1_thermocouple.readCelsius()) || isnan(protein2_thermocouple.readCelsius())) {
    return false;
  }
  return true;
}

// This function displays an error message on the LCD screen if the sensors are not working correctly
void displaySensorError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Erro no sensor");
  lcd.setCursor(0, 1);
  lcd.print("Verifique conexoes");
  lcd.setCursor(0, 2);
  lcd.print("e reinicie o");
  lcd.setCursor(0, 3);
  lcd.print("controlador.");
  delay(5000);
}
