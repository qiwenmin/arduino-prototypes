#include "Arduino.h"
#include "led.h"

void led_init(LedContext *ctx) {
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);

  ctx->state = OFF;
}

bool led_toggle(LedContext *ctx) {
  ctx->state = ctx->state == OFF ? ON : OFF;

  digitalWrite(1, ctx->state == ON);
}

