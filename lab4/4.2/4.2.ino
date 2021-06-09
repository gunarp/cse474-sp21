/**
 * @file 4.2.ino
 * @authors Peter Gunarso, Sunny Hu
 * @brief Lab 4 Part 2 Task code
 * @version 0.1
 * @date 2021-06-08
 *
 * @copyright Copyright (c) 2021
 *
 */
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
    xTaskCreate(TaskRGB, "RGB LED", 128, NULL, 1, NULL);

    xTaskCreate(vTaskFanDigitial, "Digital Fan Manager", 128, NULL, 2, NULL);
    xTaskCreate(vTaskFanAnalog, "Analog Fan Manager", 128, NULL, 2, NULL);

    TaskHandle_t NoiseControl;
    xTaskCreate(vNoiseSensorControl, "Noise Sensor Controller", 128, NULL, 2, &NoiseControl);
    TaskHandle_t SerialWatchdog;
    xTaskCreate(vTaskSerial, "Serial Watchdog", 128, NULL, 0, &SerialWatchdog);
    void * params[2] = {NoiseControl, SerialWatchdog};
    xTaskCreate(vTaskKeypad, "Keypad and State Manager", 270, params, 3, NULL);


    delay(500);

    vTaskStartScheduler();
}

void loop() {
}

/**
 * @brief Task 1 from part 1
 *
 * @param pvParameters This task doesn't take any parameters
 */
void TaskBlink(void *pvParameters) {
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
