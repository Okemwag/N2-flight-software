#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

/*
 * =================== POSITION VARIABLES ====================
 */
float altitude, velocity, acceleration, ax, ay, az, kalmanAltitude;
float s, v, a;


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
 * data variables
 */
String Data;

/*
 * Wi-Fi connection variables
 */
 static const char* ssid = "Eduh"; // change to credentials of the ground station WiFi
 static const char* key = "password2";

#endif