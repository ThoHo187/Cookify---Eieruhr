// RotaryEncoder.cpp

#include "RotaryEncoder.h"
#include "Arduino.h"

#define LATCH0 0 // input state position 0
#define LATCH3 3 // input state position 3


const int8_t KNOBDIR[] = 
{
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
};

// Reset an Position [3]
// ==> rechts, hochzählen
// <== links,  runterzählen

// Initialisierung 
RotaryEncoder::RotaryEncoder(int pin1, int pin2, LatchMode mode)
{
  // Speichere Hardware Setup
  _pin1 = pin1;
  _pin2 = pin2;
  _mode = mode;

  // input pins & pullup resistor Setup
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);

  // wenn nicht mit Bewegung gestartet, RotaryEncoder Pos [3] 
  int sig1 = digitalRead(_pin1);
  int sig2 = digitalRead(_pin2);
  _oldState = sig1 | (sig2 << 1);

  // start in Position [0];
  _position = 0;
  _positionExt = 0;
  _positionExtPrev = 0;
} 

//aktuelle Auswahl von 1-12 die durch den rotary encoder ausgewählt wird
int auswahl(int anzahl, int newPos, int level_schnellauswahl)
{
  static int pos = 0;
  static int wahl = 0;

  if (level_schnellauswahl != 2)
  {
    if (pos != newPos) 
    {
    wahl = newPos % anzahl;
    if (wahl>0)
    {
      wahl = wahl - anzahl;
    }
    else
    {
      wahl = wahl;  
    }
    wahl = wahl < 0 ? -wahl : wahl; 
    }
  }
  else
  {
    wahl = wahl;
  }
  pos = newPos;
  return wahl;
}

long RotaryEncoder::getPosition()
{
  return _positionExt;
} 

// RotaryEncoderButton für MenüLevel inaktiv/aktiv schalten für einzelne Timer
int set_level(int button_status, int level_akt, int level_max)
{
    static int pre_button_status = 1;
    static int gedrueckt = 0;

    if (button_status == 0)
    {
      if (pre_button_status == 1)
      {
        gedrueckt = 1;
      }
      else
      {
        gedrueckt = 0;
      }
    }
    else
    {
      gedrueckt = 0;
    }
    pre_button_status = button_status;

    //level_max ist abhängig von der Timerart. Schnellauswahl hat 3 Level, die anderen Timer 2 Level.
    if (gedrueckt == 1)
    {
      if (level_akt <= level_max)
      {
        level_akt = level_akt +1;
      }
      else
      {
        level_akt = level_akt;
      }
    }
    if (level_akt > level_max)
    {
      level_akt = 1;
    }
    return level_akt;
  }

RotaryEncoder::Direction RotaryEncoder::getDirection()
{
  RotaryEncoder::Direction ret = Direction::NOROTATION;

  if (_positionExtPrev > _positionExt) 
  {
    ret = Direction::COUNTERCLOCKWISE;
    _positionExtPrev = _positionExt;
  } else if (_positionExtPrev < _positionExt) 
  {
    ret = Direction::CLOCKWISE;
    _positionExtPrev = _positionExt;
  } else 
  {
    ret = Direction::NOROTATION;
    _positionExtPrev = _positionExt;
  }
  return ret;
}

void RotaryEncoder::setPosition(long newPosition)
{
  switch (_mode) 
  {
  case LatchMode::FOUR3:
  case LatchMode::FOUR0:
    // nur den externen Part der Position anpassen.
    _position = ((newPosition << 2) | (_position & 0x03L));
    _positionExt = newPosition;
    _positionExtPrev = newPosition;
    break;

  case LatchMode::TWO03:
    // nur den externen Part der Position anpassen
    _position = ((newPosition << 1) | (_position & 0x01L));
    _positionExt = newPosition;
    _positionExtPrev = newPosition;
    break;
  } 
} 

void RotaryEncoder::tick(void)
{
  int sig1 = digitalRead(_pin1);
  int sig2 = digitalRead(_pin2);
  int8_t thisState = sig1 | (sig2 << 1);

  if (_oldState != thisState) {
    _position += KNOBDIR[thisState | (_oldState << 2)];
    _oldState = thisState;

    switch (_mode) {
    case LatchMode::FOUR3:
      if (thisState == LATCH3) 
      {
        // Die Hardware hat 4 steps mit einer latch am input 3
        _positionExt = _position >> 2;
        _positionExtTimePrev = _positionExtTime;
        _positionExtTime = millis();
      }
      break;

    case LatchMode::FOUR0:
      if (thisState == LATCH0) 
      {
        // Die Hardware hat 4 steps mit einer latch am input 3
        _positionExt = _position >> 2;
        _positionExtTimePrev = _positionExtTime;
        _positionExtTime = millis();
      }
      break;

    case LatchMode::TWO03:
      if ((thisState == LATCH0) || (thisState == LATCH3)) 
      {
        // Die Hardware hat 2 steps mit einer latch am input 0 & 3
        _positionExt = _position >> 1;
        _positionExtTimePrev = _positionExtTime;
        _positionExtTime = millis();
      }
      break;
    } 
  }
} 

unsigned long RotaryEncoder::getMillisBetweenRotations() const
{
  return (_positionExtTime - _positionExtTimePrev);
}

unsigned long RotaryEncoder::getRPM()
{
  // berechne max. Zeitdifferenz zwischen letztem Positionswechsel und jetzt
  unsigned long timeBetweenLastPositions = _positionExtTime - _positionExtTimePrev;
  unsigned long timeToLastPosition = millis() - _positionExtTime;
  unsigned long t = max(timeBetweenLastPositions, timeToLastPosition);
  return 60000.0 / ((float)(t * 20));
}

// Ende RotaryEncoder.cpp