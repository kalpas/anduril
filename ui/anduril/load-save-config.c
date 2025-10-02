// load-save-config.c: Load/save/eeprom functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "anduril/load-save-config-fsm.h"
#include "anduril/load-save-config.h"
#ifdef USE_INDICATOR_LED
#include "anduril/aux-leds.h"
#endif

void load_config() {
    eeprom = (uint8_t *)&cfg;

    if (! load_eeprom()) return;

#ifdef USE_INDICATOR_LED
    cfg.indicator_led_mode = indicator_led_normalize(cfg.indicator_led_mode);
#endif

    #ifdef START_AT_MEMORIZED_LEVEL
    if (load_eeprom_wl()) {
        memorized_level = eeprom_wl[0];
    }
    #endif
}

void save_config() {
    eeprom = (uint8_t *)&cfg;
    save_eeprom();
}

#ifdef START_AT_MEMORIZED_LEVEL
void save_config_wl() {
    eeprom_wl[0] = memorized_level;
    save_eeprom_wl();
}
#endif

