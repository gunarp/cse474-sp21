/**
 * @file serial.hh
 * @authors Peter Gunarso, Sunny Hu
 * @brief Header file for serial.cpp
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef SERIAL_H_
#define SERIAL_H_

#include <Arduino.h>
#include "4.2.h"

/**
 * @brief Listens to the USB Serial for any #ServoCommand inputs. Assumes
 *        that any inputs on the serial are valid #ServoCommand's
 *
 * @authors Peter Gunarso, Sunny Hu
 *
 * @param pvParameters FreeRTOS parameter passing, vTaskSerial takes no params
 */
void vTaskSerial(void * pvParameters);

#endif  // SERIAL_H_