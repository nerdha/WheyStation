#ifndef ADC_HH
#define ADC_HH

#include <stdint.h>

// Initialize the analog subsystem.
void analogInit();

// Perform a power-saving analog read on the specified
// channel.  AVCC will be used as the reference voltage
// unless
uint16_t analogRead(uint8_t channel);

#endif // ADC_HH
