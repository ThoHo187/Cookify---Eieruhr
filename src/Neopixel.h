// Neopixel.h

#include <Adafruit_NeoPixel.h>

#ifndef NeoPixel_H
#define Neopixel_H
#define rgb_buspin 18
extern Adafruit_NeoPixel strip;

extern unsigned long zeit_1_hauptalarm;
extern unsigned long zeit_2_hauptalarm;
void hauptalarm(uint16_t p);

#endif

// ENDE Neopixel.h