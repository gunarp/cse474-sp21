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

typedef struct TCB {
  char name[20];
  void (*fn_ptr)();
  int id;
  int nTimes;
  int timeSleep;
  int time;
  STATE state;
} tcb;

void sleep_474(long t);
void schedule_sync();
void task_self_quit();
void task_start(tcb * task);
void task_load(void (*fn_ptr)(), const char *);
void setOC4AFreq(uint32_t freq);
void task1();
void task2();
void speakerSetup();
void ledSetup();
