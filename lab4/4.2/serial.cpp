/**
 * @file serial.cpp
 * @author your name (you@domain.com)
 * @brief Serial Watchdog code
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "4.2.h"
#include "servos.hh"
#include "serial.hh"

void vTaskSerial(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));

    int x;
    ServoCommand cmd;
    for(;;) {
        if (mode) xTaskNotifyWait(0x00, 0xffffffff, NULL, portMAX_DELAY);
        if (Serial.available()) {
            cmd = (ServoCommand) Serial.readString().toInt();
            if (!mode) xQueueSendToBack(ServoCommandQueue, &cmd, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(SERIALDELAY));
    }
}
