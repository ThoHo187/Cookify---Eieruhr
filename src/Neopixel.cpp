// Neopixel.cpp

#include "Neopixel.h"

// NeoPixel initialisieren(Anzahl LEDs, SignalPin, RGB Daten)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, rgb_buspin, NEO_GRB + NEO_KHZ800);

unsigned long zeit_1_hauptalarm =0;
unsigned long zeit_2_hauptalarm =0;
// Funktion Hauptalarm (Blinken NEOPixel)
void hauptalarm(uint16_t p)
{
  // Es wird über die millis funktion ein Blinktakt mit der Frequenz von 1 Herz erzeugt
  unsigned long aktuelle_zeit_1 = millis();
  if(aktuelle_zeit_1-zeit_1_hauptalarm >1000)
  { 
      zeit_1_hauptalarm = aktuelle_zeit_1;
      // Der NEOPixel wird angeschaltet
      for(int n=0; n<8; n= n+1)
      {
        strip.setPixelColor(n, p); 
      }
      strip.show();
      
      unsigned long aktuelle_zeit_2= millis();
    
    if(aktuelle_zeit_2 - zeit_2_hauptalarm >2000)
    {
      zeit_2_hauptalarm = aktuelle_zeit_2;
      // Der NEOPixel wird abgescahltet
      for(int m=0; m<8; m=m+1)
      {
       strip.setPixelColor(m,0);
      }
      strip.show();
    }
  } 
}

// ENDE Neopixel.cpp