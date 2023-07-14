#include "LCD_control.h"
#include "Arduino.h"


// LCD object
LiquidCrystal_I2C lcd(i2cAddress, lcdColumns, lcdRows);

const int lcdColumns = 16;
const int lcdRows = 2;

// I2C address of the PCF8574T
const int i2cAddress = 0x27;

// Button pins
const int button1Pin = 8;
const int button2Pin = 9;
const int button3Pin = 10;

// Menu variables
int currentOption = 0; // Current selected menu option
int numPlants = 1;     // Number of plants (default: 1)
int mlWater = 5;       // Milliliters of water per plant (default: 5)
int hoursBetweenSprinklers = 1; // Hours between sprinklers (default: 1)

// Button variables
volatile bool button1Pressed = false; // Flag for button 1 press
volatile bool button2Pressed = false; // Flag for button 2 press
volatile bool button3Pressed = false; // Flag for button 3 press

// Timer variables
unsigned long menuTimeout = 20000;    // Menu timeout in milliseconds
unsigned long lastButtonPressTime = 0; // Time of the last button press

// Interrupt service routines
void button1ISR() {
  button1Pressed = true;
}

void button2ISR() {
  button2Pressed = true;
}

void button3ISR() {
  button3Pressed = true;
}

// Initialize LCD
void initializeLCD() {
  lcd.begin(lcdColumns, lcdRows);
  lcd.print("Menu:");
  lcd.setCursor(0, 1);
  lcd.print("Option: ");
}

// Display current option values on LCD
void displayMenu() {
  lcd.setCursor(8, 1);
  lcd.print("   "); // Clear previous value
  lcd.setCursor(8, 1);

  switch (currentOption) {
    case 0:
      lcd.print(numPlants);
      break;
    case 1:
      lcd.print(mlWater);
      break;
    case 2:
      lcd.print(hoursBetweenSprinklers);
      break;
  }
}

// Adjust option values based on button input
void adjustOption(int& option, int minVal, int maxVal, int increment) {
  option += increment;

  if (option < minVal) {
    option = minVal;
  } else if (option > maxVal) {
    option = maxVal;
  }

  displayMenu();
}

// Save modified option value
void saveOption() {
  switch (currentOption) {
    case 0:
      numPlants = mlWater;
      break;
    case 1:
      mlWater = mlWater;
      break;
    case 2:
      hoursBetweenSprinklers = hoursBetweenSprinklers;
      break;
  }

  displayMenu();
}


void loopLCD(){
// Check if button 1 is pressed to activate the menu
  if (button1Pressed) {
    button1Pressed = false; // Reset button 1 flag
    currentOption = 0; // Reset current option

    lcd.clear();
    displayMenu();

    lastButtonPressTime = millis();

    // Wait for other buttons to be pressed within the timeout period
    while (millis() - lastButtonPressTime < menuTimeout) {
      if (button2Pressed) {
        button2Pressed = false; // Reset button 2 flag
        adjustOption(currentOption, 1, 12, 1); // Adjust current option
        lastButtonPressTime = millis();
      }

      if (button3Pressed) {
        button3Pressed = false; // Reset button 3 flag
        adjustOption(currentOption, 5, 200, 5); // Adjust current option
        lastButtonPressTime = millis();
      }

      if (button1Pressed) {
        button1Pressed = false; // Reset button 1 flag
        saveOption(); // Save modified option value
        lastButtonPressTime = millis();
      }
    }

    lcd.clear();
    lcd.print("Menu timeout");
    delay(2000);
    lcd.clear();
    lcd.print("Menu:");
    lcd.setCursor(0, 1);
    lcd.print("Option: ");
  }
}
/*
// Main setup function (called from Arduino sketch)
void setup() {
  // Initialize I2C communication
  Wire.begin();

  // Attach interrupt service routines to buttons
  attachInterrupt(digitalPinToInterrupt(button1Pin), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button3Pin), button3ISR, FALLING);

  // Initialize LCD
  initializeLCD();
}

// Main loop function (called from Arduino sketch)
void loop() {
  // Check if button 1 is pressed to activate the menu
  if (button1Pressed) {
    button1Pressed = false; // Reset button 1 flag
    currentOption = 0; // Reset current option

    lcd.clear();
    displayMenu();

    lastButtonPressTime = millis();

    // Wait for other buttons to be pressed within the timeout period
    while (millis() - lastButtonPressTime < menuTimeout) {
      if (button2Pressed) {
        button2Pressed = false; // Reset button 2 flag
        adjustOption(currentOption, 1, 12, 1); // Adjust current option
        lastButtonPressTime = millis();
      }

      if (button3Pressed) {
        button3Pressed = false; // Reset button 3 flag
        adjustOption(currentOption, 5, 200, 5); // Adjust current option
        lastButtonPressTime = millis();
      }

      if (button1Pressed) {
        button1Pressed = false; // Reset button 1 flag
        saveOption(); // Save modified option value
        lastButtonPressTime = millis();
      }
    }

    lcd.clear();
    lcd.print("Menu timeout");
    delay(2000);
    lcd.clear();
    lcd.print("Menu:");
    lcd.setCursor(0, 1);
    lcd.print("Option: ");
  }
}
*/
