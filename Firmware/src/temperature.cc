#include "temperature.hh"
#include "adc.hh"

#include <avr/io.h>

#define TEMPERATURE_CHANNEL 8

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
  int raw = analogRead(TEMPERATURE_CHANNEL);
  return rawToCelsius(raw);
}
