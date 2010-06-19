#include "weigh.hh"
#include "adc.hh"

#include <avr/io.h>

/**
 * PC0  -  Analog input    -  Output from instrumentation amp
 */
#define WEIGH_CHANNEL 0

// Initialize the weighing system
void initWeigh() {
  // Set port as input.
  DDRC &= ~(_BV(0));
}

// Perform a measurement and return an
// approximate weight
float weigh() {
  // Check that there's no sampling in progress (omitted)
  // Select channel in ADMUX.
  return (float)analogRead(WEIGH_CHANNEL);
}
