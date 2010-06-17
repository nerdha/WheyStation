#include "hard_sleep.hh"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Functions for a power-saving sleep.
// This module uses TIMER2.
#define F_CPU 8000000

// Power-save sleep of 32.768ms duration
void sleep_32ms() {
  cli();
  // Set up timer 2 interrupt: WGM normal (000)
  // Clock prescaler = 1/1024
  TCCR2A = 0;
  TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
  TIMSK2 = _BV(TOIE2);
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sei();
  sleep_mode();
  cli();
  // Turn off interrupt
  while (TCNT2 == 0) {} // Workaround for horrible bug in core
  TIMSK2 = _BV(0);
  sei();
}

// This will be slightly less than 1s (0.983s+overhead)
void sleep_1s() {
  int count = 30;
  while (count--) {
    sleep_32ms();
  }
}

ISR(TIMER2_OVF_vect) {
  // Just a wakeup
}
