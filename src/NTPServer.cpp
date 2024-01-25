// NTPServer.cpp

#include "NTPServer.h"
#include "Display.h"

// Ntp-Server
const char* ntpServerIP = "de.pool.ntp.org";
const long  gmtOffset_sec = 3600;     //Mitteleuropäische Zeit
const int   daylightOffset_sec = 3600;


// Aktuelle Tageszeit über NTP-Server abrufen
void menuetageszeit()
{ 
  // die Formatierungs hinterlegung für die Uhrzeit wird aufgrufen
  struct tm timeinfo;
  // sollte die Verbindung zum NTP-Server nicht möglich sein wird folgende Meldung angezeigt
  if(!getLocalTime(&timeinfo)){
    Serial.println("NPN_Server konnte nicht erreicht werden");
    display.setCursor(35, 5);     
    display.println("Tageszeit");
    display.setTextSize(1);
    display.setCursor(30,25);
    display.println("NTP Server" ); 
    display.setCursor(20, 35);
    display.println("nicht verfuegbar");
    //display.display();   
    return;
  }
  // Bei erfolgreicher Verbindung wird die Aktuelle Uhrzeit ausgegben
  display.setTextSize(1);
  display.setCursor(30,25);
  display.println(&timeinfo,"%d %B %Y" ); 
  display.setCursor(40, 35);
  display.println(&timeinfo, "%H:%M:%S");
}

// ENDE NTPServer.cpp