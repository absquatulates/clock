#include "display_utils.h"


void display_time()
{
    int text_width{strlen(time_string) * 12};
    int x{(SCREEN_WIDTH - text_width) / 2};
    int y{(SCREEN_HEIGHT - 16) / 2};

    display.setTextSize(2);
    display.setCursor(x,y);
    sprintf(time_string, "%02d:%02d:%02d", time.get_hour(), time.get_minute(), time.get_second());
    display.print(time_string);
    display.display();
}


void format_enter_time()
{
    display.setTextSize(1);
    display.setCursor(1,0);
    display.print(F("Please enter time:"));
}