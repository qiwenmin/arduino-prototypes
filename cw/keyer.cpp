#include "Arduino.h"
#include "keyer.h"
#include "led_def.h"

#define KEYER_DEFAULT_PWM 10
#define KEYER_DEFAULT_PIN LED_PIN
#define KEYING_DEFAULT_VALUE LED_ON_VALUE

Keyer::Keyer() {
  this->_state = IDLE;
  this->_pin = KEYER_DEFAULT_PIN;
  this->_keyingValue = KEYING_DEFAULT_VALUE;
  this->setWpm(KEYER_DEFAULT_PWM);
}

void Keyer::init(unsigned long currentMillis) {
  this->_state = IDLE;
  this->_lastMillis = currentMillis;
}

void Keyer::setPin(int value, bool keyingValue) {
  this->_pin = value;
  this->_keyingValue = keyingValue;
}

void Keyer::setWpm(int value) {
  this->_mpe = 1200 / value;
}

bool Keyer::isIdle() {
  return this->_state == IDLE;
}

bool Keyer::keying(int elements) {
  return this->setState(KEYING, elements);
}

bool Keyer::ig(int elements) {
  return this->setState(IG, elements);
}

bool Keyer::setState(State state, int elements) {
  if (state == IDLE) return false;
  if (this->_state == IG) return false;
  if (this->_state == KEYING && state != IG) return false;

  this->_timeout = this->_mpe * elements;
  this->_state = state;

  digitalWrite(this->_pin, this->_state == KEYING ? this->_keyingValue : !this->_keyingValue);

  return true;
}

void Keyer::update(unsigned long currentMillis) {
  if (this->_state == IDLE) {
    this->_lastMillis = currentMillis;
    return;
  }

  if (currentMillis - this->_lastMillis >= this->_timeout) {
    if (this->_state == KEYING) {
      this->setState(IG, 1); // tail gap
    } else { // IG
      this->_state = IDLE;
    }

    this->_lastMillis = currentMillis;
  }
}

