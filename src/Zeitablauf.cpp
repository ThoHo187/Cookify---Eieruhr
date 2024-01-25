// Zeitablauf.cpp

#include "Zeitablauf.h"
#include "Variablen.h"
#include "RotaryEncoder.h"
#include "Neopixel.h"
#include "Display.h"
#include "Timer.h"


  // Hier wird die Mehtode zur Zeitsteuerung abgerufen
void zeitsteuerung::zeitablauf(unsigned long timer, int timernummer)
  {
    unsigned long aktuelle_zeit = millis();
    if(startzeiten[timernummer] == 0)
    {
      startzeiten[timernummer]= aktuelle_zeit;
    }
    // Wenn die Differeznzeit größer als die Timerzeit ist, ist der Timer abgelaufen
    if (aktuelle_zeit-startzeiten[timernummer] >= timer)
    { 
      // NEOPixel gibt Signal aus, wenn die Zeit abgelaufen ist
      if(hauptalarmaktiv==0 or timerabgelaufen==timernummer)
      {
        // Der Hauptalarm wird für den agbelaufenen Timer gestartet^
        hauptalarmaktiv = 1;
        timerabgelaufen = timernummer;
        hauptalarm(strip.Color(0,0,127));
        // Es wird eine Alarmmeldung am Display ausgegben 
        alarmmeldung_display(timernummer);
        // Der Taster Quitieren wird abgefragt
        if(digitalRead(buttonPin)==LOW)
        {
          // Alle LEDs werden abgeschaltet
          for(int m=0; m<8; m=m+1)
              {
              strip.setPixelColor(m,0);
              }
              strip.show();
          // Timer aus Array Listetimer entfernen
          for(int i =0; i<10; i++)
          {
            if(timernummer==timeraktiv[i])
            {
              timeraktiv[i]=0;
              // Alle Zeiten werden auf Null gesetzt
              hauptalarmaktiv = 0;
              display.clearDisplay();
              display.display();
              startzeiten[timernummer]=0;
              deltazeit[timernummer]=timer;
              menu_level[timernummer-1]=1;
              delay(500);
            }           
          }
        }       
      }     
    }

    else
    {
      // Verbleibende Zeit wird während des Betriebes abgespeichert
      float delta = timer-(aktuelle_zeit-startzeiten[timernummer]);
      deltazeit[timernummer-1] = delta;      
    }
  }

// Die Methode zur Steuerung des NEOPixel aufrufen

void zeitsteuerung::lichtsteuerung(unsigned long timer, int timernummer)
{ 
  // Der NEOPixel zeigt die abgelaufende Zeit an, wenn der Timer im Display ausgewählt wurde 
  // und kein Timer abgelaufen ist (Hauptalarm)
  if(hauptalarmaktiv==0){
  // Soblad 1/7 er Zeit abgelaufen ist wird eine LED am Strip angeschaltet
  // 1.LED GRÜN 
  if(deltazeit[timernummer]<= timer and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(0, strip.Color(0,255,0));
    strip.show(); 
    //Serial.println(deltazeit[timernummer]);
  }
  // 2.LED GRÜN 
  if(deltazeit[timernummer]<= timer*0.875 and deltazeit[timernummer]>=timer*0.01 )
  {
    strip.setPixelColor(1, strip.Color(0,255,0));
    strip.show();  
  }
  // 3.LED GRÜN 
  if(deltazeit[timernummer]<= timer*0.75 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(2, strip.Color(0,255,0));
    strip.show();  
  }
  // 4.LED GRÜN 
  if(deltazeit[timernummer]<= timer*0.625 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(3,strip.Color(0,255,0) );
    strip.show();  
  }
  // 5.LED GELB
  if(deltazeit[timernummer]<= timer*0.5 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(4, strip.Color(225,225,0));
    strip.show();  
  }
  // 6.LED GELB
  if(deltazeit[timernummer]<= timer*0.375 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(5,strip.Color(255,255,0) );
    strip.show();  
  }
  // 7.LED ROT
  if(deltazeit[timernummer]<= timer*0.25 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(6, strip.Color(225,0,0));
    strip.show();  
  }
  // 8.LED ROT
  if(deltazeit[timernummer]<= timer*0.125 and deltazeit[timernummer]>=timer*0.001 )
  {
    strip.setPixelColor(7, strip.Color(255,0,0));
    strip.show();  
  }
  if(deltazeit[timernummer]<= timer*0.008 and deltazeit[timernummer]>=timer*0.0005)
  { 
    // Alle LEDs werden nun abgeschaltet, damit es zu keiner überschreitung mit den Haupalarm kommt
    for(int m =0; m<8; m=m+1)
    {
      strip.setPixelColor(m,0);
    }
    strip.show();
   // Serial.println("neopixel aus");    
  }
 }  
}

// ENDE Zeitablauf.cpp