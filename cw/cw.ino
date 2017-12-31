#include "keyer.h"

Keyer keyer;

static unsigned long currentMillis;

void setup() {
  currentMillis = millis();

  pinMode(1, OUTPUT);

  keyer.init(currentMillis);
  keyer.setPin(1);
  keyer.setWpm(20);
}

const char codes[] PROGMEM = {
  3, 1, 3, 1, -2, // c
  3, 3, 1, 3, -6,  // q

  3, 1, 3, 1, -2, // c
  3, 3, 1, 3, -6,  // q

  3, 1, 1, -2, // d
  1, -6, // e

  3, 1, 1, 1, -2, // b
  3, 3, 1, -2, // g
  1, 3, 3, 3, 3, -2, // 1
  1, 3, 1, -2, // r
  1, -2, // e
  3, 1, -6, // n

  3, 1, 1, 1, -2, // b
  3, 3, 1, -2, // g
  1, 3, 3, 3, 3, -2, // 1
  1, 3, 1, -2, // r
  1, -2, // e
  3, 1, -6, // n

  3, 1, 3, -13 // k
};

static int codeIndex = 0;
static int codeLen = sizeof(codes);

void loop() {
  currentMillis = millis();

  if (keyer.isIdle()) {
    char c = pgm_read_byte(&codes[codeIndex]);
    codeIndex ++;
    if (codeIndex >= codeLen) codeIndex = 0;

    if (c > 0)
      keyer.keying(c);
    else
      keyer.ig(-c);
  }

  keyer.update(currentMillis);
}

