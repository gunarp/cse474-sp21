/**
 * @file fan.cpp
 * @authors Peter Gunarso, Sunny Hu
 * @brief Fan Controlling Tasks
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "fan.hh"

/**
 * @brief Actual Instantiation of the FanCommandQueue, which holds #FanCommand
 *
 */
QueueHandle_t FanCommandQueue;

/**
 * @brief Actual instantiation of FanPWMQueue, delivers pwms to vTaskFanAnalog.
 *
 */
QueueHandle_t FanPWMQueue;

void vTaskFanDigitial(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));
    // set up fan queue
    FanCommandQueue = xQueueCreate(1, sizeof(FanCommand));

    // set up fan
    pinMode(FANPIN, OUTPUT);
    analogWrite(FANPIN, 0);

    FanCommand cmd;
    int fanVal = MINFANPWM;
    for (;;) {
        cmd = STAY;
        // poll queue
        xQueueReceive(FanCommandQueue, &cmd, portMAX_DELAY);
        switch (cmd)
        {
        case FAN_RESET:
            fanVal = MINFANPWM;
            break;

        case FASTER:
            fanVal = min(fanVal + FANSTEP, MAXFANPWM);
            break;

        case SLOWER:
            fanVal = max(fanVal - FANSTEP, MINFANPWM);
            break;

        default:
            break;
        }

        analogWrite(FANPIN, fanVal);
    }
}

void vTaskFanAnalog(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));
    FanPWMQueue = xQueueCreate(1, sizeof(int));

    int pwm;
    for (;;) {
        xQueueReceive(FanPWMQueue, &pwm, portMAX_DELAY);
        analogWrite(FANPIN, pwm);
    }
}