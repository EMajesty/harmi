#include "DisplayManager.h"
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

const byte chordPos[] = {0, 0};

void DisplayManager::init() {
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.print("Hell World");
}

void DisplayManager::displayChord(const String& chordName) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(chordName);
}
