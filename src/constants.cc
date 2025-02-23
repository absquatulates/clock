#include "constants.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Time time{};
char time_string[9];  // "HH:MM:SS" + null terminator
unsigned long previous_millis{};
const long interval = 1000;