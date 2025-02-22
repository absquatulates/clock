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

#define CHANGE_TIME_BUTTON 2
#define NEXT_BUTTON 3
#define DONE_BUTTON 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Time time{};
char time_string[9];  // "HH:MM:SS" + null terminator
unsigned long previous_millis{};
const long interval = 1000;

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

    pinMode(CHANGE_TIME_BUTTON, INPUT);
    pinMode(NEXT_BUTTON, INPUT);
    pinMode(DONE_BUTTON, INPUT);


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
    unsigned long current_millis{millis()};

    if (current_millis - previous_millis >= interval)
    {
        previous_millis = current_millis;
        time++;

        display.clearDisplay();

        int text_width{strlen(time_string) * 12};
        int x{(SCREEN_WIDTH - text_width) / 2};
        int y{(SCREEN_HEIGHT - 16) / 2};

        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE); 
        display.setCursor(x,y);
        sprintf(time_string, "%02d:%02d:%02d", time.get_hour(), time.get_minute(), time.get_second());
        display.print(time_string);
        display.display();
    }
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




    int state{}; //0 = hour, 1 = minute, 2 = second
    

    while (true)
    {
        display.clearDisplay();
        
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE); 
        display.setCursor(1,0);
        display.print(F("Please enter time:"));

        display.setTextSize(2);

        int text_width{strlen(time_string) * 12};
        int x{(SCREEN_WIDTH - text_width) / 2};
        int y{(SCREEN_HEIGHT - 16) / 2};
        display.setCursor(x,y);

        //display.setCursor(30,40);
        sprintf(time_string, "%02d:%02d:%02d", time.get_hour(), time.get_minute(), time.get_second());
        display.print(time_string);
        display.display();

        if (digitalRead(CHANGE_TIME_BUTTON) == HIGH)
        {
            switch (state)
            {
            case 0:
                time.inc_hour();
                delay(120);
                break;

            case 1:
                time.inc_minute();
                delay(120);
                break;

            case 2:
                time.inc_second();
                delay(120);
                break;
            
            default:
                break;
            }
        }
        else if (digitalRead(NEXT_BUTTON) == HIGH)
        {
            if (state == 2)
                state = 0;
            else
                state++;

            delay(200);
        }
        else if (digitalRead(DONE_BUTTON) == HIGH)
        {
            break;
        }
        
        
    }
}