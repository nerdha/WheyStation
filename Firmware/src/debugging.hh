#ifndef DEBUGGING_HH
#define DEBUGGING_HH

/**
 * PC1  -  Digital output  -  Debug LED (lit high)
 */

// Init debugging pins and ports
void initDebug();

// Turn the debugging LED on or off
void setDebugLED(bool on);

#endif // DEBUGGING_HH
