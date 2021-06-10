/**
 * @file 4.2.h
 * @authors Peter Gunarso, Sunny Hu
 * @brief Project Header file
 * @version 0.1
 * @date 2021-06-09
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef PROJ_H_
#define PROJ_H_

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "servos.hh"
#include "controls.hh"
#include "fan.hh"
#include "serial.hh"

#define SERIALDELAY 200
#define KEYPADDELAY 20
#define SENSORPERIOD 40

/**
 * @brief Allow any cpp files who include this header file to access the ServoCommandQueue
 *
 */
extern QueueHandle_t ServoCommandQueue;

/**
 * @brief Allow any cpp files who include this header file to access the FanCommandQueue
 *
 */
extern QueueHandle_t FanCommandQueue;

/**
 * @brief Allow any cpp files who include this header file to access the FanPWMQueue
 *
 */
extern QueueHandle_t FanPWMQueue;

/**
 * @brief Allow any cpp files who include this header file to access the system state
 *
 */
extern int mode;

#endif  // PROJ_H_
