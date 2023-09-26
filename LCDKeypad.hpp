#ifndef LCDKEYPAD_HPP
#define LCDKEYPAD_HPP

#include <LiquidCrystal.h>

#define USE_TIMER_1     true
#include <TimerInterrupt.h>


class LCDKeypad;
void buttonUpdater(LCDKeypad *lcd);

class LCDKeypad : public LiquidCrystal
{
public:
    enum buttons
    {
        BUTTON_SELECT,
        BUTTON_LEFT,
        BUTTON_UP,
        BUTTON_DOWN,
        BUTTON_RIGHT,
        BUTTON_NONE
    };

private:
    uint8_t buttonInPin;

    struct button
    {
        void *onPressArg;
        void *onReleaseArg;
        void (*onPress)(void *);
        void (*onRelease)(void *);
    };

    struct button buttons[5];
    enum buttons pressedButton;

    friend void buttonUpdater(LCDKeypad *lcd);

public:
    LCDKeypad(uint8_t rs, uint8_t enable,
              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t analogIn)
        : LiquidCrystal(rs, enable, d0, d1, d2, d3), buttonInPin(analogIn), pressedButton(BUTTON_NONE)
    {
        ITimer1.init();
        ITimer1.attachInterruptInterval(1, buttonUpdater, this);
    }

    void setButtonCallbacks(enum buttons button, void (*onPressCb)(void *), void *onPressArg, void (*onReleaseCb)(void *), void *onReleaseArg)
    {
        buttons[button].onPress = onPressCb;
        buttons[button].onPressArg = onPressArg;
        buttons[button].onRelease = onReleaseCb;
        buttons[button].onReleaseArg = onReleaseArg;
    }

    void startButtonListener() {}
};

void buttonUpdater(LCDKeypad *lcd)
{
    const enum LCDKeypad::buttons pressedButtonCache = lcd->pressedButton;
    const uint16_t buttonValue = analogRead(lcd->buttonInPin);
    if (buttonValue > 1000)
    {
        if (lcd->pressedButton != LCDKeypad::BUTTON_NONE)
            if (lcd->buttons[lcd->pressedButton].onRelease)
                lcd->buttons[lcd->pressedButton].onRelease(lcd->buttons[lcd->pressedButton].onReleaseArg);
        lcd->pressedButton = LCDKeypad::BUTTON_NONE;
        return;
    }
    else if (buttonValue > 700)
        lcd->pressedButton = LCDKeypad::BUTTON_SELECT;
    else if (buttonValue > 400)
        lcd->pressedButton = LCDKeypad::BUTTON_LEFT;
    else if (buttonValue > 300)
        lcd->pressedButton = LCDKeypad::BUTTON_DOWN;
    else if (buttonValue > 100)
        lcd->pressedButton = LCDKeypad::BUTTON_UP;
    else
        lcd->pressedButton = LCDKeypad::BUTTON_RIGHT;

    if (pressedButtonCache == LCDKeypad::BUTTON_NONE)
        if (lcd->buttons[lcd->pressedButton].onPress)
            lcd->buttons[lcd->pressedButton].onPress(lcd->buttons[lcd->pressedButton].onPressArg);
}

#endif