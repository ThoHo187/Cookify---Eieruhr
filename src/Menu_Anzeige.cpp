// MENU_ANZEIGE.h

#include "Zeitablauf.h"
#include "Variablen.h"
#include "RotaryEncoder.h"
#include "Neopixel.h"
#include "Display.h"
#include "Timer.h"
#include "NTPServer.h"
#include "Menu_Anzeige.h"

// Erstellen von Klassen, insgesamt 12 Objekte bzw. Timer/Menüs


  //Funktion für Displayanzeige
  void menu::show_menu(int menu_auswahl ,char* Timer_name, int abgelaufene_zeit, int zeit_timer, char* text_unten_level_1, char* text_unten_level_2, char* text_unten_level_3, int timer_level, int *zeigertimeraufneopixel)
  {
    static int pre_menu = 1;
    static int pre_level = 1;
    static int pre_abgelaufene_zeit = 1;
    static int pre_zeit_timer = 1;
    int minutes;
    int seconds;
    char buffer[6];
    int textWidth3;
    int zeit_in_sek = abgelaufene_zeit/1000;

    int textHeight = 8;   //Texthöhe immer 8 Pixel hoch
    int textWidth1 = strlen(Timer_name) * 6;  //Zeichenlänge immer 6 Pixel lang
    int textWidth2 = 30; //Textweite für Timer sind 30 Pixel
    if (timer_level ==1)
    {
      textWidth3 = strlen(text_unten_level_1) * 6;  // Zeichen 6 Pixel lang
    }
    if (timer_level ==2)
    {
      textWidth3 = strlen(text_unten_level_2) * 6;  // Zeichen ist 6 Pixel lang
    }
    if (timer_level ==3)
    {
      textWidth3 = strlen(text_unten_level_3) * 6;  // Zeichen ist 6 Pixel lang
    }
    // Bei Menüänderung zu Begin NEOPixel abschalten.
    if(pre_menu != menu_auswahl)
    {
      // NEOPixel abschalten 
        for(int i =0; i<8; i=i+1)
        {
          strip.setPixelColor(i,0);
        }
        strip.show();
    }
    // bei Schnellauswahl:
    if ( menu_auswahl != 0)
    {
      // Wenn Timer aktiv: durch Invetieren des Displays Timer herausheben & auf Variable zeit_in_sek umgestellt werden.
      if (timer_level == 2)
      {
        display.invertDisplay(true);
        minutes = zeit_in_sek/60;
        seconds = zeit_in_sek%60;
        // Ausgabe NEOPixel
        *zeigertimeraufneopixel = menu_auswahl+1;
      }
      // Wenn der Timer nicht aktiv: Anzeige der Variable zeit_timer
      else
      {
        display.invertDisplay(false);
        minutes = zeit_timer/60;
        seconds = zeit_timer%60;
        *zeigertimeraufneopixel=0;
        for(int i =0; i<8; i=i+1)
        {
          strip.setPixelColor(i,0);
        }
        strip.show();
      }
    } 

    //wenn ein normaler Timer (nicht Schnellauswahl) angewählt ist:
    if ( menu_auswahl == 0)
    {
      if (timer_level == 1)
      {
        display.invertDisplay(false);
        minutes = zeit_timer/60;
        seconds = zeit_timer%60;
        *zeigertimeraufneopixel=0;
        for(int i =0; i<8; i=i+1)
        {
          strip.setPixelColor(i,0);
        }
        strip.show();
      }
      else if (timer_level == 2)
      {
        display.invertDisplay(false);
        minutes = zeit_timer/60;
        seconds = zeit_timer%60;
        *zeigertimeraufneopixel=0;
        for(int i =0; i<8; i=i+1)
        {
          strip.setPixelColor(i,0);
        }
        strip.show();
      }
      else if (timer_level == 3)
      {
        display.invertDisplay(true);
        minutes = zeit_in_sek/60;
        seconds = zeit_in_sek%60;
        // Der NEOPixel wird ausgegeben
        *zeigertimeraufneopixel = menu_auswahl+1;
      }    
    }

    std::sprintf(buffer, "%02d:%02d", minutes, seconds);
    // Bei Änderung eines Displayparameters soll folgendes Programm abgerufen werden  
    // Verhindern die Beeinflussung der Laufzeiten durch display.display
    if (pre_menu != menu_auswahl || pre_level != timer_level || pre_abgelaufene_zeit != abgelaufene_zeit || pre_zeit_timer != zeit_timer || menu_auswahl==11)
    {
        display.drawRect(0,0,128,18, SSD1306_WHITE);
        display.drawRect(0,18,128,28, SSD1306_WHITE);
        display.drawRect(0,46,128,18, SSD1306_WHITE);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(64 - textWidth1/2, 9 - textHeight/2);
        display.println(Timer_name);
        display.setCursor(64 - textWidth2/2, 32 - textHeight/2);
        
      
      if (menu_auswahl != 11)
      {
        display.println(buffer);
      }
      else
      {
        menuetageszeit();
      }
      if (timer_level == 1)
      {
        display.setCursor(64 - textWidth3/2, 55 - textHeight/2);
        display.println(text_unten_level_1);
      }
      if (timer_level == 2)
      {
        display.setCursor(64 - textWidth3/2, 55 - textHeight/2);
        display.println(text_unten_level_2);
      }
      if (timer_level == 3)
      {
        display.setCursor(64 - textWidth3/2, 55 - textHeight/2);
        display.println(text_unten_level_3);
      }
      display.display(); // Aktualisiert das Display
    }
      pre_menu = menu_auswahl;
      pre_level = timer_level;
      pre_abgelaufene_zeit = abgelaufene_zeit;
      pre_zeit_timer = zeit_timer;
  }

// ENDE MENU_ANZEIGE.cpp