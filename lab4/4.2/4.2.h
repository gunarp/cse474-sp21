#ifndef PROJ_H_
#define PROJ_H_

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "servos.hh"
#include "controls.hh"
#include "fan.hh"
#include "serial.hh"

extern QueueHandle_t ServoCommandQueue;
extern QueueHandle_t FanCommandQueue;
extern QueueHandle_t FanPWMQueue;

#endif  // PROJ_H_
