#include "config.h"
#include "InputManager.h"
#include "ChordGenerator.h"
#include "MidiManager.h"
#include "DisplayManager.h"

InputManager inputManager;
ChordGenerator chordGenerator;
MidiManager midiManager;
DisplayManager displayManager;

void setup() {
    inputManager.init();
    midiManager.init();
    displayManager.init();
}

void loop() {
    int currentNote = inputManager.getNotePressed();

    if (currentNote != -1) {
        BaseChordType baseChordType = inputManager.getBaseChordType();
        byte chordModifiers = inputManager.getChordModifiers();

        chordGenerator.generateChord(currentNote, baseChordType, chordModifiers);

        int* chordNotes = chordGenerator.getChordNotes();
        int chordNoteCount = chordGenerator.getChordNoteCount();
        midiManager.sendChord(chordNotes, chordNoteCount);

        String chordName = chordGenerator.getChordName(currentNote, baseChordType, chordModifiers);
        displayManager.displayChord(chordName);
    }
}
