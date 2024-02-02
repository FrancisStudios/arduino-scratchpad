#include <uRTCLib.h>

uRTCLib rtc(0x68);

int DATA = 8;
int CLOCK = 9;
int REGCLOCK = 10;

int numbers[4];

void setup() {
  delay(2000);
  pinMode(DATA, OUTPUT);
  pinMode(REGCLOCK, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  URTCLIB_WIRE.begin();
  Serial.begin(9600);
  rtc.set(0, 6, 21, 6, 2, 5, 15);
}

void loop() {
  rtc.refresh();

  getBackFourDigits(rtc.hour(), rtc.minute(), numbers);

  Serial.print(numbers[0]);
  Serial.print(numbers[1]);
  Serial.print(':');
  Serial.print(numbers[2]);
  Serial.print(numbers[3]);
  Serial.println();
  delay(1000);
}


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
