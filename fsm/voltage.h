// voltage.h: Helpers for low-voltage behaviour and temporary overrides.
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef USE_LVP

void voltage_frost_note_stepdown(void);
void voltage_frost_tick(void);
bool voltage_frost_offer_active(void);
void voltage_frost_request_enable(void);
void voltage_frost_commit_enable(void);
bool voltage_frost_is_active(void);
void voltage_frost_reset(void);

#else

static inline void voltage_frost_note_stepdown(void) {}
static inline void voltage_frost_tick(void) {}
static inline bool voltage_frost_offer_active(void) { return false; }
static inline void voltage_frost_request_enable(void) {}
static inline void voltage_frost_commit_enable(void) {}
static inline bool voltage_frost_is_active(void) { return false; }
static inline void voltage_frost_reset(void) {}

#endif

