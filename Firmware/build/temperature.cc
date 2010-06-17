#include "temperature.hh"

#include <avr/io.h>

#define VREF_INTERNAL ( _BV(REFS1) | _BV(REFS0) )
#define VREF_AVCC _BV(REFS0)

#define VREF VREF_INTERNAL

// Select the ADC prescaler.  @8MHz, we use a
// prescaler of clk/128.
#define ADC_PRESCALER ( _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) )

// Initialize temperature measuring
void initTempurature() {
  // no initialization needs to be done.
}

// Convert a raw ADC value to an approximate temperature.
int rawToCelsius(int raw) {
  // voltage in mV = raw * 1.1V/1024
  // T = ((1.1*1000/1024)*raw - 242) * 70/72
  // We could go through floats, but this works out to about
  // T ~= raw - 236
  return raw-236;
}

// Return the approximate temperature in C
int measureTemperature() {
  // Check that there's no sampling in progress (omitted)
  // Select channel in ADMUX.
  ADMUX = VREF | _BV(MUX3);
  // Start conversion: write 1 to ADSC.
  ADCSRA = _BV(ADEN) | _BV(ADSC) | ADC_PRESCALER;
  loop_until_bit_is_clear(ADCSRA,ADSC);
  int raw = ADCW;
  return rawToCelsius(raw);
}
