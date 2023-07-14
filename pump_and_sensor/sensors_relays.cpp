/*
 * This code uses the Adafruit MCP23017 library to control the MCP23017 I2C 
 * expander. The API provides functions to initialize the API, set sensor 
 * thresholds and relay durations, start and stop readings, read the sensors, 
 * and activate/deactivate the relays. The performDailyReadings function is a 
 * placeholder for you to implement the logic to perform readings at 8 PM using 
 * a real-time clock (RTC) module.

Remember to install the Adafruit MCP23017 library via the Arduino Library Manager
before using this code. Also, make sure to connect the MCP23017 I2C expander 
correctly to the Arduino UNO and configure the sensorThresholds and 
relayDurations arrays with appropriate values.
 */

#include "sensors_relays.h"


// Variables
int sensorThresholds[NUM_SENSORS];  // Threshold values for each sensor
int relayDurations[NUM_SENSORS];   // Duration for each relay activation

Adafruit_MCP23X17 mcp;  // MCP23017 object for relay control
Ds1302 rtc(6, 7, 8);   // DS1302 object for RTC


// Function to initialize the API
void initializeSensors() {
  Wire.begin();
  mcp.begin_I2C();
  rtc.init();
  
  // Configure relay pins as output
  for (int i = 0; i < NUM_SENSORS; i++) {
    mcp.pinMode(RELAY_PIN_BASE + i, OUTPUT);
  }
  
  // Set initial threshold and duration values
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorThresholds[i] = 0;
    relayDurations[i] = 0;
  }
}

// Function to set the threshold value for a sensor
void setSensorThreshold(int sensorNumber, int threshold) {
  if (sensorNumber >= 1 && sensorNumber <= NUM_SENSORS) {
    sensorThresholds[sensorNumber - 1] = threshold;
  }
}

// Function to set the duration for a relay
void setRelayDuration(int sensorNumber, int duration) {
  if (sensorNumber >= 1 && sensorNumber <= NUM_SENSORS) {
    relayDurations[sensorNumber - 1] = duration;
  }
}

// Function to start sensor readings
void startReadings(int numSensors) {
  numSensors = min(numSensors, NUM_SENSORS);

  for (int i = 0; i < numSensors; i++) {
    activateRelay(i + 1);
  }

  // Schedule daily readings at 8 PM
  // Use the MH-DS1302 real-time clock (RTC) module for accurate timekeeping
 // rtc.setDOW(WEDNESDAY);      // Set the day of the week (0-6) - Adjust accordingly
 Ds1302::DateTime dt = {
            .year = 23,
            .month = Ds1302::MONTH_OCT,
            .day = 12,
            .hour = 21,
            .minute = 30,
            .second = 00,
            .dow = Ds1302::DOW_WED
        };

  rtc.setDateTime(&dt);     // Set the time (hours, minutes, seconds) - Adjust accordingly
}

// Function to stop sensor readings
void stopReadings() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    deactivateRelay(i + 1);
  }
}

// Function to read the sensor values
void readSensors(int numSensors) {
  numSensors = min(numSensors, NUM_SENSORS);

  for (int i = 0; i < numSensors; i++) {
    int sensorValue = analogRead(ANALOG_PIN_BASE + i);

    if (sensorValue > sensorThresholds[i]) {
      activateRelay(i + 1);
      delay(relayDurations[i]);
      deactivateRelay(i + 1);
    }
  }
}

// Function to activate a relay
void activateRelay(int sensorNumber) {
  mcp.digitalWrite(RELAY_PIN_BASE + sensorNumber - 1, HIGH);
}

// Function to deactivate a relay
void deactivateRelay(int sensorNumber) {
  mcp.digitalWrite(RELAY_PIN_BASE + sensorNumber - 1, LOW);
}

// Function to perform daily readings at 8 PM
void performDailyReadings() {
  // Implement the logic to perform readings at 8 PM using the MH-DS1302 real-time clock (RTC) module
  // For example, you can use rtc.getTime() to get the current time and compare it with the scheduled time for readings
}
