// NTPServer.h

#include <Wire.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#ifndef NTPServer_H
#define NTPServer_H

extern const char* ntpServerIP ;
extern const long  gmtOffset_sec;
extern const int   daylightOffset_sec;
extern const char* PARAM_INPUT;

extern AsyncWebServer server;

void menuetageszeit();

#endif

// ENDE NTPServer.h