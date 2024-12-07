#pragma once

#include <Arduino.h>

class DisplayManager {
public:
  DisplayManager();
  void init();
  void displayChord(const String &chordName);
};
