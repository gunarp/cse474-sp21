#define BIT3 1 << 3;

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
  while (countHalfPeriods < maxHalfPeriods) {
    if (TIFR4 & (1 << OCF4A)) {
      countHalfPeriods++;
      TIFR4 = (1 << OCF4A);
    }
  }
}

void setup() {
  TCCR4A = 0;
  TCCR4B = 0;
  // set our timer to work in CTC mode
  TCCR4A |= (0 << WGM41) | (0 << WGM40);
  TCCR4B |= (0 << WGM43) | (1 << WGM42);

  // set timer to work in toggle mode
  TCCR4A |= (0 << COM4A1) | (1 << COM4A0);

  // disable interrupts on the timer
  TIMSK4 = 0;

  // set the prescaler of the timer,
  // which follows the formula:
  //
  //  f_out = f_i/o / 2 * N * (OCR4A + 1)
  //
  // because f_i/o = 16Mhz, we'll just set N = 1
  TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
  OCR4A = 0;
  TCNT4H = 0;

  // OC4A is tied to pin 6, which is controlled by PH3
  // set pin 6 as an output pin
  DDRH |= BIT3;
}

void loop() {
  playOneSec(400);
  playOneSec(250);
  playOneSec(800);
  playOneSec(0);
}
