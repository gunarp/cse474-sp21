/**
 * @file SRRI.h
 * @authors Peter Gunarso, Sunny Hu
 * @brief Header file for demo4.ino
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
#define BIT4 1<<4
#define BIT5 1<<5
#define BIT6 1<<6
#define BIT7 1<<7

#define S0 0b1110 << 4
#define S1 0b1101 << 4
#define S2 0b1011 << 4
#define S3 0b0111 << 4

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

/// All codes for digits 0-9 on our 7-segment displays
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                                 };



#define NTASKS 10

// possible states for our tasks to be in
enum state {READY, RUNNING, SLEEPING};

enum flagState {PENDING, DONE};

/**
 * @brief Puts currently running function to sleep for t ms
 * 
 * @param t Number of ms for task to sleep for
 */
void sleep_474(long t);
/**
 * @brief Manages sleep time and clocks each task sees. If a task cannot sleep for any longer, wakes up the task.
 * 
 */
void schedule_sync();
/**
 * @brief Sets the frequency of OC4A to match a given frequency freq
 * 
 * @param freq Desired frequency to set OC4A
 */
void setOC4AFreq(uint32_t freq);
/**
 * @brief Manages task 1 behavior, falshes an LED on and off
 * 
 */
void task1();
/**
 * @brief Manages task 2 behavior, plays the theme from "Close Encounters of the Third Kind" once, pauses for 4 seconds, and plays again.
 * 
 */
void task2();
/**
 * @brief Manages task 3 behavior, counts up by tenths of a second on 7-segment display
 * 
 */
void task3();
void convert(int * digits, int val);
void send7(byte arr[7]);
void interruptSetup();
void speakerSetup();
void ledSetup();
void displaySetup();
