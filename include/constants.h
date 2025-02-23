#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Time.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_DC 8
#define OLED_CS 10
#define OLED_RESET 9

#define CHANGE_TIME_BUTTON 2
#define NEXT_BUTTON 3
#define DONE_BUTTON 4

extern Adafruit_SSD1306 display;
extern Time time;
extern char time_string[9];  // "HH:MM:SS" + null terminator
extern unsigned long previous_millis;
extern const long interval;


#endif