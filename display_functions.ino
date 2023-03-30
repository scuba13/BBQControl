/* 
   This function displays the splash screen with the following details:
   - Clears the LCD screen
   - Sets the cursor position to (4,1) and prints the text "BBQ Controller"
   - Sets the cursor position to (7,2) and prints the text "By Du"
   - Waits for 2 seconds before returning
*/
void displaySplashScreen()
{
  lcd.clear();
  lcd.setCursor(4, 1); // Centralizar o texto na linha
  lcd.print("BBQ Controller");
  lcd.setCursor(7, 2); // Centralizar o texto na linha
  lcd.print("By Du");
  delay(2000);
}

/*
   This function displays the menu with the following details:
   - Clears the LCD screen
   - For each visible item in the menu:
     - Sets the cursor position to (0, i)
     - If the current item is the selected item, print ">", else print " "
     - Retrieves the text of the menu option from PROGMEM and prints it
*/
void displayMenu()
{
  lcd.clear();
  for (int i = 0; i < maxVisibleItems; i++)
  {
    lcd.setCursor(0, i);
    if (i == menuIndex - topItemIndex)
    {
      lcd.print(">");
    }
    else
    {
      lcd.print(" ");
    }

    char buffer[21];
    strcpy_P(buffer, (char*)pgm_read_word(&(menuOptions[topItemIndex + i])));
    lcd.print(buffer);
  }
}

// This function displays information about the BBQ and the different proteins being cooked on an LCD screen
void displayMonitor() 
{
  while (true) 
  {
    // Clear the LCD Screen
    lcd.clear();

    // Quadrant 1 - BBQ temperature
    lcd.setCursor(0, 0);
    lcd.print("BBQ:");
    lcd.setCursor(0, 1);
    lcd.print(thermocouple.readCelsius() + bbqCompensation, 1);
    lcd.print((char)223);
    lcd.print("C / ");
    lcd.print(bbqTemperature, 1);
    lcd.print((char)223);
    lcd.print("C");

    // Quadrant 2 - Info about Protein 1
    lcd.setCursor(10, 0);
    lcd.print("P1:");
    lcd.setCursor(10, 1);
    lcd.print(protein1_thermocouple.readCelsius() + protein1Compensation, 1);
    lcd.print((char)223);
    lcd.print("C / ");
    lcd.print(protein1Temperature, 1);
    lcd.print((char)223);
    lcd.print("C");

    // Quadrant 3 - Info about Protein 2
    lcd.setCursor(0, 2);
    lcd.print("P2:");
    lcd.setCursor(0, 3);
    lcd.print(protein2_thermocouple.readCelsius() + protein2Compensation, 1);
    lcd.print((char)223);
    lcd.print("C / ");
    lcd.print(protein2Temperature, 1);
    lcd.print((char)223);
    lcd.print("C");

    // Quadrant 4 - Information about Smoke and Mod
    lcd.setCursor(10, 2);
    lcd.print("Smoke:");
    lcd.print(relay3_enabled ? "ON " : "OFF");
    lcd.setCursor(10, 3);
    lcd.print("Mod:");
    lcd.print(getRelayStatus().c_str());

    // Wait for two seconds before refreshing the screen
    delay(2000);

    // if encoder button is pressed, break out of loop and go back to menu
    if (digitalRead(ENCODER_PIN_SWITCH) == LOW) 
    {
      break;
    }
  }
  displayMenu(); // Display the Menu on the LCD Screen after breaking out of the loop
}
