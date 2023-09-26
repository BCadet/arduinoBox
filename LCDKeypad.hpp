#ifndef LCDKEYPAD_HPP
#define LCDKEYPAD_HPP

#include <LiquidCrystal.h>

#ifndef LCDKEYPAD_TIMER
#define LCDKEYPAD_TIMER 1
#endif

#if LCDKEYPAD_TIMER == 1
#define USE_TIMER_1     true
#define DEFAULT_TIMER ITimer1
#elif LCDKEYPAD_TIMER == 2
#define USE_TIMER_2     true
#define DEFAULT_TIMER ITimer2
#elif LCDKEYPAD_TIMER == 3
#define USE_TIMER_3     true
#define DEFAULT_TIMER ITimer3
#elif LCDKEYPAD_TIMER == 4
#define USE_TIMER_4     true
#define DEFAULT_TIMER ITimer4
#elif LCDKEYPAD_TIMER == 5
#define USE_TIMER_5     true
#define DEFAULT_TIMER ITimer5
#else 
#error "invalid LCDKEYPAD_TIMER value. must be [1,2,3,4,5]"
#endif
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
    TimerInterrupt *timer;

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
              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t analogIn = 0, TimerInterrupt *timer = & DEFAULT_TIMER)
        : LiquidCrystal(rs, enable, d0, d1, d2, d3), buttonInPin(analogIn), pressedButton(BUTTON_NONE), timer(timer)
    {
        timer->init();
        timer->attachInterruptInterval(1, buttonUpdater, this);
        timer->disableTimer();
    }

    void setButtonCallbacks(enum buttons button, void (*onPressCb)(void *), void *onPressArg, void (*onReleaseCb)(void *), void *onReleaseArg)
    {
        buttons[button].onPress = onPressCb;
        buttons[button].onPressArg = onPressArg;
        buttons[button].onRelease = onReleaseCb;
        buttons[button].onReleaseArg = onReleaseArg;
    }

    void startButtonListener() { timer->enableTimer(); }
    void stopButtonListener() { timer->disableTimer(); }
};

void buttonUpdater(LCDKeypad *lcd)
{
    const enum LCDKeypad::buttons pressedButtonCache = lcd->pressedButton;
    const uint16_t buttonValue = analogRead(lcd->buttonInPin);
    if (lcd->pressedButton != LCDKeypad::BUTTON_NONE)
    {
        if(buttonValue > 1000)
        {
            if (lcd->buttons[lcd->pressedButton].onRelease)
                lcd->buttons[lcd->pressedButton].onRelease(lcd->buttons[lcd->pressedButton].onReleaseArg);
            lcd->pressedButton = LCDKeypad::BUTTON_NONE;
        }
    }
    else
    {
        if(buttonValue > 1000) return;
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

        if (lcd->pressedButton != LCDKeypad::BUTTON_NONE && lcd->buttons[lcd->pressedButton].onPress)
            lcd->buttons[lcd->pressedButton].onPress(lcd->buttons[lcd->pressedButton].onPressArg);
    }
}

#endif