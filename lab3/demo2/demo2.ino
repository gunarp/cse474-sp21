/* University of Washington
 * ECE/CSE 474,  [5/12]
 *
 *   Sunny Hu
 *   Peter Gunarso
 *
 *   Lab 3, Round Robin Scheduler
 *
 */

#include "SRRI.h"

// uint32_t t1 = ADURATION;
// uint32_t t2 = t1 + (uint32_t) NFREQ * (PLAY_DURATION);
// uint32_t t3 = t2 + CDURATION;
// uint32_t t4 = t3 + 1000;

int reset1 = 0;
int reset2 = 0;

static void (* taskArr[NTASKS]) ();
static int sFlag = PENDING;
static int sleepArr[NTASKS];
static int stateArr[NTASKS];
static int currTask;

void setup() {
  // get all our outputs set up
  interruptSetup();
  // speakerSetup();
  ledSetup();
  LED_PORT |= BIT2;
  // populate task array
  for (int i = 0; i < NTASKS; i++) {
    taskArr[i] = NULL;
  }
  taskArr[0] = task1;
  taskArr[1] = task2;
  taskArr[NTASKS-1] = schedule_sync;
}

void loop() {
  // while (1) {}
  // for (int i = 0; i < NTASKS; i++) {
  //   if (taskArr[i] != NULL && taskState[i] == READY) {
  //     // start up this task
  //     taskState[i] = RUNNING;
  //     currTask = i;
  //     *(taskArr[i])();

  //     // tear down
  //     if (taskState[i] == RUNNING) taskState[i] = READY;
  //   }
  // }
}

ISR(TIMER3_COMPA_vect) {
  sFlag = DONE;
  // SPEAKER_PORT ^= BIT3;
  LED_PORT ^= BIT2;
}

void sleep_474(int t) {
  // sleep array @ [function index], set value to t
  sleepArr[currTask] = t;
  // state array @ [function index], set state to SLEEPING
  stateArr[currTask] = SLEEPING;
}

void schedule_sync() {
  while (sFlag == PENDING) {
  }

  // for (int i = 0; i < NTASKS; i++) {
  //   // update remaining sleep time
  //   if (stateArr[i] == SLEEPING) {
  //     sleepArr[i] -= 2;
  //   }
  //   // wake up any sleeping tasks
  //   if (sleepArr[i] < 2) {
  //     // reset to t = 0 in sleep array (not sure if needed)
  //     sleepArr[i] = 0;
  //     // change corresponding state from SLEEPING to READY
  //     stateArr[i] = READY;
  //   }
  // }

  // reset sFlag
  sFlag = PENDING;
  return;
}

// sets the OCR4A to make the clock cycle frequency
// the same as the input freq
void setOC4AFreq(uint32_t freq) {
  PRESCALER = freq == 0 ? 0 : 16000000 / (2 * freq);
  TIMER_COUNTER = 0;
}

void task1() {
  static unsigned long time;
  time++;

  // reset everything given a reset signal
  if (reset1) {
    LED_PORT |= BIT2;
    time = 0;
    reset1 = 0;
    return;
  }

  // flash led on pin 47 for FLASH_DURATION
  if (time == (0 * FLASH_DURATION) + 1) {
    LED_PORT &= ~BIT2;
  }

  if (time == (1 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
  }

  if (time == 1000) {
    time = 0;
  }

  return;
}

void task2() {
  static unsigned long time;
  time++;

  if (reset2) {
    setOC4AFreq(0);
    time = 0;
    reset2 = 0;
    return;
  }

  // play tone
  for (int i = 0; i < NFREQ; i++) {
    if (time == ((unsigned long) i * PLAY_DURATION) + 1) {
      setOC4AFreq(melody[i]);
    }
  }

  // stop playing for 4 seconds
  if (time == ((unsigned long) NFREQ * PLAY_DURATION) + 1) {
    setOC4AFreq(0);
  }

  // start playing after 4 seconds
  for (int i = 0; i < NFREQ; i++) {
    if (time == (PICKUP_TIME + (unsigned long) i * PLAY_DURATION) + 1) {
      setOC4AFreq(melody[i]);
    }
  }

  // reset
  if (time == (PICKUP_TIME + (unsigned long) NFREQ * PLAY_DURATION) + 1) {
    time = 0;
  }
}

void interruptSetup() {
  // reset settings
  TCCR3A = 0;
  TCCR3B = 0;

  // set timer to work in CTC mode
  TCCR3A |= (0 << WGM31) | (0 << WGM30);
  TCCR3B |= (0 << WGM33) | (1 << WGM32);
  TCCR3A |= (0 << COM3A1) | (1 << COM3A0);

  // enable interrupt on counter A
  TIMSK3 |= OCIE3A;

  // set frequency of timer
  // TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
  TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30); // 1024
  OCR3A =  7812; // should make around 1 hz
  // OCR3A = 16000;
  TCNT3H = 0;

  // enable interrupts
  SREG |= (1<<7);
}

void speakerSetup() {
  // clear timer settings
  TIMER_REG_A = 0;
  TIMER_REG_B = 0;
  // set our timer to work in CTC mode
  TIMER_REG_A |= (0 << WGM41) | (0 << WGM40);
  TIMER_REG_B |= (0 << WGM43) | (1 << WGM42);

  // set timer to work in toggle mode
  TIMER_REG_A |= (0 << COM4A1) | (1 << COM4A0);

  // disable interrupts on the timer
  TIMSK4 = 0;

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

void ledSetup() {
  // set output pins for task1
  LED_DDR |= BIT2;
}