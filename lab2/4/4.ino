/* University of Washington
 * ECE/CSE 474,  [4/29]
 *
 *   Sunny Hu
 *   Peter Gunarso
 *
 *   Lab 2, Task 4
 *
 */

#include "4.h"

int resetM = 0;
int resetB = 0;

byte spidata[16]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void OC4ASetup() {
  // clear timer settings
  TIMER_REG_A = 0;
  TIMER_REG_B = 0;
  // set our timer to work in CTC mode
  TIMER_REG_A |= (0 << WGM41) | (0 << WGM40);
  TIMER_REG_B |= (0 << WGM43) | (1 << WGM42);

  // set timer to work in toggle mode
  TIMER_REG_A |= (0 << COM4A1) | (1 << COM4A0);

  // disable interrupts on the timer
  TIMER_MASK = 0;

  // set the prescaler of the timer,
  // which follows the formula:
  //
  //  f_out = f_i/o / 2 * N * (PRESCALER + 1)
  //
  // because f_i/o = 16Mhz, we'll just set N = 1
  TIMER_REG_B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
  PRESCALER = 0;
  TIMER_COUNTER = 0;

  // OC4A is tied to pin 6, which is controlled by PH3
  // set pin 6 as an output pin
  SPEAKER_DDR |= BIT3;
}

void LEDMatrixSetup() {
  // set pinmodes
  DIN_DDR |= DIN_BIT;
  CS_DDR |= CS_BIT;
  CLK_DDR |= CLK_BIT;
  CS_PORT |= CS_BIT;

  XYINPUT_DDR &= ~XIN_BIT;
  XYINPUT_DDR &= ~YIN_BIT;

  spiTransfer(OP_DISPLAYTEST,0);
  spiTransfer(OP_SCANLIMIT,7);
  spiTransfer(OP_DECODEMODE,0);
  spiTransfer(OP_SHUTDOWN,1);

  // turn matrix display off
  for (int i = 0; i < 8; i++) {
    spiTransfer(i, (byte)0);
    //spiTransfer(i, 0b11000000);
  }
}

void setup(){
  OC4ASetup();
  LEDMatrixSetup();
}

void loop() {
  taskB();
  taskMATRIX();
  delay(1);
}

// from LED_Matrix.ino
//
// this function turns on a collection of LEDs on, with
// opcode selecting the row, and data being the values
// for the entire row.
void spiTransfer(volatile byte opcode, volatile byte data){
  int offset = 0; //only 1 device
  int maxbytes = 16;

  for(int i = 0; i < maxbytes; i++) { //zero out spi data
    spidata[i] = (byte)0;
  }
  //load in spi data
  spidata[offset+1] = opcode+1;
  spidata[offset] = data;
  digitalWrite(CS, LOW); //
  for(int i=maxbytes;i>0;i--)
    shiftOut(DIN,CLK,MSBFIRST,spidata[i-1]);
  digitalWrite(CS,HIGH);
}

void taskMATRIX() {
  static unsigned long time;
  static int posX, posY;
  time++;

  if (resetM) {
    // calculate bit shift for display
    int dispX = -posX + MAX;

    // turn the LED at (x, y) on
    spiTransfer(posY, (byte)(1 << dispX));
    return;
  }

  if (time == 50) {
    // turn LED at (x, y) off (technically, this clears the whole row.)
    spiTransfer(posY, (byte)0);

    posX = analogRead(A5) >> 7;
    posY = analogRead(A3) >> 7;

    // calculate bit shift for display
    int dispX = -posX + MAX;

    // turn the LED at (x, y) on
    spiTransfer(posY, (byte)(1 << dispX));

    time = 0;
  }
  return;
}

void setOC4AFreq(uint32_t freq) {
  PRESCALER = freq == 0 ? 0 : 16000000 / (2 * freq);
  TIMER_COUNTER = 0;
}

void taskB() {
  static unsigned long time;
  time++;

  if (resetB) {
    setOC4AFreq(0);
    time = 0;
    resetB = 0;
    return;
  }

  for (int i = 0; i < NFREQ; i++) {
    if (time == ((unsigned long) i * PLAY_DURATION) + 1) {
      setOC4AFreq(melody[i]);
    }
  }

  if (time == ((unsigned long) NFREQ * PLAY_DURATION) + 1) {
    time = 0;
  }
}