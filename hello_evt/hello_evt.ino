#include <Eventually.h>
#include "led.h"

EvtManager mgr;

USE_EVENTUALLY_LOOP(mgr)

LedContext ledCtx;

void setup() {
  led_init(&ledCtx);

  EvtTimeListener *ledToggleEvtLsnr = new EvtTimeListener(500, true, on_led_toggle);
  ledToggleEvtLsnr->extraData = &ledCtx;
  mgr.addListener(ledToggleEvtLsnr);
}

bool on_led_toggle(EvtListener *lsnr, EvtContext *) {
  LedContext *ctx = (LedContext *)lsnr->extraData;
  return led_toggle(ctx);
}

