#include "MidiManager.h"
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, serialMIDI);

void MidiManager::init() {
  usbMIDI.begin(MIDI_CHANNEL_OMNI);
  serialMIDI.begin(MIDI_CHANNEL_OMNI);
}

void MidiManager::sendChord(int *notes, int noteCount) {}

void MidiManager::killAllNotes() {
  for (int i = 0; i < 128; ++i) {
    usbMIDI.sendNoteOff(i, 0, 1);
    serialMIDI.sendNoteOff(i, 0, 1);
  }
}
