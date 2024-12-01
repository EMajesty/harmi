#include "midi_messaging.h"
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

void initMidi() { usbMIDI.begin(MIDI_CHANNEL_OMNI); }

void sendChord(byte notes[]) {
  int size = sizeof(notes) / sizeof(notes[0]);
  killAll();
  for (int i = 0; i < size; i++) {
    usbMIDI.sendNoteOn(notes[i], 127, 1);
  }
}

// stupid
void killAll() {
  for (int i = 0; i < 128; ++i) {
    usbMIDI.sendNoteOff(i, 0, 1);
  }
}
