#include <uRTCLib.h>

uRTCLib rtc(0x68);

/* Pin Setup */
int DATA = 8;
int CLOCK = 9;
int REGCLOCK = 10;

/* Global Stores */
int numbers[4];
bool displayMemory[32];
int hours = 12;
int minutes = 12;

bool displayMemoryTest[32] = { HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW, HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW, HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, HIGH };

/*Lifecycle Hooks */
void setup() {
  delay(2000);
  pinMode(DATA, OUTPUT);
  pinMode(REGCLOCK, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  URTCLIB_WIRE.begin();
  Serial.begin(9600);
  rtc.set(5, 7, 5, 7, 2, 5, 15);
}

void loop() {
  static const unsigned long displayRefreshInterval = 1000;
  static const unsigned long clockRefreshInterval = 5000;
  static unsigned long lastRefreshTime = 0;
  static unsigned long lastClockReTime = 0;

  if (millis() - lastRefreshTime >= displayRefreshInterval) {
    lastRefreshTime += displayRefreshInterval;
    updateDisplay();
  }

  if (millis() - lastClockReTime >= clockRefreshInterval) {
    lastClockReTime += clockRefreshInterval;
    updateClock();
  }
}

/* Updates Display */
void updateDisplay() {
  getBackFourDigits(12, 10, numbers);
  setDisplayMemory(numbers[0], numbers[1], numbers[2], numbers[3]);
  writeDisplayRegisters();
}

/* Updates RTC */
void updateClock() {
  rtc.refresh();
  hours = rtc.hour();
  minutes = rtc.minute();
}

/* Puts the Four Digits Into The Numbers Array */
void getBackFourDigits(int hour, int minute, int numbers[]) {
  int hourDecimal = hour / 10;
  int hourSingles = hour % 10;
  int minuteDecimal = minute / 10;
  int minuteSingles = minute % 10;

  numbers[0] = hourDecimal;
  numbers[1] = hourSingles;
  numbers[2] = minuteDecimal;
  numbers[3] = minuteSingles;
}

/* Sets Display Memory Bytes */
void setDisplayMemory(int firstDigit, int secondDigit, int thirdDigit, int fourthDigit) {

  int rDigits[4] = { firstDigit, secondDigit, thirdDigit, fourthDigit };

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

  int displayMemoryAddress = 0;

  for (int r = 0; r < 4; r++) {
    for (int bit = 0; bit < 8; bit++) {
      displayMemory[displayMemoryAddress] = characterMap[rDigits[r]][bit];
      displayMemoryAddress++;
    }
  }

  displayMemoryAddress = 0;
}

/* Bitbang Bits Into The Display Registers */
void writeDisplayRegisters() {
  for (int bit = 0; bit < 32; bit++) {
    writeBit(displayMemory[bit]);
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
