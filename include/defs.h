#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define SEA_LEVEL_PRESSURE_HPA 1024
#define CURRENT_ALTITUDE 1524

// Timing delays
#define SHORT_DELAY 10

#define PORT 4210

#define BAUD_RATE 115200

// value to detect lift off deviation
#define LIFT_OFF_DEVIATION 2 // ideal: 50 cm

// state defs
#define PRELAUNCH_STATE 0
#define IN_FLIGHT_STATE 1
#define BURN_OUT_STATE 2
#define COASTING_STATE 3
#define APOGEE_STATE 4
#define PARACHUTE_STATE 5
#define GROUND_STATE 6

#endif