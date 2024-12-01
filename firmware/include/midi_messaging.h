#pragma once

#include <Arduino.h>

void initMidi();
void sendChord(byte notes[]);
void killAll();
