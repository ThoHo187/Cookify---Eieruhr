// RTC.h

#ifndef Variablen_H
#define Variablen_H

extern int deltazeit[15];
extern int startzeit[15];
extern unsigned long startzeiten[15];  // Beachten Sie den korrekten Datentyp und die Array-Größe
extern int timeraktiv[15];  // Beachten Sie den korrekten Datentyp und die Array-Größe
extern bool hauptalarmaktiv;
extern int timerabgelaufen;
extern int timeramneopixel;
extern int programmstart;
extern int menu_levels_const[];
extern int menu_level[15];  // Beachten Sie den korrekten Datentyp und die Array-Größe
extern int anzahl_menu;

#endif
