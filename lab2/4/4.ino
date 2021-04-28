#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10

#define MIN 0
#define MAX 7

void spiTransfer(volatile byte row, volatile byte data);

// change these pins as necessary
int DIN = 47;
int CS =  49;
int CLK = 51;

byte spidata[16]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void setup(){

  //must
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CS, HIGH);
  spiTransfer(OP_DISPLAYTEST,0);
  spiTransfer(OP_SCANLIMIT,7);
  spiTransfer(OP_DECODEMODE,0);
  spiTransfer(OP_SHUTDOWN,1);

  int startX = 4;
  int startY = 4;
}

// void setup() {
//   // declare the pins here for the joystick controller
//   // set CS to high thru directly changing the hw register
// }

void loop() {
  int xInc = analogRead(x pin) / 128;
  int yInc = analogRead(y pin) / 128;

  startX +=
}

// from LED_Matrix.ino
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