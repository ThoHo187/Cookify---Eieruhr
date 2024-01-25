// Timer.h

#ifndef Timer_H
#define Timer_H

#include "time.h"

extern const char* timernamen_klasse[15];
int schnellauswahl_set_timer(int menu_auswahl, unsigned long time, int encoder_zaehler, int timer_startwert, int level, int deltazeit);
void alarmmeldung_display(int timernummer);
#endif

// ENDE Timer.h