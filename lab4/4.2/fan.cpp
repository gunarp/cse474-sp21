#include "fan.hh"

QueueHandle_t FanCommandQueue;
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

        Serial.print("fanVal: ");
        Serial.println(fanVal);
        analogWrite(FANPIN, fanVal);
    }
}

void vTaskFanAnalog(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));
    FanPWMQueue = xQueueCreate(1, sizeof(int));

    int pwm;
    for (;;) {
        xQueueReceive(FanPWMQueue, &pwm, portMAX_DELAY);
        Serial.print("sent pwm: ");
        Serial.println(pwm);
        analogWrite(FANPIN, pwm);
    }
}