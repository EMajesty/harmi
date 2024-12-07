#pragma once

#include "config.h"
#include <Arduino.h>

class MidiManager {
public:
  MidiManager();
  void init();
  void sendChord(int *notes, int noteCount);
  void killAllNotes();

private:
  void sendUSBMidiChord(int *notes, int noteCount);
  void sendSerialMidiChord(int *notes, int noteCount);
};
