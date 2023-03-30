// Define a new function to get the status of the two relays
std::string getRelayStatus() {
  if (relay1_enabled && relay3_enabled) { // Both relays are on
    return "ALL";
  } else if (relay1_enabled && !relay3_enabled) { // Only relay 1 is on
    return "HEAT";
    } else if (!relay1_enabled && relay3_enabled) { // Only relay 1 is on
    return "SMOKE";
  } else { // Both relays are off
    return "WAIT";
  }
}

// Function to check the power button state and turn off all relays if pressed
void checkPowerButtonAndTurnOffRelays() {
  if (digitalRead(STANDBY_BUTTON_PIN) == HIGH) {
    // Save the current temperature settings before turning off all relays
    int bbqTemp = bbqTemperature;
    int protein1Temp = protein1Temperature;
    int protein2Temp = protein2Temperature;

    // Set all temperature settings to 0
    bbqTemperature = 0;
    protein1Temperature = 0;
    protein2Temperature = 0;

    // Turn off all relays
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(SMOKE_RELAY_PIN, LOW);
    
    // Display standby message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stand By Ligado");
    lcd.setCursor(0, 1);
    lcd.print("Para continuar o BBQ");
    lcd.setCursor(0, 2);
    lcd.print("Desligue o botao de");
    lcd.setCursor(0, 3);
    lcd.print("Stand By");

    // Wait for power button to be turned off
    while (digitalRead(STANDBY_BUTTON_PIN) == HIGH) {
      delay(100);
    }

    // Restore temperature settings after power button is turned off
    bbqTemperature = bbqTemp;
    protein1Temperature = protein1Temp;
    protein2Temperature = protein2Temp;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Stand By Desligado");
    lcd.setCursor(0, 2);
    lcd.print("Continuando o BBQ");
  }
}

void safeShutdown() {
  // Desliga relés
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(SMOKE_RELAY_PIN, LOW);

  // Desliga alto-falante
  noTone(BUZZER_PIN);

  // Exibe mensagem de desligamento no display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Desligando o");
  lcd.setCursor(0,1);
  lcd.print("Sistema...");
  delay(2000);

  // Desliga display
  lcd.setBacklight(0);
  lcd.clear();
  lcd.noDisplay();
}
