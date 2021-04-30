#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10

#define MAX 7

// ========================================================
// speaker constants
// ========================================================
#define BIT0 1<<0
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3

#define TIMER_REG_A TCCR4A
#define TIMER_REG_B TCCR4B
#define TIMER_MASK TIMSK4
#define TIMER_COUNTER TCNT4H
#define PRESCALER OCR4A
#define SPEAKER_DDR DDRH
#define SPEAKER_PORT PORTH

#define note_c 261
#define note_d 294
#define note_e 329
#define note_f 349
#define note_g 392
#define note_a 440
#define note_b 493
#define note_C 523
#define note_R 0

#define PLAY_DURATION 200
#define NFREQ 53
int melody[] = { note_e, note_R, note_d, note_R, note_c, note_R, note_d, note_R,
                 note_e, note_R, note_e, note_R, note_e, note_R, note_d, note_R,
                 note_d, note_R, note_d, note_R, note_e, note_R, note_g, note_R,
                 note_g, note_R, note_e, note_R, note_d, note_R, note_c, note_R,
                 note_d, note_R, note_e, note_R, note_e, note_R, note_e, note_R,
                 note_e, note_R, note_d, note_R, note_d, note_R, note_e, note_R,
                 note_d, note_R, note_c, note_R, note_c };

// ========================================================
// matrix constants
// ========================================================
#define DIN 45
#define CS 38
#define CLK 50

#define DIN_BIT 1<<4
#define CS_BIT 1<<7
#define CLK_BIT 1<<3;

#define DIN_DDR DDRL
#define CS_DDR DDRD
#define CLK_DDR DDRB

#define CS_PORT PORTD

#define XYINPUT_DDR DDRF
#define XIN_BIT 1 << 3
#define YIN_BIT 1 << 5

// ========================================================
// function prototypes
// ========================================================
/***************************************************
 * void taskMATRIX();
 *      Handles the timing of the LED Matrix operation, using
 *      the connected joystick to control the lit dot in the matrix.
 *
 *      Author Sunny Hu
 */

void taskMATRIX();
/***************************************************
 * void taskB();
 *      Handles the timing of the speaker operation, cycles
 *      through notes in melody, with each tone playing
 *      for PLAY_DURATION milliseconds
 *
 *      Author Peter Gunarso
 */

void taskB();
/***************************************************
 * void setOC4AFreq(uint32_t freq)
 *      freq - The desired output frequency for OC4A
 *      Returns - Nothing, but sets the clock cycle frequency
 *                of OC4A to be freq
 *
 *      Sets the prescaler of the OC4A clock to make OC4A go at a
 *      frequency of freq. Follows the equation:
 *
 *      f_out = f_i/o / 2 * N * (PRESCALER + 1)
 *
 *      and assumes N=1
 *
 *      Author Peter Gunarso
 *
 */
void setOC4AFreq(uint32_t);

/***************************************************
 * void spiTransfer(volatile byte opcode, voltatile byte data)
 *      opcode - row selector
 *      data - row data
 *
 *      this function turns on a collection of LEDs on, with
 *      opcode selecting the row, and data being the values
 *      for the entire row.
 *
 *      Author Ishaan Bhimani
 *
 */
void spiTransfer(volatile byte, volatile byte);