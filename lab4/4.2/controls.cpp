#include "4.2.h"
#include "controls.hh"
#include "fan.hh"

const byte ROWS = 4;
const byte COLS = 4;

const byte rowPins[ROWS] = {25, 27, 29, 31};
const byte colPins[COLS] = {33, 35, 37, 39};

int red_light_pin= 3;
int green_light_pin = 2;
int blue_light_pin = 23;

// 0 = voice
// 1 = control
static int mode;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void vTaskKeypad(void * pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(100));
    // setup
    ServoCommand servCmd;
    FanCommand fanCmd;

    Keypad customKeypad = Keypad(makeKeymap(hexaKeys), (byte *) rowPins, (byte *) colPins, ROWS, COLS);

    // poll forever
    for(;;) {
        servCmd = NONE;
        char key = customKeypad.getKey();
        switch(key) {
            case '5':
                // reset position
                if (mode) {
                    servCmd = SERV_RESET;
                    xQueueSendToBack(ServoCommandQueue, &servCmd, 0);
                    fanCmd = FAN_RESET;
                    xQueueSendToBack(FanCommandQueue, &fanCmd, 0);
                }
                break;

            case '2':
                // in
                if (mode) {
                    servCmd = IN;
                    xQueueSendToBack(ServoCommandQueue, &servCmd, 0);
                }
                break;

            case '8':
                // out
                if (mode) {
                    servCmd = OUT;
                    xQueueSendToBack(ServoCommandQueue, &servCmd, 0);
                }
                break;

            case '4':
                // left
                if (mode) {
                    servCmd = LEFT;
                    xQueueSendToBack(ServoCommandQueue, &servCmd, 0);
                }
                break;

            case '6':
                // right
                if (mode) {
                    servCmd = RIGHT;
                    xQueueSendToBack(ServoCommandQueue, &servCmd, 0);
                }
                break;

            case '*':
                // slower
                if (mode) {
                    fanCmd = SLOWER;
                    xQueueSendToBack(FanCommandQueue, &fanCmd, 0);
                }
                break;

            case '#':
                // faster
                if (mode) {
                    fanCmd = FASTER;
                    xQueueSendToBack(FanCommandQueue, &fanCmd, 0);
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
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    vTaskDelete(NULL);
}

void vNoiseSensorControl(void * pvParameters) {
    int max = -1;
    for (;;) {
        if (mode) vTaskDelay(pdMS_TO_TICKS(200));
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
            // send read value to fan pwm
            double sendVal = (readVal - 5)/600.0 > 1 ? 1 : (readVal - 5)/600.0;
            xQueueSend(FanPWMQueue, &sendVal, 0);
        }
    }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void TaskRGB(void *pvParameters) {
  vTaskDelay(pdMS_TO_TICKS(100));
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  for(;;) {
    if(mode == 0) {
      RGB_color(255, 0, 0); // Red
    }
    if(mode == 1) {
      RGB_color(0, 255, 0); // Green
    }
    vTaskDelay( pdMS_TO_TICKS(20) );
  }
}
