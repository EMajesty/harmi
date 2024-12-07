#include "ChordGenerator.h"
#include "config.h"

void ChordGenerator::generateChord(byte rootNote, BaseChordType baseType, byte modifiers) {
    chordNoteCount = 0;
    createBaseChord(rootNote, baseType);
    applyChordModifiers(modifiers);
}

void ChordGenerator::createBaseChord(byte rootNote, BaseChordType baseType) {
    chordNoteCount = 0;
    
    // Add root note
    chordNotes[chordNoteCount++] = rootNote;
    
    // Create base chord structure
    switch (baseType) {
        case MINOR:
            // Minor: root, minor third, perfect fifth
            chordNotes[chordNoteCount++] = rootNote + 3;  // minor third
            chordNotes[chordNoteCount++] = rootNote + 7;  // perfect fifth
            break;
        
        case MAJOR:
            // Major: root, major third, perfect fifth
            chordNotes[chordNoteCount++] = rootNote + 4;  // major third
            chordNotes[chordNoteCount++] = rootNote + 7;  // perfect fifth
            break;
        
        case AUGMENTED:
            // Augmented: root, major third, augmented fifth
            chordNotes[chordNoteCount++] = rootNote + 4;  // major third
            chordNotes[chordNoteCount++] = rootNote + 8;  // augmented fifth
            break;
        
        case DIMINISHED:
            // Diminished: root, minor third, diminished fifth
            chordNotes[chordNoteCount++] = rootNote + 3;  // minor third
            chordNotes[chordNoteCount++] = rootNote + 6;  // diminished fifth
            break;
    }
}

void ChordGenerator::applyChordModifiers(byte modifiers) {
    // Apply additional notes based on modifiers
    if (modifiers & ADD6) {
        // Add sixth
        chordNotes[chordNoteCount++] = chordNotes[0] + 9;
    }
    
    if (modifiers & MINOR7) {
        // Add minor seventh
        chordNotes[chordNoteCount++] = chordNotes[0] + 10;
    }
    
    if (modifiers & MAJOR7) {
        // Add major seventh
        chordNotes[chordNoteCount++] = chordNotes[0] + 11;
    }
    
    if (modifiers & ADD9) {
        // Add ninth
        chordNotes[chordNoteCount++] = chordNotes[0] + 14;
    }
}

String ChordGenerator::getChordName(byte rootNote, BaseChordType baseType, byte modifiers) {
    String chordName;
    
    // Convert root note to note name
    String rootNames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    chordName = rootNames[rootNote % 12];
    
    // Add base chord type
    switch (baseType) {
        case MINOR:
            chordName += "m";
            break;
        case MAJOR:
            // Major is default, no suffix needed
            break;
        case AUGMENTED:
            chordName += "aug";
            break;
        case DIMINISHED:
            chordName += "dim";
            break;
    }
    
    // Add modifiers
    if (modifiers & ADD6) chordName += "6";
    if (modifiers & MINOR7) chordName += "m7";
    if (modifiers & MAJOR7) chordName += "M7";
    if (modifiers & ADD9) chordName += "9";
    
    return chordName;
}
