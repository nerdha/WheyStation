#ifndef DEBUGGING_HH
#define DEBUGGING_HH

/**
 * PC1  -  Digital output  -  Debug LED (lit high)
 * PD0  -  RXD             -  Serial debugging comms
 * PD1  -  TXD             -  Serial debugging comms
 */

// Init debugging pins and ports
void initDebug();

// Turn the debugging LED on or off
void setDebugLED(bool on);

// Send a debugging message
void sendDebugMsg(char* msg);

#endif // DEBUGGING_HH
