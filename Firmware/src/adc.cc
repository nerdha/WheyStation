#include "adc.hh"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


#define VREF_INTERNAL ( _BV(REFS1) | _BV(REFS0) )
#define VREF_AVCC _BV(REFS0)

// Select the ADC prescaler for internal sources.  @8MHz, we use a
// prescaler of clk/128.
#define ADC_INTERNAL_PRESCALER ( _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) )

// Select the ADC prescaler for external sources.  @8MHz, we use a
// prescaler of clk/64.
#define ADC_EXTERNAL_PRESCALER ( _BV(ADPS2) | _BV(ADPS1) )

uint16_t analogRead(uint8_t channel) {
  // Check that there's no sampling in progress (omitted)
  // Turn off analog power saving
  PRR &= ~(_BV(PRADC));
  bool internal = (channel == 8);
  // Select channel in ADMUX.
  if (internal) {
    // The temperature sensor requires the internal
    // voltage reference
    ADMUX = VREF_INTERNAL | channel;
  } else {
    // Use AVCC for external signals
    ADMUX = VREF_AVCC | channel;
  }
  uint8_t prescaler = internal?ADC_INTERNAL_PRESCALER:ADC_EXTERNAL_PRESCALER;
  // Turn on ADC interrupt to wake chip when conversion
  // is done.
  ADCSRA = _BV(ADEN) | prescaler | _BV(ADIE);
  // Start conversion: write 1 to ADSC.  Do we need this when entering sleep mode?
  // ADCSRA |= _BV(ADSC);
  // Go into sleep mode until conversion is done
  set_sleep_mode(SLEEP_MODE_ADC);
  sei();
  sleep_mode();
  // Turn on analog power saving
  PRR |= _BV(PRADC);
  return ADCW;
}

ISR(ADC_vect) {
  // Wakeup
}
