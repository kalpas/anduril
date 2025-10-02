// voltage.c: Helpers for low-voltage behaviour and temporary overrides.
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "fsm/voltage.h"

#ifdef USE_LVP

#include "fsm/wdt.h"

#ifndef FROST_WINDOW_SECONDS
#define FROST_WINDOW_SECONDS 5
#endif
#define FROST_WINDOW_TICKS (FROST_WINDOW_SECONDS * TICKS_PER_SECOND)

static uint16_t frost_offer_ticks = 0;
static bool frost_request_pending = false;
static bool frost_enabled = false;

void voltage_frost_note_stepdown(void) {
    frost_offer_ticks = FROST_WINDOW_TICKS;
    frost_request_pending = false;
}

void voltage_frost_tick(void) {
    if (frost_offer_ticks) {
        frost_offer_ticks--;
    }
}

bool voltage_frost_offer_active(void) {
    return frost_offer_ticks != 0;
}

void voltage_frost_request_enable(void) {
    frost_offer_ticks = 0;
    frost_request_pending = true;
}

void voltage_frost_commit_enable(void) {
    if (frost_request_pending) {
        frost_enabled = true;
    }
    frost_request_pending = false;
}

bool voltage_frost_is_active(void) {
    return frost_enabled;
}

void voltage_frost_reset(void) {
    frost_offer_ticks = 0;
    frost_request_pending = false;
    frost_enabled = false;
}

#endif  // ifdef USE_LVP

