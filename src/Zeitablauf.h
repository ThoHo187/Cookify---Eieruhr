// Zeitablauf.h

#ifndef Zeitablauf_H
#define Zeitablauf_H

#include <Arduino.h>  // Füge alle notwendigen Bibliotheken hinzu

class zeitsteuerung {
private:
  // Hier private Elemente deklarieren

public:
  void zeitablauf(unsigned long timer, int timernummer);
  void lichtsteuerung(unsigned long timer, int timernummer);
};


#endif // ZEITSTEUERUNG_H

// ENDE Zeitablauf.h