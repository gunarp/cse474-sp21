/* University of Washington
 * ECE/CSE 474,  [4/29]
 *
 *   Sunny Hu
 *   Peter Gunarso
 *
 *   Lab 2, Task 2.4
 *
 */

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(47, LOW);
  digitalWrite(48, HIGH);
  digitalWrite(49, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(333);                       // wait for a second
  digitalWrite(47, HIGH);
  digitalWrite(48, LOW);
  digitalWrite(49, HIGH);    // turn the LED off by making the voltage LOW
  delay(333);
  digitalWrite(47, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(49, LOW);
  delay(333);                       // wait for a second
}
