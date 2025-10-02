// aux-leds.h: Aux LED functions for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define INDICATOR_LED_MODE_OFF     0
#define INDICATOR_LED_MODE_LOW     1
#define INDICATOR_LED_MODE_HIGH    2
#define INDICATOR_LED_MODE_BLINK   3
#define INDICATOR_LED_MODE_BEACON  4

#define INDICATOR_LED_FIELD_WIDTH      3
#define INDICATOR_LED_OFF_MASK         ((1 << INDICATOR_LED_FIELD_WIDTH) - 1)
#define INDICATOR_LED_LOCKOUT_SHIFT    INDICATOR_LED_FIELD_WIDTH
#define INDICATOR_LED_LOCKOUT_MASK     (INDICATOR_LED_OFF_MASK << INDICATOR_LED_LOCKOUT_SHIFT)

#ifdef TICK_DURING_STANDBY
    #define INDICATOR_LED_NUM_MODES    5
#else
    #define INDICATOR_LED_NUM_MODES    3
#endif

#define INDICATOR_LED_COMPOSE(off_mode, lock_mode) \
    ((((lock_mode) & INDICATOR_LED_OFF_MASK) << INDICATOR_LED_LOCKOUT_SHIFT) \
     | ((off_mode) & INDICATOR_LED_OFF_MASK))

static inline uint8_t indicator_led_get_off_field(uint8_t value) {
    return value & INDICATOR_LED_OFF_MASK;
}

static inline uint8_t indicator_led_get_lock_field(uint8_t value) {
    return (value & INDICATOR_LED_LOCKOUT_MASK) >> INDICATOR_LED_LOCKOUT_SHIFT;
}

static inline uint8_t indicator_led_normalize(uint8_t value) {
    uint8_t off = indicator_led_get_off_field(value);
    uint8_t lock = indicator_led_get_lock_field(value);

    if ((off >= INDICATOR_LED_NUM_MODES) || (lock >= INDICATOR_LED_NUM_MODES)) {
        uint8_t legacy_off = value & 0x03;
        uint8_t legacy_lock = (value >> 2) & 0x03;
        off = legacy_off;
        lock = legacy_lock;
    }

    if (off >= INDICATOR_LED_NUM_MODES) {
        off %= INDICATOR_LED_NUM_MODES;
    }
    if (lock >= INDICATOR_LED_NUM_MODES) {
        lock %= INDICATOR_LED_NUM_MODES;
    }

    return INDICATOR_LED_COMPOSE(off, lock);
}

static inline uint8_t indicator_led_get_off_mode(uint8_t value) {
    return indicator_led_get_off_field(indicator_led_normalize(value));
}

static inline uint8_t indicator_led_get_lockout_mode(uint8_t value) {
    return indicator_led_get_lock_field(indicator_led_normalize(value));
}

static inline uint8_t indicator_led_set_off_mode(uint8_t value, uint8_t mode) {
    value = indicator_led_normalize(value);
    mode %= INDICATOR_LED_NUM_MODES;
    return (value & (~INDICATOR_LED_OFF_MASK)) | (mode & INDICATOR_LED_OFF_MASK);
}

static inline uint8_t indicator_led_set_lockout_mode(uint8_t value, uint8_t mode) {
    value = indicator_led_normalize(value);
    mode %= INDICATOR_LED_NUM_MODES;
    return (value & (~INDICATOR_LED_LOCKOUT_MASK))
        | ((mode & INDICATOR_LED_OFF_MASK) << INDICATOR_LED_LOCKOUT_SHIFT);
}

static inline uint8_t indicator_led_next_mode(uint8_t mode) {
    mode = (mode + 1) % INDICATOR_LED_NUM_MODES;
    #ifdef INDICATOR_LED_SKIP_LOW
    if (mode == INDICATOR_LED_MODE_LOW) {
        mode = (mode + 1) % INDICATOR_LED_NUM_MODES;
    }
    #endif
    return mode;
}

#if defined(USE_INDICATOR_LED) && defined(TICK_DURING_STANDBY)
void indicator_led_update(uint8_t mode, uint16_t tick);
#endif
#if defined(USE_AUX_RGB_LEDS) && defined(TICK_DURING_STANDBY)
uint8_t setting_rgb_mode_now = 0;
void rgb_led_update(uint8_t mode, uint16_t arg);
void rgb_led_voltage_readout(uint8_t bright);
/*
 * 0: R
 * 1: RG
 * 2:  G
 * 3:  GB
 * 4:   B
 * 5: R B
 * 6: RGB
 * 7: rainbow
 * 8: voltage
 */
const PROGMEM uint8_t rgb_led_colors[] = {
    0b00000000,  // 0: black
    0b00000001,  // 1: red
    0b00000101,  // 2: yellow
    0b00000100,  // 3: green
    0b00010100,  // 4: cyan
    0b00010000,  // 5: blue
    0b00010001,  // 6: purple
    0b00010101,  // 7: white
};
// intentionally 1 higher than total modes, to make "voltage" easier to reach
// (at Hank's request)
#define RGB_LED_NUM_COLORS 11
#define RGB_LED_NUM_PATTERNS 4
#ifndef RGB_LED_OFF_DEFAULT
#define RGB_LED_OFF_DEFAULT 0x19  // low, voltage
//#define RGB_LED_OFF_DEFAULT 0x18  // low, rainbow
#endif
#ifndef RGB_LED_LOCKOUT_DEFAULT
#define RGB_LED_LOCKOUT_DEFAULT 0x39  // blinking, voltage
//#define RGB_LED_LOCKOUT_DEFAULT 0x37  // blinking, disco
#endif
#ifndef RGB_RAINBOW_SPEED
#define RGB_RAINBOW_SPEED 0x0f  // change color every 16 frames
#endif
#endif

//#define USE_OLD_BLINKING_INDICATOR
//#define USE_FANCIER_BLINKING_INDICATOR
#ifdef USE_INDICATOR_LED
    // bits 3-5 control lockout mode
    // bits 0-2 control "off" mode
    // modes are: 0=off, 1=low, 2=high, 3=blink, 4=10s beacon (blink/beacon require TICK_DURING_STANDBY)
    #ifndef INDICATOR_LED_DEFAULT_MODE
        #ifdef USE_INDICATOR_LED_WHILE_RAMPING
            #define INDICATOR_LED_DEFAULT_MODE INDICATOR_LED_COMPOSE(INDICATOR_LED_MODE_LOW, INDICATOR_LED_MODE_HIGH)
        #else
            #define INDICATOR_LED_DEFAULT_MODE INDICATOR_LED_COMPOSE(INDICATOR_LED_MODE_LOW, INDICATOR_LED_MODE_BLINK)
        #endif
    #endif
#endif

