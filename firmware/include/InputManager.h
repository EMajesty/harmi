#pragma once

#include "config.h"
#include <Arduino.h>
#include <Keypad.h>

const byte KEY_ROWS = 5;
const byte KEY_COLS = 4;

void keypadEvent(KeypadEvent key);

class InputManager {
public:
  InputManager();
  void init();
  int getNotePressed();
  BaseChordType getBaseChordType();
  byte getChordModifiers();

private:
  int currentNote;
  bool modifierStates[8];
};
