#include "weigh.hh"

#include <avr/io.h>

/**
 * PC0  -  Analog input    -  Output from instrumentation amp
 */

#define VREF_INTERNAL ( _BV(REFS1) | _BV(REFS0) )
#define VREF_AVCC _BV(REFS0)

#define VREF VREF_INTERNAL

// Select the ADC prescaler.  @8MHz, we use a
// prescaler of clk/64.
#define ADC_PRESCALER ( _BV(ADPS2) | _BV(ADPS1) )

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
  ADMUX = VREF | 0;
  // Start conversion: write 1 to ADSC.
  ADCSRA = _BV(ADEN) | _BV(ADSC) | ADC_PRESCALER;
  loop_until_bit_is_clear(ADCSRA,ADSC);
  return (float)ADCW;
}
