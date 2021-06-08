#include "4.2.h"

void setup() {
    // set up i/o devices
    Serial.begin(19200);
    // vServoSetup();

    // create tasks
    // xTaskCreate(vTaskServo, "Servo Manager", 128, NULL, 0, NULL);
    xTaskCreate(vTaskKeypad, "Keypad Manager", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}

void loop() {
}