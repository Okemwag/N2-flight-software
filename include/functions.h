#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BasicLinearAlgebra.h>
#include <WiFi.h>
#include <SD.h>
#include "global_variables.h" // header file containing variables
#include "defs.h" // header file containing constants

Adafruit_BMP085 barometer; 
Adafruit_MPU6050 accelerometer;

using namespace BLA;
/* 
* ==================== FUNCTION DECLARATION ==================== 
*/
void initializeComponents();
void getSensorReadings();
void printToSerial();
void kalman();
void connectToWifi();
void logToSD();

/*
 * ==================== CORE TASKS SEPARATION ====================
 */
TaskHandle_t Task1;
TaskHandle_t Task2;
void Task1code(void* pvParameters);
void Task2code(void* pvParameters);

/*
 * ==================== FUNCTION DEFINITIONS ====================
 */
void initializeComponents(){
  /*
   * This function checks and initializes all the sensors and components 
   * Params: none
   * Return: void
   */

  Serial.begin(BAUD_RATE);

  // Initialize BMP pressure sensor
  Serial.println("Barometer Check...");
  if(!barometer.begin()){
    Serial.println("Barometer not found...");
    while (1){
      delay(SHORT_DELAY);
    }
  }
  Serial.println("Barometer OK..."); // todo : these checks to be logged and relayed to ground as logs

  // Initialize MPU6050 accelerometer
  Serial.println("Accelerometer Check...");
  if(!accelerometer.begin()){
    Serial.println("Accelerometer not found...");
    while (1) {
      delay(SHORT_DELAY);
    }
  }
  
  Serial.println("Accelerometer OK...");
}
 
void getSensorReadings(){
  sensors_event_t a, g, temp;
  accelerometer.getEvent(&a, &g, &temp);

  // read altitude
  altitude = barometer.readAltitude(SEA_LEVEL_PRESSURE);

  // read x axis acceleration
  ax = a.acceleration.x;

  // read y axis acceleration
  ay = a.acceleration.y;

  // read z axis acceleration
  az = a.acceleration.z;  
}

void printToSerial(){
  Data = String(altitude) + "," + String(ax) + "," + String(ay) + "," + String(az);
  Serial.println(Data);  
}

void kalman(){
    //Measurement matrix
    BLA::Matrix<2, 1> Z = {altitude,
                           ay};
                           
    //Predicted state estimate
    BLA::Matrix<3, 1> x_hat_minus = A * x_hat;
    
    //Predicted estimate covariance
    BLA::Matrix<3, 3> P_minus = A * P * (~A) + Q;
    
    BLA::Matrix<3, 2> K = P_minus * (~H) * (H * P_minus * ((~H) + R)).Inverse(); // inverse here
    
    //Measurement residual
    Y = Z - (H * x_hat_minus);
    
    //Updated state estimate
    x_hat = x_hat_minus + K * Y;
    
    //Updated estimate covariance
    P = (I - K * H) * P_minus;
    Y = Z - (H * x_hat_minus);

    s = x_hat(0); // displacement
    v = x_hat(1); // velocity
    a = x_hat(2); // acceleration
}

void connectToWifi(){
  WiFi.begin(ssid, key);

  // check if connection okay
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Establishing connection to WiFi...");
    delay(SHORT_DELAY);
  }

  // connection okay
  Serial.println("Connection established...");
  Serial.println(WiFi.localIP()); 
  
}

void logToSD(){
	/*
	* ==================== Write flight data to SD card =====================
	*/
}

#endif