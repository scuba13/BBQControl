// This function triggers the alarm and displays the alert message
// on the LCD screen while the alarm is active
void triggerAlarm(int proteinNumber)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. Proteina ");
  lcd.print(proteinNumber);
  lcd.setCursor(0, 1);
  lcd.print("ALERTA!");

  
  // Play the alarm sound on the buzzer Activite
  digitalWrite(BUZZER_PIN, HIGH);
  
  // Blink the alert message on the LCD while the alarm is active
  while (digitalRead(ENCODER_PIN_SWITCH) == HIGH)
  {
    lcd.setCursor(0, 1);
    lcd.print("            ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("ALERTA!");
    delay(500);
  }
  
  // Stop the alarm sound and return to the monitor display
  digitalWrite(BUZZER_PIN, LOW);
  displayMonitor();
}

// This function is called to silence the alarm. It first stops the alarm sound 
// by calling noTone(), then sets the digital pin connected to the alarm to LOW, 
// and finally calls the displayMonitor() function to update the display.
//void silenceAlarm()
//{
//  noTone(BUZZER_PIN);
//  digitalWrite(ALARM_PIN, LOW);
//  displayMonitor();
//}
