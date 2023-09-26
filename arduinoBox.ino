#include "LCDKeypad.hpp"

LCDKeypad lcd(8, 9, 4, 5, 6, 7, 0);

void onSelectPress(void* arg)
{
    lcd.print("SELECT");
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
}

void loop()
{
    // static uint16_t code = 0x0000;
    // put your main code here, to run repeatedly:
    // static enum LCDKeypad::buttonValue oldValue = LCDKeypad::RELEASED;
    // enum LCDKeypad::buttonValue value = lcd.readButton();
    // if (value != LCDKeypad::RELEASED)
    // {
    //     switch (value)
    //     {
    //     case LCDKeypad::RELEASED:
    //         Serial.println("RELEASED");
    //         break;
    //     case LCDKeypad::SELECT:
    //         Serial.println("SELECT");
    //         lcd.setCursor(0,0);
    //         for(uint8_t i=15;i>0;--i) lcd.print(code&(1<<i)?1:0);
    //         break;
    //     case LCDKeypad::LEFT:
    //         Serial.println("LEFT");
    //         break;
    //     case LCDKeypad::RIGHT:
    //         Serial.println("RIGHT");
    //         break;
    //     case LCDKeypad::UP:
    //         Serial.println("UP");
    //         code++;
    //         break;
    //     case LCDKeypad::DOWN:
    //         Serial.println("DOWN");
    //         if(code > 0) code--;
    //         break;
    //     }
    //     oldValue = value;
    //     lcd.setCursor(0,1);
    //     lcd.print(code);
    // }
}
