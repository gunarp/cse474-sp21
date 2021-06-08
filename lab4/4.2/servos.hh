#include <Servo.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#ifndef SERVO_H_
#define SERVO_H_

// pins to operate servos with
#define HSERVPIN 7
#define VSERVPIN 6
// degrees to move per command
#define STEP 5

enum ServoCommand {IN, OUT, LEFT, RIGHT};

// set up servo pins and control queue
void vServoSetup();

// task which will constantly poll a queue for servo movement updates
void vTaskServo(void *);

#endif  // SERVO_H_

