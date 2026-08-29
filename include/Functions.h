
#pragma once

#include "Includes.h"

TFT_eSPI tft = TFT_eSPI();

// Button class

Beeper buz(Sound_Pin);

#define Button_timeout 50
unsigned long last_time;

class Button {
   public:
    Button(uint8_t pin) : pin(pin) {
        pinMode(pin, INPUT_PULLUP);
        state = digitalRead(pin);
    }

    bool click() {
        if (uint8_t(uint8_t(millis()) - tmr) < 50) return false;

        tmr = millis();
        if (state != digitalRead(pin)) {
            state = !state;
            if (!state) return true;
        }
        return false;
    }

   private:
    const uint8_t pin;
    uint8_t tmr;
    bool state;
};
