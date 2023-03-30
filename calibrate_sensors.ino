// This function calibrates three different sensors and allows the user to adjust their compensation values using an encoder. 
// The function starts by initializing a sensorIndex variable that will be used as a reference for which sensor is currently being calibrated.
// It also assigns a pointer to the bbqCompensation variable and sets it as the first sensor to calibrate.
// The while loop runs indefinitely until the calibration is stopped or all three sensors have been calibrated.
// Inside the loop, the LCD is cleared and the current sensor being calibrated is displayed.
// Another while loop is used to allow the user to adjust the compensation value using the encoder.
// The encoderDelta variable is used to track the changes made by the encoder and adjust the compensation value accordingly.
// The LCD is updated with the new compensation value and instructions on how to adjust it.
// If the user changes to a different sensorIndex, the function updates the compensationPtr pointer to the appropriate sensor and displays the new sensor name on the LCD.
// Once all sensors have been calibrated, the function breaks out of the while loop and returns. 




void calibrateSensors()
{
  int sensorIndex = 0;
  double *compensationPtr = &bbqCompensation;

  while (true)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (sensorIndex)
    {
      case 0:
        compensationPtr = &bbqCompensation;
        lcd.print("Calib. BBQ:");
        break;
      case 1:
        compensationPtr = &protein1Compensation;
        lcd.print("Calib. Prot. 1:");
        break;
      case 2:
        compensationPtr = &protein2Compensation;
        lcd.print("Calib. Prot. 2:");
        break;
      default:
        break;
    }

    while (digitalRead(ENCODER_PIN_SWITCH) == HIGH)
    {
      encoder.tick();
      int16_t encoderDelta = encoder.getPosition();

      if (encoderDelta != 0)
      {
        *compensationPtr += encoderDelta * 0.1;
        if (*compensationPtr < -20.0)
        {
          *compensationPtr = -20.0;
        }
        else if (*compensationPtr > 20.0)
        {
          *compensationPtr = 20.0;
        }
      }

      lcd.setCursor(0, 1);
      lcd.print("Compensacao: ");
      lcd.print(*compensationPtr, 1);
      lcd.setCursor(0, 2);
      lcd.print("Use encoder para");
      lcd.setCursor(0, 3);
      lcd.print("ajustar valor");
      delay(200);
    }

    delay(200); 
    sensorIndex++;
    if (sensorIndex > 2){
      break;
    }
  }
}
