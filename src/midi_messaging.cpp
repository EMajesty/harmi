#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

void initMidi() { usbMIDI.begin(MIDI_CHANNEL_OMNI); }
void loopMidi() {
    usbMIDI.sendNoteOn(42, 127, 1);
    delay(1000);
    usbMIDI.sendNoteOff(42, 0, 1);
    delay(1000);
}
