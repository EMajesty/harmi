#pragma once

#include <Arduino.h>
#include "config.h"

class ChordGenerator {
    public:
        ChordGenerator();
        void generateChord(byte rootNote, BaseChordType baseType, byte modifiers);
        int* getChordNotes();
        int getChordNoteCount();
        String getChordName(byte rootNote, BaseChordType baseType, byte modifiers);

    private:
        int chordNotes[8];
        int chordNoteCount;

        void createBaseChord(byte rootNote, BaseChordType baseType);
        void applyChordModifiers(byte modifiers);
};
