// Display.cpp

#include "RTC.h"
#include "Display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Char Arrays die auf dem Display angezeigt werden
char *set_Timer_level_1[] = {"",
                "Cookify 1",
                "Cookify 2",
                "Cookify 3",
                "Cookify 4",
                "Cookify 5",
                "Cookify 6",
                "Cookify 7",
                "Cookify 8",
                "Cookify 9",
                "Cookify 10",
                ""};

char *set_Timer_level_2[] = {"Timer einstellen",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                "Timer aktiv...",
                ""};

char *set_Timer_level_3[] = {"Timer aktiv...",
                "Cookify 1",
                "Cookify 2",
                "Cookify 3",
                "Cookify 4",
                "Cookify 5",
                "Cookify 6",
                "Cookify 7",
                "Cookify 8",
                "Cookify 9",
                "Cookify 10",
                ""};

char *menu_set[] = {"Schnellauswahl",
                "Expressreis",
                "Eier weich",
                "Eier mittel",
                "Eier hart",
                "Schwarztee",
                "Dehnen",
                "Powerworkout",
                "Pizza",
                "Nudeln",
                "Studytime",
                "aktuelle Uhrzeit"};

RTC_DS3231 rtc;
bool showRTC = true;

void draw_displayStart() 
{
  int originalTextSize;
  uint16_t originalTextColor;

  display.clearDisplay();

  if (showRTC) 
  {
    // Ändern der Schriftgröße und Farbe im Display
    display.setTextSize(2);
    display.setTextColor(WHITE);  // Weiß

    DateTime now = rtc.now();
    String timeStr = String(now.hour()) + ":" + String(now.minute());

    // Textgrenzen abrufen, Berechnen von Textbreite und Texthöhe
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(timeStr, 0, 0, &x, &y, &w, &h);

    // Berechnen der Position, Zentrieren des Textes am Dispaly
    int xPos = (display.width() - w) / 2;
    int yPos = (display.height() - h) / 2;

    display.setCursor(xPos, yPos);
    display.cp437(true);
    display.println(timeStr);
  }

  // Wiederherstellen der ursprünglichen Schriftgröße und -farbe
  display.setTextSize(originalTextSize);
  display.setTextColor(originalTextColor);

  display.display();
  delay(10);
}

// ENDE Display.cpp