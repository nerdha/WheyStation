#include "light_sensor.hh"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

/**
 * PD2  -	 Digital input	 -  CdS light sensor
 * This pin goes high when illuminated, low when not.
 */

// Initialize the light sensor
void initLight() {
  DDRD &= ~(_BV(2));
}

// Get the current state of the light sensor
// (true indicates light present; false darkness).
bool isLight() {
  return ( (PIND & _BV(2)) != 0 );
}

// Set the interrupt on the light sensor pin
// to wake the chip on the PD1/PCINT18 pin going
// low.
// N.B.: because of the inversion of levels we use
// PCINT18 instead of INT0 on the same pin.
void sleepUntilLight() {
  // Trigger on level change
  cli();
  PCMSK2 |= _BV(PCINT18);
  PCICR |= _BV(PCIE2);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sei();
  sleep_mode();
  cli();
  PCMSK2 &= ~_BV(PCINT18);
  PCICR &= ~_BV(PCIE2);
  sei();
}

ISR(PCINT2_vect) {
}
