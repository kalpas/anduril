// Helpers for channel modes which need a no-op gradual tick
// Copyright (C) 2025 Anduril contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

static inline bool gradual_tick_null(uint8_t gt)
{
    (void) gt;
    return true;
}
