// MENU_ANZEIGE.h 

#ifndef Menu_Anzeige_H
#define Menu_Anzeige_H 


class menu
{
private:

public:
    void show_menu(int menu_auswahl ,char* Timer_name, int abgelaufene_zeit, int zeit_timer,
     char* text_unten_level_1, char* text_unten_level_2, char* text_unten_level_3, int timer_level,
      int *zeigertimeraufneopixel);

};

#include <Arduino.h>
#endif

// ENDE MENU_ANZEIGE.h

