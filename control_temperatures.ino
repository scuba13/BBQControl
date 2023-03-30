
// This function controls the temperature of a BBQ smoker or grill.
// It reads the current temperature from a thermocouple sensor and compares it to the desired temperature.
// Depending on the temperature difference, it turns on or off two relays that control the fan and the heating element.
// The relays are connected to the pins RELAY_PIN and TURBO_BBQ_RELAY_PIN.
// The function updates the boolean variables relay1_enabled and relay2_enabled to reflect the current state of the relays.

//void controlTemperature() {
//  // Read the current temperature from the thermocouple sensor in Celsius
//  double currentTemperature = thermocouple.readCelsius();
//  // Calculate the temperature difference between the desired temperature and the current temperature
//  float temp_diff = bbqTemperature - currentTemperature;
//
//// Segunda proteção para nao iniciar os reles ligado, a primeira esta no loop
//  if (bbqTemperature = 0) {
//    digitalWrite(RELAY_PIN, LOW);
//    digitalWrite(TURBO_BBQ_RELAY_PIN, LOW);
//    relay1_enabled = false;
//    relay2_enabled = false;
//  } 
//    // If the temperature difference is larger than 30 degrees Celsius, turn on both relays at full power
//    else if (temp_diff >= 30) {
//      digitalWrite(RELAY_PIN, HIGH);
//      digitalWrite(TURBO_BBQ_RELAY_PIN, HIGH);
//      relay1_enabled = true;
//      relay2_enabled = true;
//    }
//    // If the temperature difference is between 3 and 30 degrees Celsius, turn on only the first relay to control the BBQ
//    else if (temp_diff >= 3) {
//      digitalWrite(RELAY_PIN, HIGH);
//      digitalWrite(TURBO_BBQ_RELAY_PIN, LOW);
//      relay1_enabled = true;
//      relay2_enabled = false;
//    }
//    // If the current temperature is within 1 degree Celsius of the desired temperature, turn off both relays
//    else if (currentTemperature >= bbqTemperature - 1) {
//      digitalWrite(RELAY_PIN, LOW);
//      digitalWrite(TURBO_BBQ_RELAY_PIN, LOW);
//      relay1_enabled = false;
//      relay2_enabled = false;
//    }
//    // If the current temperature is lower than the desired temperature but the temperature difference is less than 3 degrees Celsius, turn on only the second relay to control the heating element
//    else {
//      digitalWrite(RELAY_PIN, HIGH);
//      digitalWrite(TURBO_BBQ_RELAY_PIN, LOW);
//      relay1_enabled = true;
//      relay2_enabled = false;
//    }
//
//  }

   void controlTemperature()
    {
    double currentTemperature = thermocouple.readCelsius();

    // Desliga o relé quando a temperatura atual for 1 grau abaixo da temperatura definida
    if (currentTemperature >= bbqTemperature - 1)
    {
      digitalWrite(RELAY_PIN, LOW);
    }
    // Liga o relé quando a temperatura atual for 1 graus abaixo da temperatura definida
    else if (currentTemperature <= bbqTemperature - 1)
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    } 

  // The following function controls the temperature of a protein by checking if it has surpassed a set temperature.
  // If an alarm is not already enabled, the function will trigger an alarm and enable it if the current temperature is greater
  // than or equal to the set temperature. If an alarm is already enabled, the function will silence the alarm
  // if a specific digital pin is read as LOW and return to "Monitor" mode by displaying its output.

void controlProtein1Temperature() {
  double currentTemperature = protein1_thermocouple.readCelsius();
  
  if (!alarmEnabledProtein1) {
    if (currentTemperature >= protein1Temperature) {
      triggerAlarm(1);
      alarmEnabledProtein1 = true;
    }
  } else {
    // Não precisa mais verificar o botão do encoder, basta chamar a função triggerAlarm()
    triggerAlarm(1);
  }
}

void controlProtein2Temperature() {
  double currentTemperature = protein2_thermocouple.readCelsius();
  
  if (!alarmEnabledProtein2) {
    if (currentTemperature >= protein2Temperature) {
      triggerAlarm(2);
      alarmEnabledProtein2 = true;
    }
  } else {
    // Não precisa mais verificar o botão do encoder, basta chamar a função triggerAlarm()
    triggerAlarm(2);
  }
}
