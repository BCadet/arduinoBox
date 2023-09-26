#include "LCDKeypad.hpp"

LCDKeypad lcd(8, 9, 4, 5, 6, 7, 0);

void onSelectPress(void* arg)
{
    lcd.print("SELECT");
}

void onUpPress(void* arg)
{
    lcd.print("UP");
}

void onSelectRelease(void *arg)
{
    lcd.clear();
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    lcd.begin(16, 2);
    lcd.clear();
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("INIT");
    lcd.print("ARDUINO BOX");

    lcd.setButtonCallbacks(LCDKeypad::BUTTON_SELECT, onSelectPress, NULL, onSelectRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_UP, onUpPress, NULL, NULL, NULL);
}

void loop()
{

}
