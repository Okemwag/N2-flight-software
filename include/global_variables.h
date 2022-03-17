#include "defs.h";
#ifndef GLOBALVARIABLES_H

#define GLOBALVARIABLES_H

/*
 * =================== STATE VARIABLES ====================
 */


int currentState = PRELAUNCH_STATE;

/*
 * =================== POSITION VARIABLES ====================
 */
float altitude, velocity, acceleration, ax, ay, az, kalmanAltitude;
float s, v, a;
float longitude, latitude;

/*
 * =================== KALMAN MATRIXES ====================
 */

float q = 0.0013;

// The system dynamics
BLA::Matrix<3, 3> A = {1.0, 0.1, 0.005,
                       0, 1.0, 0.1,
                       0, 0, 1.0};

// Relationship between measurement and states
BLA::Matrix<2, 3> H = {1.0, 0, 0,
                       0, 0, 1.0};

// Initial posteriori estimate error covariance
BLA::Matrix<3, 3> P = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};

// Measurement error covariance
BLA::Matrix<2, 2> R = {0.25, 0,
                       0, 0.75};

// Process noise covariance
BLA::Matrix<3, 3> Q = {q, 0, 0,
                       0, q, 0,
                       0, 0, q};

// Identity Matrix
BLA::Matrix<3, 3> I = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};

BLA::Matrix<3, 1> x_hat = {1500.0,
                           0.0,
                           0.0};

BLA::Matrix<2, 1> Y = {0.0,
                       0.0};

/*
 * Wi-Fi connection variables
 */

static const char *ssid = "ground-station"; // change to credentials of the ground station WiFi
static const char *key = "password";

String sensor_data; // convert char to string
String data_message;

// set up data fetch interval variables
unsigned long previousMillis = 0;
const long interval = 2000;

AsyncWebServer server(80);

/*
 * liftoff detection variables
 */
bool is_lift_off = false;
uint previous_altitude;
uint current_altitude;

/*
 * apogee detection variables
 */
bool is_apogee = false;

// circular buffer creation
CircularBuffer<float, 5> altitude_buffer;

unsigned long tm;



#endif