
// This function sets the temperature using the provided min and max temperature range and a message to display on an LCD.
// It takes a pointer to the current set temperature, the minimum and maximum temperature limits, and a message to display.

void setTemperature(int *setTemperature, int minTemperature, int maxTemperature, const char *message)
{
  // Clear the LCD and print the message
  lcd.clear();
  lcd.print(message);

  // Set the initial temperature to be the minimum temperature
  int temp = minTemperature;

  // While the encoder switch is high, read and adjust the temperature
  while (digitalRead(ENCODER_PIN_SWITCH) == HIGH)
  {
    encoder.tick();
    int16_t encoderDelta = encoder.getPosition();
    temp += encoderDelta;

    // Ensure the temperature is within the allowed range and adjust it accordingly
    if (temp < minTemperature)
    {
      temp = minTemperature;
    }
    else if (temp > maxTemperature)
    {
      temp = maxTemperature;
    }

    // Display the temperature on the LCD
    lcd.setCursor(11, 0);
    lcd.print(temp);
    lcd.print("C");
    delay(200);
  }

  // Delay and set the temperature value to the final adjusted value
  delay(200);
  *setTemperature = temp;

  // Call the displayMenu() function
  displayMenu();
}

// Function to set BBQ temperature
void setBBQTemperature() {
    // Calling setTemperature function with parameters
    // temperature variable, minimum temperature, maximum temperature and prompt message
    setTemperature(&bbqTemperature, 60, 200, "Temp. BBQ: ");
}

// Function to set Protein 1 temperature
void setProtein1Temperature() {
    // Calling setTemperature function with parameters
    // temperature variable, minimum temperature, maximum temperature and prompt message
    setTemperature(&protein1Temperature, 35, 90, "Temp. Proteina 1: ");
}

// Function to set Protein 2 temperature
void setProtein2Temperature() {
    // Calling setTemperature function with parameters
    // temperature variable, minimum temperature, maximum temperature and prompt message
    setTemperature(&protein2Temperature, 35, 90, "Temp. Proteina 2: ");
}
