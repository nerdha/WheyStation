
// The WheyStation will use the AVR's internal oscillator at
// 8MHz.
#define F_CPU 8000000UL
#include "debugging.hh"
#include "weigh.hh"
#include "temperature.hh"
#include "light_sensor.hh"
#include "hard_sleep.hh"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include "xbee.hh"

// General outline of operation:
// * Send reset message.
// * Loop:
//  * If light is off, sleep until light comes on again
//  * Check weight
//  * Check temp
//  * Report both
//  * Sleep 1s
int main( void )
{
  initDebug();
  initWeigh();
  initTempurature();
  initLight();
  initXBee();

  send("good morning.  milk?\r\n");
  while(1) {
    if (!isLight()) {
      setDebugLED(false);
      sleepUntilLight();
      setDebugLED(true);
    }
    float weight = weigh();
    char buffer[30];
    sprintf(buffer,"Weight %d.\r\n",(int)weight);
    send(buffer);
    sprintf(buffer,"Calibration %x.\r\n",(int)OSCCAL);
    send(buffer);
    int temperature = measureTemperature();
    sprintf(buffer,"Temp %d.\r\n",temperature);
    send(buffer);
    sleep_1s();
  }
  return 0;
}
