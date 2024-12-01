#include "input.h"
#include <Keypad.h>
#include <pio_encoder.h>

const byte ROWS = 5;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'m','n','o','p'},
    {'q','r','s','t'},
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'}
};

byte rowPins[ROWS] = {26,15,14,13,12};
byte colPins[COLS] = {8,9,10,11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

PioEncoder encoder(6);

void initInput() {
    encoder.begin();
}

void loopInput() {
    if (keypad.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++) {
            if (keypad.key[i].stateChanged) {
                switch (keypad.key[i].kstate) {
                    case PRESSED:
                        break;
                    case HOLD:
                        break;
                    case RELEASED:
                        break;
                    case IDLE:
                        break;
                }
            }
        }
    }
}
