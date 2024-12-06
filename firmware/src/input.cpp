#include "input.h"
#include <Keypad.h>
#include <pio_encoder.h>
#include "lcd.h"

const byte ROWS = 5;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'a','b','c','d'},
    {'e','f','g','h'},
    {'i','j','k','l'},
    {'m','n','o','p'},
    {'q','r','s','t'}
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
                char keyCode = keypad.key[i].kchar;

                switch (keypad.key[i].kstate) {
                    case PRESSED:
                        printChord(keyCode);
                        // Check for note keys
                        switch (keyCode) {
                            case 0x10 ... 0x1B:
                                // Trigger chord from note buttons
                                // Take into account chromatic/modal mode
                                break;
                        }
                        break;
                    case HOLD:
                        // Check for mod keys
                        switch (keyCode) {
                            case 0x00 ... 0x07:
                                // Add modifier to chord
                                // Retrig on mod change into toggleable setting
                                // By default only add new modifiers to next chord
                                break;
                        }
                        break;
                    case RELEASED:
                        // Use in case holdable chords get implemented
                        break;
                    case IDLE:
                        break;
                }
            }
        }
    }

    int counts = encoder.getCount();

    if (counts < 0) {
        // Clockwise
        printChord('x');
    } else if (counts > 0) {
        // Counterclockwise
        printChord('y');
    }

    encoder.reset();
}
