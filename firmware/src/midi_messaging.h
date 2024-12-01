#pragma once

#include <Arduino.h>

void initMidi();
void loopMidi();
void sendChord(byte notes[]);
void killAll();
