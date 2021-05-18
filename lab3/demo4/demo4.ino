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

void (* taskArr[NTASKS]) ();
volatile int sFlag = PENDING;
volatile int currTask;
volatile int sleepArr[NTASKS];
volatile int stateArr[NTASKS];
volatile long timeArr[NTASKS];

void setup() {
  // get all our outputs set up
  interruptSetup();
  speakerSetup();
  ledSetup();
  // LED_PORT |= BIT2;
  // populate task array
  for (int i = 0; i < NTASKS; i++) {
    taskArr[i] = NULL;
    timeArr[i] = 0;
    stateArr[i] = READY;
    sleepArr[i] = 0;
  }
  taskArr[0] = task1;
  taskArr[1] = task2;
  taskArr[2] = task3;
  taskArr[NTASKS-2] = schedule_sync;
  Serial.begin(9600);

  // set up digit selectors
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  // set up 7-seg outputs
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);

  digitalWrite(13, 1);
  digitalWrite(12, 1);
  digitalWrite(11, 1);
  digitalWrite(10, 1);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  for (int i = 0; i < NTASKS; i++) {
    if (taskArr[i] != NULL && stateArr[i] == READY) {
      // start up this task
      stateArr[i] = RUNNING;
      currTask = i;
      (*taskArr[i])();


      // tear down
      if (stateArr[i] == RUNNING) stateArr[i] = READY;
    }
  }
}

ISR(TIMER3_COMPA_vect) {
  sFlag = DONE;
}

void sleep_474(long t) {
  // sleep array @ [function index], set value to t
  sleepArr[currTask] = t;
  // state array @ [function index], set state to SLEEPING
  stateArr[currTask] = SLEEPING;
  return;
}

void schedule_sync() {
  while (sFlag == PENDING) {
    3 + 5;
  }
  for (int i = 0; i < NTASKS; i++) {
    // update remaining sleep time
    if (stateArr[i] == SLEEPING) {
      sleepArr[i] -= 2;
      // wake up any sleeping tasks
      if (sleepArr[i] < 2) {
        // reset to t = 0 in sleep array (not sure if needed)
        sleepArr[i] = 0;
        // change corresponding state from SLEEPING to READY
        stateArr[i] = READY;
      }
    }

    timeArr[i] += 2;
  }

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
  // reset everything given a reset signal
  if (reset1) {
    LED_PORT |= BIT2;
    timeArr[currTask] = 0;
    reset1 = 0;
    return;
  }

  // flash led on pin 47 for FLASH_DURATION
  if (timeArr[currTask] < (1 * FLASH_DURATION) + 1) {
    LED_PORT &= ~BIT2;
    sleep_474(250);
    return;
  }

  if (timeArr[currTask] < (2 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
    sleep_474(750);
    return;
  }

  if (timeArr[currTask] >= 1000) {
    timeArr[currTask]= 0;
  }

  return;
}

void task2() {
  if (reset2) {
    setOC4AFreq(0);
    timeArr[currTask] = 0;
    reset2 = 0;
    return;
  }

  // play tone
  for (int i = 0; i < NFREQ; i++) {
    if ( timeArr[currTask] >= ((unsigned long) i * PLAY_DURATION) &&
      timeArr[currTask] < (((unsigned long) i + 1) * PLAY_DURATION) ) {
      setOC4AFreq(melody[i]);
      sleep_474(PLAY_DURATION);
      return;
    }
  }

  // stop playing for 4 seconds
  if (timeArr[currTask] < PICKUP_TIME) {
    setOC4AFreq(0);
    sleep_474(PAUSE_DURATION);
    return;
  }

  // start playing after 4 seconds
  for (int i = 0; i < NFREQ; i++) {
    if (timeArr[currTask] >= (PICKUP_TIME + ((unsigned long) i) * PLAY_DURATION) &&
        timeArr[currTask] < (PICKUP_TIME + ((unsigned long) i + 1) * PLAY_DURATION)) {
      setOC4AFreq(melody[i]);
      sleep_474(PLAY_DURATION);
      return;
    }
  }

  // reset
  if (timeArr[currTask] >= (PICKUP_TIME + (unsigned long) NFREQ * PLAY_DURATION)) {
    timeArr[currTask] = 0;
  }
}

void convert(int * digits, int val) {
  // array for all the vals?
	digits[0] = val % 10;
	digits[1] = (val/10) % 10;
	digits[2] = (val/100) % 10;
	digits[3] = (val/1000) % 10;
}

void task3() {
  static int count;
  static int digits[4];

  // take digits out of count
  convert(digits, count);

  // display count on the 7seg display
  for (int i = 0; i < 4; i++) {
    int pin = 10 + i;
    // i think i need to fix this if statement to make it work
    if (timeArr[currTask] % 5 == 0 && timeArr[currTask] < 5*i) {
      // turn 7seg & specified digit on
      digitalWrite(pin, 0);
      byte *disp = seven_seg_digits[digits[i]];
      send7(disp);
      sleep_474(2);
      return;
    } else { // turn off digit
      // should this be a separate if statement?
      byte disp[7] = {0, 0, 0, 0, 0, 0, 0};
      send7(disp);
      digitalWrite(pin, 1);
      sleep_474(3);
      return;
    }
  }

  // reset
  if (timeArr[currTask] >= 100) {
    digitalWrite(LED_BUILTIN, HIGH); // this doesn't seem to turn on/happen
    timeArr[currTask] = 0;
    count = count == 9999 ? 0 : count + 1;
  }
}

void send7(byte arr[7]) {
  digitalWrite(22, arr[0]);
  digitalWrite(23, arr[1]);
  digitalWrite(24, arr[2]);
  digitalWrite(25, arr[3]);
  digitalWrite(26, arr[4]);
  digitalWrite(27, arr[5]);
  digitalWrite(28, arr[6]);
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
  TIMSK3 |= (1 << OCIE3A);

  // set frequency of timer
  TCCR3B |= (0 << CS32) | (0 << CS31) | (1 << CS30);
  // TCCR3B |= (1 << CS32) | (0 << CS31) | (1 << CS30); // 1024
  // OCR3A =  7812; // should make around 1 hz
  OCR3A = 32000;
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
