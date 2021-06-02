#include "4.2.h"
#include <Keypad.h>

#ifndef KEYPAD_H_
#define KEYPAD_H_

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// note: code from [insert website link here]
void keypadSetup();

// task for keypad
void taskKeypad();



#endif // KEYPAD_H_