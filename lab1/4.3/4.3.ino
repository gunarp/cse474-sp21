// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(10, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(10, LOW);  // anode of LED is connected to pin 10, so setting pin 10 to LOW actually completes the circuit
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
  delay(200);
  digitalWrite(10, HIGH); 
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
  delay(200);
}
