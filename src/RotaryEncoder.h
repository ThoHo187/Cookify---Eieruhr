// RotaryEncoder.h

#ifndef RotaryEncoder_h
#define RotaryEncoder_h
#define PIN_IN1 32
#define PIN_IN2 35
#define buttonPin 33

#include <RotaryEncoder.h>
#include "Arduino.h"

int auswahl(int anzahl, int newPos, int level_schnellauswahl);
int set_level(int button_status, int level_akt, int level_max);

class RotaryEncoder
{
public:
  enum class Direction 
  {
    NOROTATION = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = -1
  };

  enum class LatchMode 
  {
    FOUR3 = 1, // 4 steps, Latch an Position 3 
    FOUR0 = 2, // 4 steps, Latch an Position 0 
    TWO03 = 3  // 2 steps, Latch an Position 0 & 3 
  };

  // ----- Constructor -----
  RotaryEncoder(int pin1, int pin2, LatchMode mode = LatchMode::FOUR0);

  // Positionsabruf
  long getPosition();

  //Simpler Abruf der letzten Drehrichtung, 0 = keine Drehung, 1 =  rechts, -1 = links
  Direction getDirection();

  // aktuelle Position anpassen
  void setPosition(long newPosition);

  // Funktion alle paar Milisekunden oder über Interrupts aufrufen, Handlungsstatus vom RotaryEncoder
  void tick(void);

  // Gibt die aktuell vermerkte Zeit in Millisekunden
  unsigned long getMillisBetweenRotations() const;

  // RPM Wiedergabe
  unsigned long getRPM();

private:
  int _pin1, _pin2; // Arduino pins für den Encoder.
  
  LatchMode _mode; // Latch mode vom Inizialisieren

  volatile int8_t _oldState;

  volatile long _position;        // Interne Position (4 mal _positionExt)
  volatile long _positionExt;     // Externe Position
  volatile long _positionExtPrev; // Externe Position (Nur für Richtungskontrolle)

  unsigned long _positionExtTime;     // Die Zeit des letzten Positionswechsels.
  unsigned long _positionExtTimePrev; // Die Zeit des vorherigen Positionswechsels.
};

#endif

// ENDE  RotaryEncoder.h