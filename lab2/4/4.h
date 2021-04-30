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
// timing details for Matrix operation
void taskMATRIX();
// timing details for speaker operation
void taskB();
// utility function which sets the output of OC4A to
// match a given frequency
void setOC4AFreq(uint32_t);
// utility function which operates the lights on the LED matrix
void spiTransfer(volatile byte, volatile byte);