#ifndef FAN_H_
#define FAN_H_

#include "4.2.h"

#define FANPIN 12
#define MINFANPWM 30
#define MAXFANPWM 255
#define FANSTEP 15

enum FanCommand {FAN_RESET, STAY, FASTER, SLOWER};

void vTaskFanDigitial(void *);
void vTaskFanAnalog(void *);

#endif  // FAN_H_