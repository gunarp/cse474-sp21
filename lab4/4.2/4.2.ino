#include "4.2.h"

#include "fan.hh"
#include "keypad.hh"
#include "serial.hh"
#include "servos.hh"

int alpha = 0;

void setup()
{
    Serial.begin(19200);
}

void loop()
{
    modifyInt(&alpha, 0);
    Serial.write(alpha);
    Serial.write('\n');
    delay(500);
    modifyInt(&alpha, 39);
    Serial.write(alpha);
    Serial.write('\n');
    delay(500);
    modifyInt(&alpha, 69);
    Serial.write(alpha);
    Serial.write('\n');
}