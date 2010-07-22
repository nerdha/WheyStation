#include "debugging.hh"

#include <avr/io.h>

/**
 * PC1  -  Digital output  -  Debug LED (lit high)
 */

// Init debugging pins and ports
void initDebug() {
  // Init debug LED
  DDRC |= _BV(1);
}

// Turn the debugging LED on or off
void setDebugLED(bool on) {
  if (on) {
    PORTC |= _BV(1);
  } else {
    PORTC &= ~(_BV(1));
  }
}

