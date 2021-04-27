// 49 -> PL0
// 48 -> PL1
// 47 -> PL2

// source: https://wiki.wpi.edu/robotics/Port_manipulation_and_digitalWrite()#The_easy_way

#define BIT0 1<<0;
#define BIT1 1<<1;
#define BIT2 1<<2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  DDRL |= BIT0;
  DDRL |= BIT1;
  DDRL |= BIT2;
}

// the loop function runs over and over again forever
void loop() {
  DDRL |= BIT2;
  DDRL &= ~BIT1;
  DDRL &= ~BIT0;
  delay(333);                       // wait for a second
  DDRL &= ~BIT2;
  DDRL |= BIT1;
  DDRL &= ~BIT0;
  delay(333);
  DDRL &= ~BIT2;
  DDRL &= ~BIT1;
  DDRL |= BIT0;
  delay(333);                       // wait for a second
}
