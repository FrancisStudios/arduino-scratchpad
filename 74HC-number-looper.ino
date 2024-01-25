int DATA = 8;
int REGCLOCK = 10;
int CLOCK = 9;


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(REGCLOCK, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Serial.begin(9600);
}
// { 6    5    4    3    2    1    8    7   };
// { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };

bool character_one[8] = { LOW, LOW, LOW, HIGH, HIGH, LOW, LOW, LOW };
bool character_two[8] = { LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH };
bool character_three[8] = { LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW, HIGH };
bool character_four[8] = { HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH };
bool character_five[8] = { HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW, HIGH };
bool character_six[8] = { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, LOW, HIGH };
bool character_seven[8] = { LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, HIGH };
bool character_eight[8] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH };
bool character_nine[8] = { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH };
bool character_zero[8] = { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW };

bool characterMap[10][8] = { character_one[8], character_two[8], character_three[8], character_four[8], character_five[8], character_six[8], character_seven[8], character_eight[8], character_nine[8], character_zero[8] };

int n = 0;
//bool charSelection[8] = characterMap[1];

void loop() {
  //writeChar(character_two);
  /* Multiple writes helps unstuck register bits */
  numberLooper(n);
  delay(100);
  numberLooper(n);
  delay(100);
  numberLooper(n);
  delay(1000);

  n == 9
    ? n = 0
    : n++;
}

/* Writes a char on the Segments */
void writeChar(bool character[8]) {
  for (int i = 0; i < 8; i++) {
    writeBit(character[i]);
  }
}

/* Writes a bit to the 74HC Series Register */
void writeBit(bool bit) {
  digitalWrite(REGCLOCK, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(DATA, bit);
  digitalWrite(CLOCK, LOW);
  digitalWrite(REGCLOCK, HIGH);
}

/* Gets desired number data */
bool* getCharacter(int number) {
  bool characterMap[10][8] = {
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW },
    { LOW, LOW, LOW, HIGH, HIGH, LOW, LOW, LOW },
    { LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH },
    { LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW, HIGH },
    { HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH },
    { HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW, HIGH },
    { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, LOW, HIGH },
    { LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, HIGH },
    { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH },
    { HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH }
  };

  bool character[8];

  for (int segmentCounter = 0; segmentCounter < 8; segmentCounter++) {
    character[segmentCounter] = characterMap[number][segmentCounter];
  }

  return character;
}

void numberLooper(int number) {
  switch (number) {
    case 0:
      writeChar(character_zero);
      break;
    case 1:
      writeChar(character_one);
      break;
    case 2:
      writeChar(character_two);
      break;
    case 3:
      writeChar(character_three);
      break;
    case 4:
      writeChar(character_four);
      break;
    case 5:
      writeChar(character_five);
      break;
    case 6:
      writeChar(character_six);
      break;
    case 7:
      writeChar(character_seven);
      break;
    case 8:
      writeChar(character_eight);
      break;
    case 9:
      writeChar(character_nine);
      break;
  }
}