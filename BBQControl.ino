// Melhorias ja previstas:
// Adicionar lib Bounce2
// Adicionar Interrupção no Encoder
// Tratamento de Erro


// Including the necessary libraries for the project
#include <Wire.h> // Library for I2C communication
#include <RotaryEncoder.h> // Library for rotary encoder communication
#include <max6675.h> // Library for temperature sensors communication
#include <LiquidCrystal_I2C.h> // Library for LCD display communication | Se nao funcionar tentar https://github.com/mathertel/LiquidCrystal_PCF8574
#include <string> // Library for manipulating strings

// Assigning values to the pins used in the project
#define ENCODER_PIN_A 25 // Rotary encoder pin A 
#define ENCODER_PIN_B 26 // Rotary encoder pin B
#define ENCODER_PIN_SWITCH 27 // Rotary encoder push button pin

#define RELAY_PIN 32 // Relay control pin
#define SMOKE_CONTROL_BUTTON_PIN 36 // Smoke control button pin
#define BUZZER_PIN 33 // buzzer output pin
#define SMOKE_RELAY_PIN 34 // Smoke relay control pin

#define MAX6675_BBQ_SCK_PIN 14 // Barbecue temperature sensor SCK pin
#define MAX6675_BBQ_CS_PIN 12 // Barbecue temperature sensor CS pin
#define MAX6675_BBQ_MISO_PIN 13 // Barbecue temperature sensor MISO pin

#define MAX6675_PROTEIN1_SCK_PIN 17 // Protein 1 temperature sensor SCK pin
#define MAX6675_PROTEIN1_CS_PIN 16 // Protein 1 temperature sensor CS pin
#define MAX6675_PROTEIN1_MISO_PIN 4 // Protein 1 temperature sensor MISO pin

#define MAX6675_PROTEIN2_SCK_PIN 18 // Protein 2 temperature sensor SCK pin
#define MAX6675_PROTEIN2_CS_PIN 5 // Protein 2 temperature sensor CS pin
#define MAX6675_PROTEIN2_MISO_PIN 23 // Protein 2 temperature sensor MISO pin

#define LCD_I2C_ADDRESS 0x27 // Default I2C address for 16x2 and 20x4 LCD modules  // pinos i2c esp32 21 SDA e 22 SCL

#define STANDBY_BUTTON_PIN 35 // Power button pin

//Creating objects and initializing them

// LiquidCrystal_I2C object to control the LCD with I2C interface
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 20, 4);

// RotaryEncoder object to read input from the rotary encoder
RotaryEncoder encoder(ENCODER_PIN_A, ENCODER_PIN_B, RotaryEncoder::LatchMode::FOUR3);

// MAX6675 object to read the temperature from the BBQ thermocouple
MAX6675 thermocouple(MAX6675_BBQ_SCK_PIN, MAX6675_BBQ_CS_PIN, MAX6675_BBQ_MISO_PIN);

// MAX6675 object to read the temperature from the protein1 thermocouple
MAX6675 protein1_thermocouple(MAX6675_PROTEIN1_SCK_PIN, MAX6675_PROTEIN1_CS_PIN, MAX6675_PROTEIN1_MISO_PIN);

// MAX6675 object to read the temperature from the protein2 thermocouple
MAX6675 protein2_thermocouple(MAX6675_PROTEIN2_SCK_PIN, MAX6675_PROTEIN2_CS_PIN, MAX6675_PROTEIN2_MISO_PIN);

// Size of the menu
const int menuSize = 8;

// Maximum number of visible items on the menu
const int maxVisibleItems = 4;

// Index of the first visible item on the menu
int topItemIndex = 0;

// Index of the selected item on the menu
int menuIndex = 0;

// Menu options
const char menuOption0[] PROGMEM = "Temperatura BBQ";
const char menuOption1[] PROGMEM = "Temperatura Proteina 1";
const char menuOption2[] PROGMEM = "Temperatura Proteina 2";
const char menuOption3[] PROGMEM = "Monitor";
const char menuOption4[] PROGMEM = "Calibrar Sensores";
const char menuOption5[] PROGMEM = "Curar BBQ";
const char menuOption6[] PROGMEM = "Desligar";

const char* const menuOptions[] PROGMEM = {
  menuOption0,
  menuOption1,
  menuOption2,
  menuOption3,
  menuOption4,
  menuOption5,
  menuOption6
};

// Variables to store the temperature readings
int bbqTemperature = 0;
int protein1Temperature = 0;
int protein2Temperature = 0;

// Variable to control the alarm
bool alarmEnabledProtein1 = false;
bool alarmEnabledProtein2 = false;

// Variables to store the sensor compensation values
double bbqCompensation = 0.0;
double protein1Compensation = 0.0;
double protein2Compensation = 0.0;

// Variables to control the relays
bool relay1_enabled = false;
bool relay3_enabled = false;

//bool smokeRelayState = false;


/*
   This function initializes the system with the following details:
   - Begins the I2C bus
   - Initializes the LCD
   - Sets the backlight to maximum brightness
   - Sets the ENCODER_PIN_SWITCH, RELAY_PIN, TURBO_BBQ_RELAY_PIN, and ALARM_PIN as inputs/outputs
   - Sets the SMOKE_RELAY_PIN as output and sets it to LOW
   - Calls the displaySplashScreen() function to display the splash screen
   - Calls the displayMenu() function to display the menu screen
*/
void setup() {
  Wire.begin();
  lcd.init();
  lcd.setBacklight(255);
  pinMode(ENCODER_PIN_SWITCH, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SMOKE_CONTROL_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SMOKE_RELAY_PIN, OUTPUT);
  //digitalWrite(SMOKE_RELAY_PIN, LOW);
  pinMode(STANDBY_BUTTON_PIN, INPUT_PULLUP);
  displaySplashScreen();
  displayMenu();
}

void loop() {
  // Verificar sensores e exibir mensagem de erro se algum sensor falhar
  if (!checkSensors()) {
    displaySensorError();
  } else {
    menuHandling();
    
    if (bbqTemperature > 0) {
      controlTemperature();
    }
    
    if (protein1Temperature > 0) {
      controlProtein1Temperature();
    }
    
    if (protein2Temperature > 0) {
      controlProtein2Temperature();
    }
    
    
    checkPowerButtonAndTurnOffRelays();
    handleSmokeControlButton();
  }
}
