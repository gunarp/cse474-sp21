#include "4.2.h"
#include "servos.hh"
#include "serial.hh"

void vTaskSerial(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));

    int x;
    ServoCommand cmd;
    for(;;) {
        if (Serial.available()) {
            cmd = (ServoCommand) Serial.readString().toInt();
            xQueueSendToBack(ServoCommandQueue, &cmd, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}