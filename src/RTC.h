// RTC.h

#ifndef RTC_H
#define RTC_H 
#define RTC_SDA 21
#define RTC_SCL 22

#include "RTClib.h"
#include <Adafruit_SSD1306.h>

extern RTC_DS3231 rtc;
extern bool showRTC;
extern Adafruit_SSD1306 display;

#endif

// ENDE RTC.h