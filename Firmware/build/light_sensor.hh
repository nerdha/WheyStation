#ifndef LIGHT_SENSOR_HH
#define LIGHT_SENSOR_HH

/**
 * PD2  -	 Digital input	 -  CdS light sensor
 */

// Initialize the light sensor
void initLight();

// Get the current state of the light sensor
// (true indicates light present; false darkness).
bool isLight();

// Sleep to save power until the light is again
// detected.
void sleepUntilLight();

#endif // LIGHT_SENSOR_HH
