// Display.h 

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#ifndef Display_H
#define Display_H 
#define SCREEN_WIDTH 128 // OLED display Breite, in pixels
#define SCREEN_HEIGHT 64 // OLED display Höhe, in pixels
#define OLED_RESET     4 // ResetTaster 
#define SCREEN_ADDRESS 0x3C // Adresse aus Datenblatt, 0x3D for 128x64, 0x3C for 128x32
#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128

extern Adafruit_SSD1306 display;
extern char *menu_set[];
extern char *set_Timer_level_1[];
extern char *set_Timer_level_2[];
extern char *set_Timer_level_3[];

void draw_displayStart();

#endif 

// ENDE Display.h