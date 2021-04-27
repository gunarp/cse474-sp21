void setup() {
  // OC4A is tied to pin 6, which is controlled by PH4
  DDRH |= 1 << 4;
}