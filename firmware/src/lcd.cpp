#include "lcd.h"
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

void initLcd() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.print("Hell World");
}
