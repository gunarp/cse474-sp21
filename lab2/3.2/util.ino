void timerSetup() {
  // clear timer settings
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

  // set output pins for taskA
  DDRL |= BIT0;
  DDRL |= BIT1;
  DDRL |= BIT2;

}