#ifndef SENSORS_RELAYS_H
#define SENSORS_RELAYS_H

#include "Wire.h"
#include "Adafruit_MCP23X17.h"
#include "Ds1302.h"

// Constants
const int NUM_SENSORS = 10;    // Number of sensors and relays
const int ANALOG_PIN_BASE = 0; // Starting analog pin for sensors
const int RELAY_PIN_BASE = 2;  // Starting relay pin

// Variables
extern int sensorThresholds[NUM_SENSORS];  // Threshold values for each sensor
extern int relayDurations[NUM_SENSORS];   // Duration for each relay activation

extern Adafruit_MCP23X17 mcp;  // MCP23017 object for relay control
extern Ds1302 rtc;   // DS1302 object for RTC

// Function prototypes
void initializeSensors();
void setSensorThreshold(int sensorNumber, int threshold);
void setRelayDuration(int sensorNumber, int duration);
void startReadings(int numSensors);
void stopReadings();
void readSensors(int numSensors);
void activateRelay(int sensorNumber);
void deactivateRelay(int sensorNumber);
void performDailyReadings();


#endif//
