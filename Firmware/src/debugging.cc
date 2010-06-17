#include "debugging.hh"

#include <avr/io.h>

/**
 * PC1  -  Digital output  -  Debug LED (lit high)
 * PD0  -  RXD             -  Serial debugging comms
 * PD1  -  TXD             -  Serial debugging comms
 */

// U2X0 is off (51 is default)
#define UBBR_VALUE 51

// Init debugging pins and ports
void initDebug() {
  // Init debug LED
  DDRC |= _BV(1);
  // Init UART at 9600 baud 8N1
  UBRR0H = UBBR_VALUE >> 8;
  UBRR0L = UBBR_VALUE & 0xff;

  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

// Turn the debugging LED on or off
void setDebugLED(bool on) {
  if (on) {
    PORTC |= _BV(1);
  } else {
    PORTC &= ~(_BV(1));
  }
}

// Send a debugging message
void sendDebugMsg(char* msg) {
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  while (*msg != '\0') {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = *msg;
    msg++;
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UCSR0A |= _BV(TXC0);
  loop_until_bit_is_set(UCSR0A, TXC0);
  UCSR0B = _BV(RXEN0);
}

