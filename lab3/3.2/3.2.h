#define BIT0 1<<0
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3

#define TIMER_REG_A TCCR4A
#define TIMER_REG_B TCCR4B
#define TIMER_MASK TIMSK4
#define TIMER_COUNTER TCNT4H
#define PRESCALER OCR4A
#define LED_DDR DDRL
#define LED_PORT PORTL
#define SPEAKER_DDR DDRH
#define SPEAKER_PORT PORTH

#define FLASH_DURATION 333
#define NFLASH 3
#define PLAY_DURATION 200
#define ADURATION 2000
#define CDURATION 10000

#define note_c 261
#define note_d 294
#define note_e 329
#define note_f 349
#define note_g 392
#define note_a 440
#define note_b 493
#define note_C 523
#define note_R 0

#define NFREQ 53
// #define NFREQ 4
int melody[] = { note_e, note_R, note_d, note_R, note_c, note_R, note_d, note_R,
                 note_e, note_R, note_e, note_R, note_e, note_R, note_d, note_R,
                 note_d, note_R, note_d, note_R, note_e, note_R, note_g, note_R,
                 note_g, note_R, note_e, note_R, note_d, note_R, note_c, note_R,
                 note_d, note_R, note_e, note_R, note_e, note_R, note_e, note_R,
                 note_e, note_R, note_d, note_R, note_d, note_R, note_e, note_R,
                 note_d, note_R, note_c, note_R, note_c };
// int melody[] = {400, 250, 800, 0};