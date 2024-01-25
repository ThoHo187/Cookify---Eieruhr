// Timer.cpp

#include "Timer.h"
#include "RotaryEncoder.h"
#include "Display.h"

const char*  timernamen_klasse[15]={"Timer alg.","Cookify", "Timer2", "Timer3", "Timer4", "Timer5", "Timer6", "Timer7", "Timer8", "Timer9", "Timer10"};

//Funktion für das Einstellen der Zeit des Schnellauswahlimers über RotaryEncoder
int schnellauswahl_set_timer(int menu_auswahl, unsigned long time, int encoder_zaehler, int timer_startwert, int level, int deltazeit){

static int pre_encoder_zaehler = 0;
static int pre_menu_number = 0;
static int pre_level = 0;
static int timer_zeit = 0;
static unsigned long time_reset = 0;
unsigned long time_differenz = time - time_reset;

  if (level == 1){
    timer_zeit = timer_startwert;
  }
  
  if (level == 2 && pre_level ==1){
    
    timer_zeit = deltazeit;
  }

  if (pre_encoder_zaehler != encoder_zaehler){
    time_reset = time;
  }
  else{
    time_reset = time_reset;
  } 

  if (menu_auswahl == 0 && pre_menu_number == menu_auswahl){

    /*bei abnehmender time_differenz wird schneller am rotary encoder gedreht.Je schneller gedreht wird, 
    desto mehr Sekunden sollen pro Encoder Schritt auf die Zeit addiert werden*/

    //Timerzeit reduzieren weil Encoder nach links gedreht wird
    if (pre_encoder_zaehler +1 == encoder_zaehler)
    {  
      if (time_differenz > 100)
      {
        timer_zeit = timer_zeit -1;
      }
      else if (time_differenz > 50)
      {
        timer_zeit = timer_zeit -5;
      }
      else if (time_differenz > 25)
      {
        timer_zeit = timer_zeit -10;
      }
      else if (time_differenz > 10)
      {
        timer_zeit = timer_zeit -20;
      }
    }
    //Timerzeit erhöhen weil Encoder nach rechts gedreht wird
    else if (pre_encoder_zaehler -1 == encoder_zaehler)
    {
      if (time_differenz > 100)
      {
      timer_zeit = timer_zeit +1;
      }
      else if (time_differenz > 50)
      {
        timer_zeit = timer_zeit +5;
      }
      else if (time_differenz > 25)
      {
        timer_zeit = timer_zeit +20;
      }
      else if (time_differenz > 10)
      {
        timer_zeit = timer_zeit +40;
      }
    }
  }
  if (timer_zeit < 0)
  {
    timer_zeit = 0;
  }
  else
  {
    timer_zeit == timer_zeit;
  }

  pre_encoder_zaehler = encoder_zaehler;
  pre_menu_number = menu_auswahl;
  pre_level = level;

  return timer_zeit;
}
// Meldung am Display, dsas der Timer abgelaufen ist
void alarmmeldung_display(int timernummer)
{ 
  // Display löscchen
  display.clearDisplay();
  // Layout des Menues darstellen
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  display.drawRect(0,display.height(), display.width(), display.height()*0.5, SSD1306_WHITE);
  display.drawRect(0,0, display.width(), display.height()*0.25, SSD1306_WHITE);
  display.setTextSize(1);     
  display.setTextColor(SSD1306_WHITE); // 
  display.setCursor(35, 5);     
  display.println("Timeralarm");
  display.setTextSize(1); 
  display.setCursor(45, 20);
  // Anzeige welcher Timer abgelaufen ist
  display.println(timernamen_klasse[timernummer-1]);
  display.setCursor(35, 30);
  display.println("abgelaufen");
  display.drawRect(0,display.height()*0.75, display.width(), display.height()*0.25, SSD1306_WHITE);
  display.setTextSize(1); 
  display.setCursor(60, 52);
  display.println("OK");
  display.display(); //  
}

//ENDE  Timer.cpp