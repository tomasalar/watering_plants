#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "Arduino.h"
// LCD configuration
extern const int lcdColumns;
extern const int lcdRows;

// I2C address of the PCF8574T
extern const int i2cAddress;

// Button pins
extern const int button1Pin;
extern const int button2Pin;
extern const int button3Pin;

// Menu variables
extern int currentOption; // Current selected menu option
extern int numPlants;     // Number of plants (default: 1)
extern int mlWater;       // Milliliters of water per plant (default: 5)
extern int hoursBetweenSprinklers; // Hours between sprinklers (default: 1)

// Button variables
extern volatile bool button1Pressed; // Flag for button 1 press
extern volatile bool button2Pressed; // Flag for button 2 press
extern volatile bool button3Pressed; // Flag for button 3 press

// Timer variables
extern unsigned long menuTimeout;    // Menu timeout in milliseconds
extern unsigned long lastButtonPressTime;  // Time of the last button press

// Prototypes of functions
void button1ISR();
void button2ISR();
void button3ISR();
void initializeLCD();
void displayMenu();
void adjustOption(int& option, int minVal, int maxVal, int increment);
void saveOption();
void loopLCD();


#endif
