#include <Arduino.h>
#include "midi_messaging.h"
#include "input.h"
#include "lcd.h"


void setup() {
    initMidi();
    initInput();
    initLcd();
}

void loop() {
    // loopMidi();
    // loopInput();
    // loopLcd();
}
