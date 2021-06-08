#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>



// task for keypad
void vTaskKeypad(void * pvParameters);
void vNoiseSensorControl(void * pvParameters);

void RGB_color(int red_light_value, int green_light_value, int blue_light_value);
void TaskRGB(void *pvParameters);

#endif  // CONTROLS_H_
