#include "Arduino.h"
//#include "Ds1302.h"
#include "LCD_control.h"
#include "sensors_relays.h"
#include "avr/sleep.h" // Include the library for sleep modes

// Pin assignments
//const int button1Pin = 8;
//const int button2Pin = 9;
//const int button3Pin = 10;

// Flag to indicate if the menu is active
bool menuActive = false;

// Function to enter sleep mode
void enterSleepMode() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power down
  sleep_enable(); // Enable sleep mode
  attachInterrupt(digitalPinToInterrupt(button1Pin), wakeUpISR, RISING); // Attach interrupt to wake up from sleep
  sleep_mode(); // Enter sleep mode
  sleep_disable(); // Disable sleep mode after waking up
  detachInterrupt(digitalPinToInterrupt(button1Pin)); // Detach interrupt
}

// Empty interrupt service routine for wake up
void wakeUpISR() {
  // Empty interrupt service routine for wake up
}

void setup() {
  // Setup the LCD API
  initializeLCD(); // Initialize the LCD API
  
  // Setup the Sensors API
  initializeSensors(); // Initialize the Sensors API

  // Attach button interrupts
  attachInterrupt(digitalPinToInterrupt(button1Pin), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button3Pin), button3ISR, FALLING);
  
  // Start sensor readings
  startReadings(NUM_SENSORS);
}

void loop() {
  // Check if the menu is active
  if (menuActive) {
    // Call the LCD API's loop function
    loopLCD();
    
    // Call the Sensors API's loop function
    readSensors(NUM_SENSORS);
  } else {
    // Enter sleep mode to conserve power
    enterSleepMode();
  }
  
  // Your additional code here
  // ...
}
