#include "servos.hh"

QueueHandle_t ServoCommandQueue;

void vServoSetup() {
    // Serial.println("Servo setup starting");
    // set servo output pins
    pinMode(HSERVPIN, OUTPUT);
    pinMode(VSERVPIN, OUTPUT);

    // set servos in neutral position
    analogWrite(HSERVPIN, CENTERPWM);
    analogWrite(VSERVPIN, CENTERPWM);

    // set up the servo command queue
    ServoCommandQueue = xQueueCreate(1, sizeof(ServoCommand));
    // Serial.println("Servo setup ending");
}

void vTaskServo(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(50));
    // Serial.println("starting task servo");
    ServoCommand command;
    int valueV = CENTERPWM;
    int valueH = CENTERPWM;
    for (;;) {
        // wait for a command forever
        xQueueReceive(ServoCommandQueue, &command, portMAX_DELAY);
        // move the servos based on incoming command, note that
        // a higher degree turns the servo
        switch (command)
        {
        case IN:
            valueV = max(valueV - STEP, MINPWM);
            break;

        case OUT:
            valueV = min(valueV + STEP, MAXPWM);
            break;

        case LEFT:
            valueH = max(valueH - STEP, MINPWM);
            break;

        case RIGHT:
            valueH = min(valueH + STEP, MAXPWM);
            break;

        case SERV_RESET:
            valueV = CENTERPWM;
            valueH = CENTERPWM;
            break;

        default:
            break;
        }
        analogWrite(VSERVPIN, valueV);
        analogWrite(HSERVPIN, valueH);
    }
}

