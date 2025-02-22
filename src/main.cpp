#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#include "Time.h"
#include "Bitmaps.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_DC 8
#define OLED_CS 10
#define OLED_RESET 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Time time{11,50,30};
char timeStr[9];  // "HH:MM:SS" + null terminator

/**
 * Function declarations
 */

void init_time();


/**
 * Setup
 */
void setup() 
{
	Serial.begin(9600);

    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }

    display.display();
    display.clearDisplay();

	display.drawBitmap(
	(128 - 48) / 2,
	(64 - 48) / 2,
	apple_logo_bmp2, 48, 48, WHITE);

    display.display();
    delay(2000);

    init_time();
    delay(1000);

}


/**
 * Main loop
 */
void loop() 
{
    display.clearDisplay();
    
    delay(1000);
    time++;

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE); 

    int text_width{strlen(timeStr) * 12};
    int x{(SCREEN_WIDTH - text_width) / 2};
    int y{(SCREEN_HEIGHT - 16) / 2};
    display.setCursor(x,y);
    sprintf(timeStr, "%02d:%02d:%02d", time.get_hour(), time.get_minute(), time.get_second());
    display.print(timeStr);
    display.display();
}



/**
 * Function implementations
 */
void init_time()
{
    Serial.println("init_time() is running..."); 
    display.clearDisplay();
    display.display();
    delay(200);

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(1,0);
    display.print(F("Please enter time:"));
    display.display();

    delay(300);


    display.setTextSize(1);
    int text_width{strlen(timeStr) * 12};
    int x{(SCREEN_WIDTH - text_width) / 2};
    int y{(SCREEN_HEIGHT - 16) / 2};
    display.setCursor(40,40);
    sprintf(timeStr, "%02d:%02d:%02d", time.get_hour(), time.get_minute(), time.get_second());
    display.print(timeStr);
    display.display();

}