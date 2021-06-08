#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>

#ifndef CONTROLS_H_
#define CONTROLS_H_

// ============================================
// Keypad.ino
// ============================================

// task for keypad
void vTaskKeypad(void * pvParameters);
void vNoiseSensorControl(void * pvParameters);

#endif  // CONTROLS_H_