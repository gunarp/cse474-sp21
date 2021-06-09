/**
 * @file fan.hh
 * @authors Peter Gunarso, Sunny Hu
 * @brief fan.cpp header file
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef FAN_H_
#define FAN_H_

#include "4.2.h"

#define FANPIN 12
#define MINFANPWM 0
#define MAXFANPWM 255
#define FANSTEP 15

/**
 * @brief Possible fan commands, FASTER and SLOWER will increment or decrement the fan's
 *        PWM by FANSTEP. FAN_RESET will set the PWM to MINFANPWM.
 *
 */
enum FanCommand {FAN_RESET, STAY, FASTER, SLOWER};

/**
 * @brief Task which waits on #FanCommands from FanCommandQueue, adjusts fan speed accordingly.
 *
 * @authors Peter Gunarso, Sunny Hu
 * @param pvParameters This function takes no parameters
 */
void vTaskFanDigitial(void * pvParameters);

/**
 * @brief Task which waits on incoming PWMs from FanPWMQueue, sets the PWM of the fan accordingly.
 *
 * @authors Peter Gunarso, Sunny Hu
 * @param pvParameters This function takes no parameters
 */
void vTaskFanAnalog(void * pvParameters);

#endif  // FAN_H_