#define LCDKEYPAD_TIMER 1
#include "LCDKeypad.hpp"

LCDKeypad lcd(8, 9, 4, 5, 6, 7, 0);

void onSelectPress(void* arg)
{
    lcd.clear();
    lcd.print("SELECT");
}

void onUpPress(void* arg)
{
    lcd.clear();
    lcd.print("UP");
}

void onRelease(void *arg)
{
    lcd.clear();
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    lcd.begin(16, 2);
    lcd.clear();
    Serial.println("ARDUINO BOX");
    lcd.print("ARDUINO BOX");

    lcd.setButtonCallbacks(LCDKeypad::BUTTON_SELECT, onSelectPress, NULL, onRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_UP, onUpPress, NULL, onRelease, NULL);

    lcd.startButtonListener();
}

void loop()
{

}
