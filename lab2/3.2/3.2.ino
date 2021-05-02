/* University of Washington
 * ECE/CSE 474,  [4/29]
 *
 *   Sunny Hu
 *   Peter Gunarso
 *
 *   Lab 2, Task 3.2
 *
 */

#include "3.2.h"

uint32_t t1 = ADURATION;
uint32_t t2 = t1 + (uint32_t) NFREQ * (PLAY_DURATION);
uint32_t t3 = t2 + CDURATION;
uint32_t t4 = t3 + 1000;

int resetA = 0;
int resetB = 0;

// sets the OCR4A to make the clock cycle frequency
// the same as the input freq
void setOC4AFreq(uint32_t freq) {
  PRESCALER = freq == 0 ? 0 : 16000000 / (2 * freq);
  TIMER_COUNTER = 0;
}

void taskA() {
  static unsigned long time;
  time++;

  // reset everything given a reset signal
  if (resetA) {
    LED_PORT |= BIT2;
    LED_PORT |= BIT1;
    LED_PORT |= BIT0;
    time = 0;
    resetA = 0;
    return;
  }

  // flash led on pin 47 for FLASH_DURATIOn
  if (time == (0 * FLASH_DURATION) + 1) {
    LED_PORT &= ~BIT2;
    LED_PORT |= BIT1;
    LED_PORT |= BIT0;
  }

  // flash led on pin 48 for FLASH_DURATION
  if (time == (1 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
    LED_PORT &= ~BIT1;
    LED_PORT |= BIT0;
  }

  // flash led on pin 49 for FLASH_DURATION
  if (time == (2 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
    LED_PORT |= BIT1;
    LED_PORT &= ~BIT0;
  }

  if (time == (3 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
    LED_PORT |= BIT1;
    LED_PORT |= BIT0;
    time = 0;
  }

  return;
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

void taskC() {
  static unsigned long time;
  time++;

  if (time <= t1) {
    taskA();
    return;
  }

  if (time <= t2) {
    taskB();
    return;
  }

  if (time <= t3) {
    taskA();
    taskB();
    return;
  }

  if (time <= t4) {
    resetA = 1;
    resetB = 1;
    taskA();
    taskB();
  }

  if (time > t4) {
    resetB = 1;
    taskB();
    time = 0;
    return;
  }

}

void setup() {
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

  // set output pins for taskA
  LED_DDR |= BIT0;
  LED_DDR |= BIT1;
  LED_DDR |= BIT2;
}

void loop() {
  taskC();
  delay(1);
}
