#ifndef __LED_H__
#define __LED_H__

typedef enum {
  OFF,
  ON
} LedState;

typedef struct {
  LedState state;
} LedContext;

void led_init(LedContext *ctx);
bool led_toggle(LedContext *ctx);

#endif // __LED_H__
