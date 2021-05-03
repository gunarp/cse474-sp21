#define BIT3 1 << 3;

// freq: desired frequency in Hz
// duration: desired duration in ms
void playTone(int freq, uint32_t duration) {
  if (freq == 0) {
    uint32_t count = 0;
    uint32_t maxTimes = duration * 1000;
    PORTH &= ~BIT3;
    while (count < maxTimes) {
      if (TIFR4 & (1 << OCF4A)) {
        count++;
        TIFR4 = (1 << OCF4A);
      }
    }
    return;
  }
  // all times are in us, the period of the clock
  uint32_t half_period = (500000 / freq);

  int maxTimes = ((float) duration / 1000) * freq;
  uint32_t countFF = 0;
  int countHalfPeriods = 0;

  // start playing the tone
  PORTH |= BIT3;

  while ((countHalfPeriods / 2) < maxTimes) {
    // on the OCF4A flag, one us has passed
    if (TIFR4 & (1 << OCF4A)) {
      countFF++;
      TIFR4 = (1 << OCF4A);
    }

    // every half period, flip the state of the speaker
    if (countFF == half_period) {
      PORTH ^= BIT3;
      countFF = 0;
      countHalfPeriods++;
    }
  }

  // ensure speaker is off afterwards
  PORTH &= ~BIT3;
}

void setup() {
  TCCR4A = 0;
  TCCR4B = 0;
  // set our timer to work in CTC mode
  TCCR4A |= (0 << WGM41) | (0 << WGM40);
  TCCR4B |= (0 << WGM43) | (1 << WGM42);

  // disable OC4A output (we'll drive the pin ourself)
  TCCR4A |= (0 << COM4A1) | (0 << COM4A0);

  // disable interrupts on the timer
  TIMSK4 = 0;

  // set the prescaler of the timer to run at
  // about 1 clock cycle / micro second
  // follows the formula:
  //
  //  f_out = f_i/o / 2 * N * (OCR4A + 1)
  //
  // because f_i/o = 16Mhz, we can use
  //  N = 1 and OCR4A = 7 as our values
  TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
  OCR4A = 7;
  TCNT4H = 0;

  // OC4A is tied to pin 6, which is controlled by PH3
  // set pin 6 as an output pin
  DDRH |= BIT3;
  Serial.begin(9600);
}

void loop() {
  playTone(400, 1000);
  playTone(250, 1000);
  playTone(800, 1000);
  playTone(0, 1000);
}
