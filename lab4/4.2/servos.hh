#ifndef SERVO_H_
#define SERVO_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// pins to operate servos with
#define HSERVPIN 7
#define VSERVPIN 6
// degrees to move per command
#define STEP 5

#define MINPWM 1330
#define MAXPWM 1530
#define CENTERPWM 1430

enum ServoCommand {NONE, SERV_RESET, IN, OUT, LEFT, RIGHT};

// set up servo pins and control queue
void vServoSetup();

// task which will constantly poll a queue for servo movement updates
void vTaskServo(void *);

#endif  // SERVO_H_
