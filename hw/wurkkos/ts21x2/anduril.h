// Wurkkos TS21 dual-7135 hardware variant for Anduril on the Attiny1616
// Uses Sofirn SP36 ramp tables as a baseline but doubles the regulated
// channel current (2x 7135) and re-enables the regulated/FET crossover blip.
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "sofirn/sp36-t1616/anduril.h"

// The dual-7135 hardware shouldn't blink at the top of the ramp.
#ifdef BLINK_AT_RAMP_CEIL
#undef BLINK_AT_RAMP_CEIL
#endif
#ifdef BLINK_AT_RAMP_CEILING
#undef BLINK_AT_RAMP_CEILING
#endif

// Use only the two moon levels in lockout mode, never manual memory.
#ifdef USE_MANUAL_MEMORY_IN_LOCKOUT_MODE
#undef USE_MANUAL_MEMORY_IN_LOCKOUT_MODE
#endif

// doubled linear channel current (2x 7135) needs a new mixed-channel ramp
// level_calc.py 5.7895 2 150 7135 1 0.1 260 FET 1 10 3000 --pwm dyn:74:4096:255:3
#undef PWM1_LEVELS
#define PWM1_LEVELS \
    1, 2, 2, 2, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, \
    9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19, 20, 21, 22, \
    23, 24, 25, 26, 27, 28, 28, 29, 30, 31, 32, 33, 34, 35, 36, \
    37, 38, 39, 40, 41, 43, 44, 45, 47, 48, 50, 52, 54, 56, 58, \
    61, 64, 67, 70, 74, 77, 82, 86, 91, 96, 102, 108, 115, 121, 128, \
    135, 143, 151, 159, 168, 177, 186, 196, 206, 217, 228, 240, 252, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0
#undef PWM2_LEVELS
#define PWM2_LEVELS \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, \
    4, 5, 7, 8, 10, 11, 13, 14, 16, 18, 20, 22, 24, 26, 28, \
    31, 33, 35, 38, 41, 43, 46, 49, 52, 55, 59, 62, 65, 69, 73, \
    76, 80, 84, 89, 93, 97, 102, 107, 112, 117, 122, 127, 133, 138, 144, \
    150, 156, 163, 169, 176, 183, 190, 198, 205, 213, 221, 229, 237, 246, 255
#undef PWM_TOPS
#define PWM_TOPS \
    4095, 3321, 2549, 3602, 2765, 1937, 2902, 2279, 2740, 2231, 2484, 2586, 2203, 2259, 2260, \
    1955, 1946, 1913, 1863, 1804, 1738, 1541, 1486, 1427, 1367, 1307, 1248, 1190, 1133, 1079, \
    1026, 975, 927, 881, 837, 795, 755, 717, 681, 647, 615, 585, 556, 529, 503, \
    479, 456, 434, 413, 394, 384, 366, 349, 340, 324, 316, 307, 298, 290, 281, \
    278, 273, 269, 264, 263, 257, 258, 255, 254, 253, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, \
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255

#undef MAX_1x7135
#define MAX_1x7135 88

// align stepped ramp to include a stop at the MAX_1x7135 crossover level
#undef RAMP_DISCRETE_CEIL
#define RAMP_DISCRETE_CEIL 122  // 20, 37, 54, 71, 88, 105, 122

// always allow moon mode to use the lowest available floor, even in stepped ramping
#define USE_LOWEST_MOON_LEVEL

// emit a blip when crossing from the linear channel to the FET
#define BLINK_AT_RAMP_MIDDLE
#define BLINK_AT_RAMP_MIDDLE_1 MAX_1x7135

// add a 500 ms dwell at the MAX_1x7135 crossover while smooth-ramping
#define USE_RAMP_CROSSOVER_GATE

