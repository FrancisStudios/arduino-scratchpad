int DATA = 8;
int REGCLOCK = 10;
int CLOCK = 9;


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(REGCLOCK, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Serial.begin(9600);
}

boolean character_nine[8] = { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH };

void loop() {
  writeChar(character_nine);
  delay(1000);
}

void writeChar(boolean character[8]) {
  for (int i = 0; i < 8; i++) {
    writeBit(character[i]);
  }
}

void writeBit(boolean bit) {
  digitalWrite(REGCLOCK, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(DATA, bit);
  digitalWrite(CLOCK, LOW);
  digitalWrite(REGCLOCK, HIGH);
}