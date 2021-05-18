/* University of Washington
 * ECE/CSE 474,  [5/12]
 *
 *   Sunny Hu
 *   Peter Gunarso
 *
 *   Lab 3, Data-Driven Scheduler
 *
 */

#include "DDS.h"

int reset1 = 0;
int reset2 = 0;

tcb taskArr[NTASKS];
tcb deadTasks[NTASKS];
volatile int id;
volatile int currTask;
volatile FLAG sFlag;

void setup() {
  // get all our outputs set up
  interruptSetup();
  speakerSetup();
  ledSetup();
  id = 0;
  // LED_PORT |= BIT2;
  // populate task array
  for (int i = 0; i < NTASKS; i++) {
    taskArr[i].fn_ptr = NULL;
    taskArr[i].id = 0;
    taskArr[i].nTimes = 0;
    taskArr[i].timeSleep = 0;
    taskArr[i].time = 0;
    taskArr[i].state = DEAD;
  }
  task_load(task1, "task 1");
  task_load(task2, "task 2");
  task_load(schedule_sync, "schedule_sync");
}

void loop() {
  for (int i = 0; i < NTASKS; i++) {
    if (taskArr[i].fn_ptr != NULL && taskArr[i].state == READY) {
      // start up this task
      taskArr[i].state = RUNNING;
      currTask = i;
      (*(taskArr[i].fn_ptr))();

      // tear down
      if (taskArr[i].state == RUNNING) taskArr[i].state = READY;
    }
  }
}

ISR(TIMER3_COMPA_vect) {
  sFlag = DONE;
}

void task_self_quit() {
  // find a spot in the dead array
  int i;
  for (i = 0; i < NTASKS; i++) {
    if (deadTasks[i].fn_ptr != NULL) break;
  }

  if (i == NTASKS) return;
  deadTasks[i].fn_ptr = taskArr[currTask].fn_ptr;
  strcpy(deadTasks[i].name, taskArr[i].name);
  deadTasks[i].state = DEAD;
}

void task_start(tcb * task) {
  if (task->state != DEAD) return;
  task_load(task->fn_ptr, task->name);
}

void task_load(void (*fn_ptr)(), const char * name) {
  // find the next open slot in the task array
  int i;
  for (i = 0; i < NTASKS; i++) {
    if (taskArr[i].fn_ptr == NULL) break;
  }

  // if there's no space, don't do anything
  if (i == NTASKS) return;

  // load up a new task
  strcpy(taskArr[i].name, name);
  taskArr[i].fn_ptr = fn_ptr;
  taskArr[i].id = id;
  id++;
  taskArr[i].nTimes = 0;
  taskArr[i].timeSleep = 0;
  taskArr[i].time = 0;
  taskArr[i].state = READY;
}

void sleep_474(long t) {
  // sleep array @ [function index], set value to t
  taskArr[currTask].timeSleep = t;
  // state array @ [function index], set state to SLEEPING
  taskArr[currTask].state = SLEEPING;
  return;
}

void schedule_sync() {
  while (sFlag == PENDING) {
    3 + 5;
  }
  for (int i = 0; i < NTASKS; i++) {
    // update remaining sleep time
    if (taskArr[i].state == SLEEPING) {
      taskArr[i].timeSleep -= 2;
      // wake up any sleeping tasks
      if (taskArr[i].timeSleep < 2) {
        // reset to t = 0 in sleep array (not sure if needed)
        taskArr[i].timeSleep = 0;
        // change corresponding state from SLEEPING to READY
        taskArr[i].state = READY;
      }
    }

    taskArr[i].time += 2;
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
    taskArr[currTask].time = 0;
    reset1 = 0;
    return;
  }

  // flash led on pin 47 for FLASH_DURATION
  if (taskArr[currTask].time < (1 * FLASH_DURATION) + 1) {
    LED_PORT &= ~BIT2;
    sleep_474(250);
    return;
  }

  if (taskArr[currTask].time < (2 * FLASH_DURATION) + 1) {
    LED_PORT |= BIT2;
    sleep_474(750);
    return;
  }

  if (taskArr[currTask].time >= 1000) {
    taskArr[currTask].time = 0;
  }

  return;
}

void task2() {
  if (reset2) {
    setOC4AFreq(0);
    taskArr[currTask].time = 0;
    reset2 = 0;
    return;
  }

  // play tone
  for (int i = 0; i < NFREQ; i++) {
    if ( taskArr[currTask].time >= ((unsigned long) i * PLAY_DURATION) &&
      taskArr[currTask].time < (((unsigned long) i + 1) * PLAY_DURATION) ) {
      setOC4AFreq(melody[i]);
      sleep_474(PLAY_DURATION);
      return;
    }
  }

  // stop playing for 4 seconds
  if (taskArr[currTask].time < PICKUP_TIME) {
    setOC4AFreq(0);
    sleep_474(PAUSE_DURATION);
    return;
  }

  // start playing after 4 seconds
  for (int i = 0; i < NFREQ; i++) {
    if (taskArr[currTask].time >= (PICKUP_TIME + ((unsigned long) i) * PLAY_DURATION) &&
        taskArr[currTask].time < (PICKUP_TIME + ((unsigned long) i + 1) * PLAY_DURATION)) {
      setOC4AFreq(melody[i]);
      sleep_474(PLAY_DURATION);
      return;
    }
  }

  // reset
  if (taskArr[currTask].time >= (PICKUP_TIME + (unsigned long) NFREQ * PLAY_DURATION)) {
    taskArr[currTask].time = 0;
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