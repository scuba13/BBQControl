

void handleSmokeControlButton() {
  static unsigned long lastButtonPressTime = 0;
  unsigned long currentMillis = millis();
  if (digitalRead(SMOKE_CONTROL_BUTTON_PIN) == LOW && currentMillis - lastButtonPressTime > 200) {
    relay3_enabled = !relay3_enabled;
    digitalWrite(SMOKE_RELAY_PIN, relay3_enabled ? HIGH : LOW);
    lastButtonPressTime = currentMillis;
  }
}
