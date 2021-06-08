#include "servos.hh"

static Servo servH;
static Servo servV;

QueueHandle_t ServoCommandQueue;

void vServoSetup() {
    // Serial.println("Servo setup starting");
    // set servo output pins
    servH.attach(HSERVPIN);
    servV.attach(VSERVPIN);

    // set servos in neutral position
    servH.write(90);
    servV.write(90);

    // set up the servo command queue
    ServoCommandQueue = xQueueCreate(1, sizeof(ServoCommand));
    // Serial.println("Servo setup ending");
}

void vTaskServo(void * pvParameters) {
    ServoCommand command;
    int valueV = servV.read();
    int valueH = servH.read();
    for (;;) {
        // wait for a command forever
        xQueueReceive(ServoCommandQueue, &command, portMAX_DELAY);
        valueV = servV.read();
        valueH = servH.read();
        // move the servos based on incoming command, note that
        // a higher degree turns the servo
        switch (command)
        {
        case IN:
            valueV -= STEP;
            break;

        case OUT:
            valueV += STEP;
            break;

        case LEFT:
            valueH += STEP;
            break;

        case RIGHT:
            valueH -= STEP;
            break;

        default:
            break;
        }
        servV.write(valueV);
        servH.write(valueH);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

