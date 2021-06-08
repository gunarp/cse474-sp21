#include <Keypad.h>

#ifndef CONTROLS_H_
#define CONTROLS_H_

// ============================================
// Keypad.ino
// ============================================

// note: code from [insert website link here]
void vKeypadSetup();

// task for keypad
void vTaskKeypad(void * pvParameters);
void vNoiseSensorControl(void * pvParameters);

#endif  // CONTROLS_H_