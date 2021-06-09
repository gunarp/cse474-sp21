/**
 * @file controls.hh
 * @authors Sunny Hu, Peter Gunarso
 * @brief control.cpp header file
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>


/**
 * @brief Task which manages keypad inputs, and subsequently manages system state
 *
 * @authors Sunny Hu, Peter Gunarso
 *
 * @param pvParameters Takes in pointers to TaskHandle_t's for #vNoiseSensorControl and #vTaskSerial,
 *                     will wake them up when the system switches to voice control mode.
 */
void vTaskKeypad(void * pvParameters);

/**
 * @brief Task which manages noise sensor, will send a pwm on #FanPWMQueue to change the speed of the
 *         motor based on how loud of a sound the sensor perceives.
 *
 * @authors Sunny Hu, Peter Gunarso
 *
 * @param pvParameters
 */
void vNoiseSensorControl(void * pvParameters);

/**
 * @brief Task which manages the RGB LED, which displays the current state of the system.
 *        When the LED flashes red, the system is in the voice control mode.
 *        When the LED flashes green, the system is in the keypad control mode.
 *
 * @author Muhammad A., Sunny Hu
 *
 * @param pvParameters
 */
void TaskRGB(void *pvParameters);

/**
 * @brief Helper function which sets the PWM of the RGB LED
 *
 * @author Muhammad A., Sunny Hu
 *
 * @param red_light_value red light pwm
 * @param green_light_value green light pwm
 * @param blue_light_value blue light pwm
 */
static void RGB_color(int red_light_value, int green_light_value, int blue_light_value);

#endif  // CONTROLS_H_
