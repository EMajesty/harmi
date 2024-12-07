#pragma once

enum Mode { CHROMATIC, MODAL };

// Base chord types (mutually exclusive)
enum BaseChordType { MINOR, MAJOR, AUGMENTED, DIMINISHED };

// Additional modifiers (combinable)
enum ChordModifier {
  NO_MODIFIER = 0,
  ADD6 = 1 << 0,
  MINOR7 = 1 << 1,
  MAJOR7 = 1 << 2,
  ADD9 = 1 << 3
};

// Mod indices
const int MODIFIER_BASE_MINOR = 0;
const int MODIFIER_BASE_MAJOR = 1;
const int MODIFIER_BASE_AUG = 2;
const int MODIFIER_BASE_DIM = 3;
const int MODIFIER_ADD6 = 4;
const int MODIFIER_MINOR7 = 5;
const int MODIFIER_MAJOR7 = 6;
const int MODIFIER_ADD9 = 7;
