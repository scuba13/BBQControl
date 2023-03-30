
// This function takes an integer parameter "index" and executes a corresponding action based on the value of "index".
// It uses a switch case structure to call the relevant function based on the index value.
// If the index matches any of the cases then it will trigger the corresponding function.
// If none of the cases match, it will break and do nothing.
void executeMenuItem(int index)
{
  switch (index)
  {
    case 0:
      setBBQTemperature();
      break;
    case 1:
      setProtein1Temperature();
      break;
    case 2:
      setProtein2Temperature();
      break;
    case 3:
      displayMonitor();
      break;
    case 4:
      calibrateSensors();
      break;
    case 5:
      cureBBQ();
    case 6:
      safeShutdown();
      break;
    default:
      break;
  }
}

void menuHandling() {
  encoder.tick();
  int16_t encoderDelta = encoder.getPosition();

  if (encoderDelta != 0) {
    menuIndex += encoderDelta;
    if (menuIndex < 0)
      menuIndex = 0;
  } else if (menuIndex >= menuSize) {
    menuIndex = menuSize - 1;
  }

  if (menuIndex < topItemIndex) {
    topItemIndex = menuIndex;
  } else if (menuIndex >= topItemIndex + maxVisibleItems) {
    topItemIndex = menuIndex - maxVisibleItems + 1;
  }

  if (digitalRead(ENCODER_PIN_SWITCH) == LOW) {
    delay(200);
    executeMenuItem(menuIndex);
  }
}
