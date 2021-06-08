#include "4.2.h"

void TaskBlink(void *);

void setup() {
    // set up i/o devices
    Serial.begin(19200);
    while (!Serial) {}
    vServoSetup();

    delay(500);

    // create tasks
    xTaskCreate(TaskBlink,  "Blink",  128,  NULL,  0,  NULL );
    xTaskCreate(vTaskServo, "Servo Manager", 128, NULL, 2, NULL);
    // delay(500);
    xTaskCreate(vTaskKeypad, "Keypad Manager", 270, NULL, 1, NULL);
    // xTaskCreate(TaskRGB, "RGB LED", 128, NULL, 1, NULL);
    xTaskCreate(vTaskFanDigitial, "Digital Fan Manager", 128, NULL, 2, NULL);
    xTaskCreate(vTaskFanAnalog, "Analog Fan Manager", 128, NULL, 2, NULL);

    delay(500);

    vTaskStartScheduler();
}

void loop() {
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  // initialize led pin as an output.
  pinMode(47, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(47, LOW); // turn on
    vTaskDelay( pdMS_TO_TICKS(100) ); // wait for one second
    digitalWrite(47, HIGH); // turn off
    vTaskDelay( pdMS_TO_TICKS(200) ); // wait for one second
  }
}
