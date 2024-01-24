int DATA = 8;
int REGCLOCK = 10;
int CLOCK = 9;


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(REGCLOCK, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Serial.begin(9600);
}

boolean data = HIGH;

void loop() {
  digitalWrite(REGCLOCK, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(DATA, data);
  digitalWrite(CLOCK, LOW);
  digitalWrite(REGCLOCK, HIGH);

  data == HIGH
    ? data = LOW
    : data = HIGH;


  delay(1000);
}