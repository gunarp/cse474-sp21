#include <Servo.h>

Servo serv;

void setup()
{
    Serial.begin(19200);
    Serial.write(serv.attach(9) + '\n');

}

void loop()
{
    serv.write(1500);
    Serial.write(serv.read()+'\n');
    delay(15);
}