#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Time.h"
#include "Bitmaps.h"
#include "display_utils.h"
#include "constants.h"



/**
 * Public variables is declared in constants.h and defined in constants.cc
 */



/*=============================================*
 *                                             *
 *            Function declarations            *
 *                                             *
 *=============================================*/

/**
 * initiate time
 */
void init_time();
int input_time(int state);





/*=============================================*
 *                                             *
 *                    Setup                    *
 *                                             *
 *=============================================*/

/**
 * Setup
 * Starting serial logging for debugging
 * Initiates buttons
 * Initiates display
 * Draws the apple logo as a loading screen
 * Initiates "time" with user input
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
    display.clearDisplay();
    display.display();
    delay(200);


    init_time();
    delay(1000);

}



/*=============================================*
 *                                             *
 *                    Loop                     *
 *                                             *
 *=============================================*/

/**
 * Main loop
 * Makes clock go tick
 * Some drifting due to millis() not being the most accurate (too slow)
 * 
 */

void loop() 
{
    unsigned long current_millis{millis()};

    if (current_millis - previous_millis >= interval)
    {
        previous_millis = current_millis;
        time++;

        display.clearDisplay();
        display_time();
    }
}


/*=============================================*
 *                                             *
 *           Function implementations          *
 *                                             *
 *=============================================*/

/**
 * Function implementations
 */

void init_time()
{
    display.setTextColor(SSD1306_WHITE); 
    format_enter_time();
    display.display();
    delay(300);

    int state{}; //0 = hour, 1 = minute, 2 = second
    while (state < 4)
    {
        display.clearDisplay();
        format_enter_time();
        display_time();
        state = input_time(state);
    }
}



int input_time(int state)
{
    if (digitalRead(CHANGE_TIME_BUTTON) == HIGH)
    {
        switch (state)
        {
        case 0:
            time.inc_hour();
            delay(150);
            break;

        case 1:
            time.inc_minute();
            delay(150);
            break;

        case 2:
            time.inc_second();
            delay(150);
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
        return 4;
    }

    return state;
}