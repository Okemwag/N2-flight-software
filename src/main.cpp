#include <Arduino.h>

/*
 * Check brownout issues to prevent ESP32 from re-booting unexpectedly
 */
#include "../include/functions.h"


void setup() {
  initializeComponents();
  connectToWifi();

  // initialize core tasks
  xTaskCreatePinnedToCore(Task1Code, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(Task2Code, "Task2", 10000, NULL, 1, &Task2, 1);

}

void loop() {

}

void Task1Code(void* pvParameters){
  for(;;){
      // read sensors
    getSensorReadings();
  
    // print Sensor values
    printToSerial();
	
	// Write sensor reading to SD card
	logToSD();
 
  }
}

void Task2Code(void* pvParameters){
  for(;;){
    Serial.println(altitude);
  }
}