#define BIT3 1 << 3;

void freq2OCR4A(int freq) {
  OCR4A = freq == 0 ? 0 : 16000000 / (2 * freq);
}

// freq: desired frequency in Hz
// duration: desired duration in ms
void playTone(int freq, int duration) {
  // all times are in us, the period of the clock
  uint32_t half_period = (500000 / freq);

  int maxTimes = (float) (duration / 1000) * freq;
  uint32_t countFF = 0;
  int countHalfPeriods = 0;

  // start playing the tone
  PORTH |= BIT3;

  while ((countHalfPeriods / 2) < maxTimes) {
    // on the OCF4A flag, one us has passed
    if (OCF4A) {
      countFF++;
    }

    // every half period, flip the state of the speaker
    if (countFF == half_period) {
      // Serial.println("flip");
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

  // set timer to work in set mode (sets to 1)
  TCCR4A |= (0 << COM4A1) | (1 << COM4A0);

  // set the prescaler of the timer to run at
  // about 1 clock cycle / micro second
  // follows the formula:
  //
  //  f_out = f_i/o / 2 * N * (OCR4A + 1)
  //
  // because f_i/o = 16Mhz, we can use
  //  N = 1 and OCR4A = 7 as our values
  TCCR4B |= (0 << CS42) | (0 << CS41) | (1 << CS40);
  OCR4A = 0;
  TCNT4H = 0;
  // OC4A is tied to pin 6, which is controlled by PH3
  // set pin 6 as an output pin
  DDRH |= BIT3;
  Serial.begin(9600);
}

void loop() {
  // playTone(400, 1000);
  // playTone(250, 1000);
  // playTone(800, 1000);
  // delay(1000);
  freq2OCR4A(400);
  delay(1000);
  freq2OCR4A(250);
  delay(1000);
  freq2OCR4A(800);
  delay(1000);
  freq2OCR4A(0);
  delay(1000);
}
