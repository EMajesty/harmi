#pragma once

enum Modifiers {
    MINOR,
    MAJOR,
    AUG,
    DIM,
    SIXTH,
    MINSEVENTH,
    MAJSEVENTH,
    NINTH
};

struct Chord {
  bool minor;
  bool major;
  bool augmented;
  bool diminished;
  bool sixth;
  bool minSeventh;
  bool majSeventh;
  bool ninth;
};

const char *ROOT_NOTES[] = {"C",  "C#", "D",  "D#", "E",  "F",
                            "F#", "G",  "G#", "A",  "A#", "B"};
