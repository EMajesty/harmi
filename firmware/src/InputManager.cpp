#include "InputManager.h"
#include "Keypad.h"
#include "config.h"
#include "pio_encoder.h"

char keys[KEY_ROWS][KEY_COLS] = {{0, 1, 2, 3},
                                 {4, 5, 6, 7},
                                 {8, 9, 10, 11},
                                 {12, 13, 14, 15},
                                 {16, 17, 18, 19}};

byte rowPins[KEY_ROWS] = {26, 15, 14, 13, 12};
byte colPins[KEY_COLS] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEY_ROWS, KEY_COLS);
PioEncoder encoder(6);

void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
  case PRESSED:
    break;
  case RELEASED:
    break;
  case HOLD:
    break;
  case IDLE:
    break;
  }
}

InputManager::InputManager() {}

void InputManager::init() {
  encoder.begin();
  keypad.addEventListener(keypadEvent);
}

int InputManager::getNotePressed() { return currentNote; }

BaseChordType InputManager::getBaseChordType() {
  // Check mutually exclusive base type modifiers
  if (modifierStates[MODIFIER_BASE_MINOR])
    return MINOR;
  if (modifierStates[MODIFIER_BASE_MAJOR])
    return MAJOR;
  if (modifierStates[MODIFIER_BASE_AUG])
    return AUGMENTED;
  if (modifierStates[MODIFIER_BASE_DIM])
    return DIMINISHED;

  // Default to major if no base type selected
  return MINOR;
}

byte InputManager::getChordModifiers() {
  byte modifiers = NO_MODIFIER;

  if (modifierStates[MODIFIER_ADD6])
    modifiers |= ADD6;
  if (modifierStates[MODIFIER_MINOR7])
    modifiers |= MINOR7;
  if (modifierStates[MODIFIER_MAJOR7])
    modifiers |= MAJOR7;
  if (modifierStates[MODIFIER_ADD9])
    modifiers |= ADD9;

  return modifiers;
}
