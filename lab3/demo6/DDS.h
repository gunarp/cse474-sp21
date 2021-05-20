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
#define TASK2_DURATION (2 * (NFREQ * PLAY_DURATION) + PAUSE_DURATION)
#define SMILE_DURATION 2000
#define PAUSE_DURATION_T5 3000

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

byte smile_seg[4][7] = { { 0,0,0,0,1,0,0 },  // = right
                         { 1,1,0,1,0,1,0 },  // = eye
                         { 1,1,0,1,0,1,0 },  // = eye
                         { 0,0,1,0,0,0,0 },  // = left
                       };

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
tcb * find_dead_task(char * name);
void setOC4AFreq(uint32_t freq);
void send7(byte arr[7]);
void convert(int * digits, int val);
void task1();
void task2();
void task4();
void task4_1();
void task4_2();
void task5();
void task5_1();
void speakerSetup();
void ledSetup();
void DDSSetup();
