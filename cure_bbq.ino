// This function performs a curing step by setting the BBQ temperature to a target temperature and maintaining it for a specified duration. It also updates an LCD display with the current step name, temperature, and remaining time in seconds, minutes, or hours depending on the duration. 
void performCuringStep(int stepIndex, int targetTemperature, long duration, const char *stepName) {
  bbqTemperature = targetTemperature;
  long targetTime = millis() + duration;
  while (millis() < targetTime) {
    controlTemperature();

    // Updates the LCD display every second
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(stepName);
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(thermocouple.readCelsius(), 1);
    lcd.print((char)223);
    lcd.print("C ");

    long remainingTime = (targetTime - millis()) / 1000;
    lcd.setCursor(0, 2);
    lcd.print("Tempo restante:");
    lcd.setCursor(0, 3);
    if (remainingTime >= 3600) {
      lcd.print(remainingTime / 3600);
      lcd.print("h");
    } else if (remainingTime >= 60) {
      lcd.print(remainingTime / 60);
      lcd.print("m");
    } else {
      lcd.print(remainingTime);
      lcd.print("s");
    }

    delay(1000);
  }
}


// This function cures a BBQ using a predefined set of temperature and time values. 
// It utilizes arrays to store the curing steps, curing times, and step names.
// It loops through the defined curing steps, calling another function to perform each step.
// After completing the first 5 steps, it prompts the user to add more wood via LCD display.
// The user is asked to press a button when ready, and the last step is executed.
// The function then finishes the curing process and displays a message on the LCD screen.
// The user is prompted to click the encoder button to return to the main menu. 

void cureBBQ() {
  const int curingSteps[] = {70, 80, 90, 100, 110, 120};
  const long curingTimes[] = {3 * 3600000L, 2 * 3600000L, 3600000L, 3600000L, 1800000L, 1800000L};
  const char *stepNames[] = {
    "Etapa 1: 70C - 3h",
    "Etapa 2: 80C - 2h",
    "Etapa 3: 90C - 1h",
    "Etapa 4: 100C - 1h",
    "Etapa 5: 110C - 30m",
    "Etapa 6: 120C - 30m"
  };

  // Loop through the first 5 curing steps
  for (int i = 0; i < 5; i++) {
    performCuringStep(i, curingSteps[i], curingTimes[i], stepNames[i]);
  }

  // Prompt the user to add more wood via LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Adicione lenha e");
  lcd.setCursor(0, 1);
  lcd.print("pressione o botao");
  lcd.setCursor(0, 2);
  lcd.print("quando estiver");
  lcd.setCursor(0, 3);
  lcd.print("pronto.");

  // Wait for the user to press the button
  while (digitalRead(ENCODER_PIN_SWITCH) == HIGH) {
    delay(100);
  }
  delay(200);

  // Execute the final curing step (Step 6)
  digitalWrite(SMOKE_RELAY_PIN, HIGH);
  performCuringStep(5, curingSteps[5], curingTimes[5], stepNames[5]);
  digitalWrite(SMOKE_RELAY_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  bbqTemperature = 0;

  // Finish the curing process and display a message on the LCD screen
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Cura concluida!");

  // Wait for the user to click the encoder button and return to the main menu.
  while (digitalRead(ENCODER_PIN_SWITCH) == HIGH) {
    delay(100);
  }
  displayMenu();
}
