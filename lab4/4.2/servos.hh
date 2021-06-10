/**
 * @file servos.hh
 * @author Peter Gunarso, Sunny Hu
 * @brief header file to organize items used for controlling servos
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef SERVO_H_
#define SERVO_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// pins to operate servos with
#define HSERVPIN 7
#define VSERVPIN 6
// degrees to move per command
#define STEP 25

#define MINPWM 1330
#define MAXPWM 1530
#define CENTERPWM 1430

/**
 * @brief Enum representing the possible commands to give to the servo motors
 *        IN, OUT, LEFT, and RIGHT all modify the servo's positions by at most STEP microseconds,
 *        NONE does nothing, and SERV_RESET will reset the positions back to CENTERPWM
 *
 */
enum ServoCommand {NONE, SERV_RESET, IN, OUT, LEFT, RIGHT};

/**
 * @brief Prepares the servo pins for output use, also sets the servos into neutral position
 *        and readies the #ServoCommandQueue for communication
 * @authors Peter Gunarso, Sunny Hu
 */
void vServoSetup();

/**
 * @brief Will wait until a value can be read from the #ServoCommandQueue, if it is able to read
 *        something from the queue, this task modifies the positions of the servos accordingly, see #ServoCommand
 *        for a description of the available commands.
 * @authors Peter Gunarso, Sunny Hu
 *
 * @param pvParameters Default FreeRTOS parameter passing method, vTaskServo doesn't take any parameters, though.
 */
void vTaskServo(void * pvParameters);

#endif  // SERVO_H_
