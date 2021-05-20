/**
 * @file DDS.h
 * @authors Sunny Hu, Peter Gunarso
 * @brief Header file for demo3.ino
 * @version 0.1
 * @date 2021-05-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define BIT0 1<<0
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3

#define TIMER_REG_A TCCR4A
#define TIMER_REG_B TCCR4B
#define TIMER_COUNTER TCNT4H
#define PRESCALER OCR4A
#define LED_DDR DDRL
#define LED_PORT PORTL
#define SPEAKER_DDR DDRH
#define SPEAKER_PORT PORTH

#define FLASH_DURATION 250
#define NFLASH 3
#define PLAY_DURATION 200
#define ADURATION 2000
#define CDURATION 10000
#define PAUSE_DURATION 4000
#define PICKUP_TIME (NFREQ * PLAY_DURATION) + PAUSE_DURATION

#define note_c3 130
#define note_c4 261
#define note_d4 293
#define note_e4 329
#define note_g3 196
#define note_R 0

#define NFREQ 13
int melody[] = { note_d4, note_R, note_e4, note_R, note_c4, note_R, note_c3,
                 note_R, note_g3, note_g3, note_g3, note_g3, note_R };

#define NTASKS 10

typedef enum {READY, RUNNING, SLEEPING, DEAD} STATE;
typedef enum flagState {PENDING, DONE} FLAG;

/**
 * @brief Struct to hold all of a Tasks running state
 * 
 */
typedef struct TCB {
  /// Task name
  char name[20];
  /// Task function
  void (*fn_ptr)();
  /// Task id
  int id;
  /// Number of times task has been run
  int nTimes;
  /// Amount of time in ms the task should sleep for
  int timeSleep;
  /// Current clock time this task sees
  int time;
  /// Running state of this task
  STATE state;
} tcb;

/**
 * @brief Puts currently running function to sleep for t ms
 * @authors Sunny Hu, Peter Gunarso
 * @param t Number of ms for task to sleep for
 */
void sleep_474(long t);

/**
 * @brief Manages sleep time and clocks each task sees. If a task cannot sleep for any longer, wakes up the task.
 * @authors Sunny Hu, Peter Gunarso
 */
void schedule_sync();

/**
 * @brief Copies contents of one TCB into another
 * @author Peter Gunarso
 * @param dst TCB to copy into, will overwrite current contents
 * @param src TCB to copy from
 */
void copy_tcb(tcb * dst, tcb * src);

/**
 * @brief Sets this task's state to DEAD and puts it into the dead task array
 * @author Peter Gunarso
 */
void task_self_quit();

/**
 * @brief Sets the given task's state to READY and puts it into the runnable task array
 * @author Peter Gunarso
 * @param task pointer to TCB to start, must be a valid TCB.
 */
void task_start(tcb * task);

/**
 * @brief Creates a TCB for a given task and puts it into the dead task array
 * @author Peter Gunarso
 * @param fn_ptr Pointer to task function to create TCB around
 * @param name Name to give the TCB
 */
void task_load(void (*fn_ptr)(), const char * name);

/**
 * @brief Finds a task in the dead task array which matches a given name
 * @author Peter Guanrso
 * @param name Name of the task to find in the dead task array
 * @return tcb* Pointer to matching task, is NULL if the task is not found
 */
tcb * find_dead_task(const char * name);

/**
 * @brief Sets the frequency of OC4A to match a given frequency freq
 * @authors Sunny Hu, Peter Gunarso
 * @param freq Desired frequency to set OC4A
 */
void setOC4AFreq(uint32_t freq);

/**
 * @brief Manages task 1 behavior, falshes an LED on and off
 * @authors Sunny Hu, Peter Guanrso
 */
void task1();

/**
 * @brief Manages task 2 behavior, plays the theme from "Close Encounters of the Third Kind" once, pauses for 4 seconds, and plays again.
 * @authors Sunny Hu, Peter Gunarso
 */
void task2();

/**
 * @brief Sets up timer and ports needed to drive a speaker using OC4A
 * @author Sunny Hu 
 */
void speakerSetup();

/**
 * @brief Sets up the LED used for this lab
 * @authors Sunny Hu, Peter Gunarso
 */
void ledSetup();
