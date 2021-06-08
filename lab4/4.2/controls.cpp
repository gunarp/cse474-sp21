#include "4.2.h"
#include "controls.hh"

static Keypad * customKeypad;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// 0 = voice
// 1 = control
int mode = 1;

void vKeypadSetup() {
    // change to match output pins
    // Serial.write("keypad setup starting");

    byte rowPins[ROWS] = {25, 27, 29, 31};
    byte colPins[COLS] = {33, 35, 37, 39};

    customKeypad = (Keypad *) malloc(sizeof(Keypad));
    *customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

    // Serial.write("keypad setup done");
}

void vTaskKeypad(void * pvParameters) {
    // setup
    vKeypadSetup();
    ServoCommand cmd;
    // poll forever
    Serial.println("hi");
    for(;;) {
        switch(customKeypad->getKey()) {
            case '2':
                // in
                if (mode) {
                    Serial.println("up");
                    cmd = IN;
                    xQueueSendToBack(ServoCommandQueue, &cmd, 0);
                }
                break;

            case '8':
                // out
                if (mode) {
                    Serial.println("out");
                    cmd = OUT;
                    xQueueSendToBack(ServoCommandQueue, &cmd, 0);
                }
                break;

            case '4':
                // left
                if (mode) {
                    cmd = LEFT;
                    xQueueSendToBack(ServoCommandQueue, &cmd, 0);
                }
                break;

            case '6':
                // right
                if (mode) {
                    cmd = RIGHT;
                    xQueueSendToBack(ServoCommandQueue, &cmd, 0);
                }
                break;

            case '*':
                // slower
                if (mode) {

                }
                break;

            case '#':
                // faster
                if (mode) {

                }
                break;

            case 'A':
                // voice mode
                mode = 0;
                break;

            case 'B':
                // keypad mode
                mode = 1;
                break;

            default :
                // don't handle other buttons
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void vNoiseSensorControl(void * pvParameters) {
    int max = -1;
    for (;;) {
        if (mode != 0) vTaskDelay(pdMS_TO_TICKS(200));
        else {
            uint readVal;
            for (int i = 0; i < 5; i++) {
                readVal = analogRead(A3); // change pin to whatever value

                // calculate absolute value wrt. potentiometer setting
                readVal = (readVal - 400) > 0 ? (readVal - 400) : (400 - readVal); // make variable for 400

                // set max val
                max = readVal > max ? readVal : max;
                vTaskDelay(pdMS_TO_TICKS(40)); // create variable
            }
            // send read value to servo pwm
            double sendVal = (readVal - 5)/600.0 > 1 ? 1 : (readVal - 5)/600.0;

        }
    }
}