# 1 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
int nPeriods;

void play250(uint8_t pin) {
  for (int i = 0; i < 50; i++) {
      digitalWrite(pin, 0x1);
      delay(2);
      digitalWrite(pin, 0x0);
      delay(2);
      nPeriods++;
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(10, 0x1);
  pinMode(13, 0x1);
  pinMode(2, 0x1);
  nPeriods = 0;
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(10, 0x0); // anode of LED is connected to pin 10, so setting pin 10 to LOW actually completes the circuit
  digitalWrite(13, 0x0);

  if (nPeriods < 500) {
    play250(2);
  } else {
    delay(200);
  }

  digitalWrite(10, 0x1);
  digitalWrite(13, 0x1);

  if (nPeriods < 500) {
    play250(2);
  } else {
    delay(200);
  }
}
