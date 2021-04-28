#define BIT0 1<<0;
#define BIT1 1<<1;
#define BIT2 1<<2;
#define BIT3 1<<3;

#define NUM_FUNC 2
void (*task_list[NUM_FUNC + 1])(void *p);

// sets the OCR4A to make the clock cycle frequency
// the same as the input freq
void freq2OCR4A(uint32_t freq) {
  OCR4A = freq == 0 ? 0 : 16000000 / (2 * freq);
  TCNT4H = 0;
}

// plays the given freq for one second
void playOneSec(int freq) {
  uint32_t maxHalfPeriods = 2 * (uint32_t) freq;
  if (freq == 0) {
    freq2OCR4A(100000);
    maxHalfPeriods = 2 * 100000;
  } else {
    freq2OCR4A(freq);
  }
  uint32_t countHalfPeriods = 0;
  unsigned long start = millis();
  while (countHalfPeriods < maxHalfPeriods) {
    if (TIFR4 & (1 << OCF4A)) {
      countHalfPeriods++;
      TIFR4 = (1 << OCF4A);
    }
  }
  Serial.println(millis() - start);
}

void taskA(void * ptr) {
  // TODO: change delay to non blocking
  PORTL &= ~BIT2;
  PORTL |= BIT1;
  PORTL |= BIT0;
  delay(333);                       // wait for .333 seconds
  PORTL |= BIT2;
  PORTL &= ~BIT1;
  PORTL |= BIT0;
  delay(333);
  PORTL |= BIT2;
  PORTL |= BIT1;
  PORTL &= ~BIT0;
  delay(333);                       // wait for .333 seconds
}

void taskB(void * ptr) {
  playOneSec(400);
  playOneSec(250);
  playOneSec(800);
  playOneSec(0);
}

void setup() {
  timerSetup();
  // set up our function table
  Serial.begin(9600);
}

void loop() {
}
