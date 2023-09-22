#ifndef LCDKEYPAD_HPP
#define LCDKEYPAD_HPP

#include <LiquidCrystal.h>

class LCDKeypad: public LiquidCrystal
{
  uint8_t buttonIn;

  public:
  LCDKeypad(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t analogIn)
    :LiquidCrystal(rs,enable,d0,d1,d2,d3)
    ,buttonIn(analogIn) {}

  enum buttonValue
  {
    RELEASED,
    SELECT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
  };

  enum buttonValue readButton() {
    uint16_t button = analogRead(buttonIn);
    if(button > 1000) return RELEASED;
    else if(button > 700) return SELECT;
    else if(button > 400) return LEFT;
    else if(button > 300) return DOWN;
    else if(button > 100) return UP;
    else return RIGHT;
  }
};

#endif