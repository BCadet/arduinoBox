// #define LCDKEYPAD_DISABLE_TIMER
#include "LCDKeypad.hpp"

LCDKeypad lcd(8, 9, 4, 5, 6, 7, 0);

byte upArrow[] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00000
};

byte downArrow[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};

byte notSelected[] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111
};

byte selected[] = {
  B11111,
  B10001,
  B10001,
  B11011,
  B10101,
  B11011,
  B10001,
  B11111
};

void onSelectPress(void* arg)
{
    lcd.setCursor(0,1);
    lcd.write(0x04);
}

void onUpPress(void* arg)
{
    lcd.setCursor(2,0);
    lcd.write(0x01);
}

void onDownPress(void* arg)
{
    lcd.setCursor(2,1);
    lcd.write(0x02);
}

void onLeftPress(void* arg)
{
    lcd.setCursor(1,1);
    lcd.write(0x7f);
}

void onRightPress(void* arg)
{
    lcd.setCursor(3,1);
    lcd.write(0x7e);
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
    lcd.createChar(0x01, upArrow);
    lcd.createChar(0x02, downArrow);
    lcd.createChar(0x03, notSelected);
    lcd.createChar(0x04, selected);
    lcd.clear();
    Serial.println("ARDUINO BOX");
    lcd.print("ARDUINO BOX");
    delay(1000);
    lcd.clear();

    lcd.setButtonCallbacks(LCDKeypad::BUTTON_SELECT, onSelectPress, NULL, onRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_UP, onUpPress, NULL, onRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_DOWN, onDownPress, NULL, onRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_LEFT, onLeftPress, NULL, onRelease, NULL);
    lcd.setButtonCallbacks(LCDKeypad::BUTTON_RIGHT, onRightPress, NULL, onRelease, NULL);

    lcd.startButtonListener();
}

void loop()
{
    // buttonUpdater(&lcd);
}
