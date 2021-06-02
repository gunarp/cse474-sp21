#include "controls.hh"

Keypad customKeypad;

void keypadSetup() {
    // change to match output pins
    byte rowPins[ROWS] = {25, 27, 29, 31};
    byte colPins[COLS] = {33, 35, 37, 39};

    customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

}

void taskKeypad(void * pvParameters) {
    // setup
    keypadSetup();

    // poll forever
    for(;;) {
        switch(customKeypad.getKey()) {
            case '2':
                // forward
                break;

            case '6':
                // backward
                break;

            case '4':
                // left
                break;

            case '8':
                // right
                break;

            case '*':
                // slower
                break;

            case '#':
                // faster
                break;

            case 'A':
                // voice mode
                break;

            case 'B':
                // keypad mode
                break;

            default :
                // don't handle other buttons
                break;
        }
    }
}