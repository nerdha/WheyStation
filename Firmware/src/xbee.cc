#include "xbee.hh"


#include <avr/io.h>
#include <util/delay.h>

// U2X0 is off (51 is default)
#define UBBR_VALUE 51

// PD3 - sleep pin
void initXBee() {
  DDRD |= _BV(3);
  sleep(false);

  // Init UART at 9600 baud 8N1
  UBRR0H = UBBR_VALUE >> 8;
  UBRR0L = UBBR_VALUE & 0xff;

  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

  _delay_ms(1100);
  send("+++");
  _delay_ms(1100);
  send("ATPL2\r");
  _delay_ms(30);
  send("ATMY1\r");
  _delay_ms(30);
  send("ATDL2\r");
  _delay_ms(30);
  send("ATSM1\r");
  _delay_ms(30);
  send("ATCN\r");
  _delay_ms(30);
  sleep(true);
}

bool isSleeping() {
  // sleep == high
  return (PORTD & _BV(3)) != 0;
}

void send(char* msg) {
  if (isSleeping()) {
    sleep(false);
    _delay_ms(14);
  }
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
  sleep(true);
}

void sleep(bool s) {
  if (!s) { // wake up
    if (isSleeping()) {
      PORTD &= ~_BV(3); // wakeup = low
    }
  } else { // sleep
    if (!isSleeping()) {
      PORTD |= _BV(3); // go to sleep = high
    }
  }
}

