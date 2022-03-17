
#include <Arduino.h>
/*
 * Check brownout issues to prevent ESP32 from re-booting unexpectedly
 */
#include "../include/functions.h"

/*
 * ==================== CORE TASKS SEPARATION ====================
 */
TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1Code(void* pvParameters){
  for(;;){

      // read sensors
    getSensorReadings();

    // send data to ground station
    serveData();
  
    // print Sensor values for debugging
    printToSerial();
	
    // Write sensor reading to SD card
    //logToSD();
  }

}

void Task2Code(void* pvParameters){
  for(;;){
    // kalmanUpdate();
    // detectLiftoff();
    // detectApogee();
  }
}


void setup() {
  tm = millis(); // read current time when this function is calles
  

  initializeComponents();
  createAccessPoint();

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", getSensorReadings().c_str());
  });

  Serial.println("DATA: " + sensor_data);

  // initialize core tasks
  xTaskCreatePinnedToCore(Task1Code, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(Task2Code, "Task2", 10000, NULL, 1, &Task2, 1);

}

void loop() {}





