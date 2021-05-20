/**
 * @file SRRI.h
 * @authors Peter Gunarso, Sunny Hu
 * @brief Header file for demo2.ino
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

// possible states for our tasks to be in
enum state {READY, RUNNING, SLEEPING};

enum flagState {PENDING, DONE};

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
 * @brief Sets up interrupts to run on timer 3 A, at a frequency of 500hz
 * @authors Sunny Hu, Peter Gunarso
 */
void interruptSetup();

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