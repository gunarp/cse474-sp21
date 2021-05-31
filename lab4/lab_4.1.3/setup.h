/**
 * @file RR.h
 * @authors Peter Gunarso, Sunny Hu
 * @brief Header file for demo1.ino
 * @version 0.1
 * @date 2021-05-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#define TIMER_REG_A TCCR4A
#define TIMER_REG_B TCCR4B
#define TIMER_MASK TIMSK4
#define TIMER_COUNTER TCNT4H
#define PRESCALER OCR4A
#define LED_DDR DDRL
#define LED_PORT PORTL
#define LED_BIT 1 << 2
#define SPEAKER_DDR DDRH
#define SPEAKER_PORT PORTH
#define NSAMPLES 512

#define PLAY_DURATION 200
#define NPLAY 3

#define note_c3 130
#define note_c4 261
#define note_d4 293
#define note_e4 329
#define note_g3 196
#define note_R 0

#define NFREQ 13
int melody[] = { note_d4, note_R, note_e4, note_R, note_c4, note_R, note_c3,
                 note_R, note_g3, note_g3, note_g3, note_g3, note_R };

// define two tasks for Blink & AnalogRead
void TaskBlink(void * pvParameters);
void TaskTheme(void * pvParameters);
void Task34Starter(void * pvParameters);
void Task3(void * pvParameters);
void Task4(void * pvParameters);

/**
 * @brief
 * @author
 */
void ledSetup();

/**
 * @brief Sets up timer and ports needed to drive a speaker using OC4A
 * @author Sunny Hu
 */
void speakerSetup();

/**
 * @brief Sets the frequency of OC4A to match a given frequency freq
 * @authors Sunny Hu, Peter Gunarso
 * @param freq Desired frequency to set OC4A
 */
void setOC4AFreq(uint32_t freq);
