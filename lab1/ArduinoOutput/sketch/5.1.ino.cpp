#include <Arduino.h>
#line 1 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
int nPeriods;

#line 3 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
void play250(uint8_t pin);
#line 14 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
void setup();
#line 23 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
void loop();
#line 3 "c:\\Users\\redba_000\\OneDrive - UW\\474\\lab1\\5.1\\5.1.ino"
void play250(uint8_t pin) {
  for (int i = 0; i < 50; i++) {
      digitalWrite(pin, HIGH);
      delay(2);
      digitalWrite(pin, LOW);
      delay(2);
      nPeriods++;
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  nPeriods = 0;
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(10, LOW);  // anode of LED is connected to pin 10, so setting pin 10 to LOW actually completes the circuit
  digitalWrite(LED_BUILTIN, LOW);

  if (nPeriods < 500) {
    play250(2);
  } else {
    delay(200);
  }

  digitalWrite(10, HIGH); 
  digitalWrite(LED_BUILTIN, HIGH);

  if (nPeriods < 500) {
    play250(2);
  } else {
    delay(200);
  }
}

