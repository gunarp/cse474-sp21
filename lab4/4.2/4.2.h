#ifndef PROJ_H_
#define PROJ_H_

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "servos.hh"
#include "controls.hh"

extern QueueHandle_t ServoCommandQueue;

#endif  // PROJ_H_