#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10

#define MIN 0
#define MAX 7

void spiTransfer(volatile byte row, volatile byte data);

// change these pins as necessary
//int DIN = 47;
//int CS =  49;
//int CLK = 51;

int DIN = 45;
int CS =  38;
int CLK = 50;

int posX;
int posY;
int resetM = 0;

byte spidata[16]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void setup(){

  //must
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CS, HIGH);
  
  pinMode(A3, INPUT);
  pinMode(A5, INPUT);
  //Serial.begin(9600);

  // turn matrix display off
  for (int i = 0; i < 8; i++) {
    spiTransfer(i, (byte)0);
    //spiTransfer(i, 0b11000000);
  }
  
}

void taskMATRIX() {
  static unsigned long time;
  time++;

  if (resetM) {
    // calculate bit shift for display
    int dispX = -posX + MAX;
  
    // turn the LED at (x, y) on
    spiTransfer(posY, (byte)(1 << dispX));
  }

  if (time == 50) {
    // turn LED at (x, y) off (technically, this clears the whole row.)
    spiTransfer(posY, (byte)0);
    
    posX = analogRead(A5) / 128;
    posY = analogRead(A3) / 128;
  
    // calculate bit shift for display
    int dispX = -posX + MAX;
  
    // turn the LED at (x, y) on
    spiTransfer(posY, (byte)(1 << dispX));

    time = 0;
  }
  return;  
}

void loop() {  
  taskMATRIX();
}

// from LED_Matrix.ino
// 
// this function turns on a collection of LEDs on, with
// opcode selecting the row, and data being the values
// for the entire row. 
void spiTransfer(volatile byte opcode, volatile byte data){
  int offset = 0; //only 1 device
  int maxbytes = 16;

  for(int i = 0; i < maxbytes; i++) { //zero out spi data
    spidata[i] = (byte)0;
  }
  //load in spi data
  spidata[offset+1] = opcode+1;
  spidata[offset] = data;
  digitalWrite(CS, LOW); //
  for(int i=maxbytes;i>0;i--)
    shiftOut(DIN,CLK,MSBFIRST,spidata[i-1]);
  digitalWrite(CS,HIGH);
}
