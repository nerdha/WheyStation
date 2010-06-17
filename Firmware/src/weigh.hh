#ifndef WEIGH_HH
#define WEIGH_HH

/**
 * PC0  -  Analog input    -  Output from instrumentation amp
 */

// Initialize the weighing system
void initWeigh();

// Perform a measurement and return an
// approximate weight in grams
float weigh();

#endif // WEIGH_HH
