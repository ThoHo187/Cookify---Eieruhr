// main.cpp

#include <Arduino.h>
#include <map>
#include "RotaryEncoder.h"
#include "RTC.h"
#include "Display.h"
#include "Timer.h"
#include "Neopixel.h"
#include "NTPServer.h"
#include "Wlan.h"  
#include "WebServer.h"
#include "Zeitablauf.h"
#include "Menu_Anzeige.h"

// Methode der Bilbiothek RotaryEncoder aufrufen
RotaryEncoder encoder_zaehler(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

// Systemvariablen
int deltazeit[15]={0};
int startzeit[15]={60, 60, 120, 180, 240, 300, 360, 420, 480, 540, 600, 1111};
unsigned long startzeiten[15]={0};
int timeraktiv[15]={};
bool hauptalarmaktiv = false;
int timerabgelaufen = 0;
int timeramneopixel=3;
int programmstart =0;
int menu_levels_const[] = {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
int menu_level[15]={1,1,1,1,1,1,1,1,1,1,1,1};
int anzahl_menu = 12;

AsyncWebServer server(80);

// Funktion RotaryEncoder auslesen
int rotary_encoder()
{
  encoder_zaehler.tick();
  int newPos = encoder_zaehler.getPosition();
  return newPos;
}

void setup() 
{
  // Serial Monitor initlaisieren
  Serial.begin(115200);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // nicht weitermachen, Dauerloop
  }

  display.clearDisplay();
    (display.width()  - LOGO_WIDTH),
    (display.height() - LOGO_HEIGHT),
    draw_displayStart();
  display.display();
  delay(5000);  

 // Connect to Wi-Fi
  Serial.println("Connecting to WiFi.");
  WiFi.begin(ssid,  password);
    while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Done!");

  // IP Adresse des ESPs ausgeben
  Serial.println(WiFi.localIP());

  // Init und Zeitaufruf
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServerIP);
 
  // NEOPixel initialisieren 
  strip.begin();
  strip.setBrightness(10);
  strip.show(); // Initialisieren, alle Pixel auf 'off'

  // RotaryEncoder Button Initialisieren 
  pinMode(buttonPin,INPUT_PULLUP);

  // Route für die Wurzel-URL ("/")
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
    request->send(200, "text/html", htmlContent);
    });

  // Start des Werbservers auf den ESP
  server.begin();
}

void loop()
{

  // Hier werden die Timer, welche im Menu gestartet wurden, in das Array übertragen
  // welcher die Mehtode Zeitablauf aufrufen 
  for(int i =0; i<11; i++)
  {

    if (i!=0)
    {
      if(menu_level[i]==2)
      {
        timeraktiv[i]=i+1;
      }
    }

    if (i==0)
    {
      if(menu_level[i]==3)
      {
        timeraktiv[i]=i+1;
      }
    }
    
    if(menu_level[i]== 1)
    {
      timeraktiv[i]=0;
      startzeiten[i+1]=0;
      deltazeit[i]=startzeit[i];
    }
    if(menu_level[i]== 2 && i == 0)
    {
      timeraktiv[i]=0;
      startzeiten[i+1]=0;
      deltazeit[i]=startzeit[i];
    }

    
    if(menu_level[i]==3  and i == 0)
    {
      timeraktiv[i]= i+1;
    }
   
  }
  display.clearDisplay();

  // RotaryEncoder Schalter;
  menu Menu[15];
  //Einlesen des RotaryEncoderButtons.
  int buttonState = digitalRead(buttonPin);
  //menu_auswahl am Anfang auf 0 und level_akt auf 1 damit kein Timer läuft
  static int menu_auswahl = 0;
  static int level_akt = 1;

  //millis Funktion für die Timer Schnellauswahl 
  unsigned long time = millis();
  //Funktionsaufruf für den RotaryEncoder
  int pos_encoder = rotary_encoder();

//Funktionsaufrufe für die Timerauswahl, Timer aktivieren/deaktivieren und Auswahl des Schnellauswahl Timers
  menu_auswahl = auswahl(anzahl_menu, pos_encoder, menu_level[0]);
  menu_level[menu_auswahl] = set_level(buttonState, menu_level[menu_auswahl], menu_levels_const[menu_auswahl]);
  startzeit[0] = schnellauswahl_set_timer(menu_auswahl, time, pos_encoder, startzeit[0], menu_level[0], deltazeit[0]);
  
  
  // Hauptmenü kann aufgerufen werden sobald kein Timer aktiv ist. Ist ein Timer aktiv, so wird das Menu gespertt und die Alarmmeldung angzeigt
  if(hauptalarmaktiv ==0)
  {

    Menu[menu_auswahl].show_menu(menu_auswahl, menu_set[menu_auswahl], deltazeit[menu_auswahl], startzeit[menu_auswahl], set_Timer_level_1[menu_auswahl], set_Timer_level_2[menu_auswahl], set_Timer_level_3[menu_auswahl], menu_level[menu_auswahl], &timeramneopixel);
  }
  
  // Es wird in der Variable "objekte" die aktiven Timer als string gespeichert
  std::map<std::string, zeitsteuerung> objekte;

  if(programmstart==0)
  {

    // Dies passiert einmalig bei Start des ESPs, um die Laufzeit zu reduzieren
    // Initialiserung in der Objekte der Klasse Zeitsteuerung
    for(int i=0; i<11;i++)
    {
      objekte[timernamen_klasse[i]]= zeitsteuerung();
    } 
  programmstart =1;
  }
  
// Die Methode zeitablauf wird aufgerufen, wenn ein Timer abläuft
  for(int nx=0; nx<11; nx++)
  { 
    int mk = timeraktiv[nx];
    
    if(mk>0)
    { 
      std:: string objName = timernamen_klasse[mk-1];
      objekte[objName].zeitablauf(startzeit[mk-1]*1000,mk);
      // Die Methode zur Anzeige der NEOPixel wird aufgerufen, wenn der zugehörige Timer aktiv ist
      if(mk== timeramneopixel)
      {
      objekte[objName].lichtsteuerung(startzeit[mk-1]*1000,mk-1);
      }
    }
  }
} 

// ENDE  main.cpp