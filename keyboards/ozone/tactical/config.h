/* Copyright 2022 Philip Mourdjis <philip.j.m@gmail.com>
 * Copyright 2022 Pablo Martinez Bernal <martinezbernalpablo@gmail.com> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

// Random values, couldn't find real ones
#define VENDOR_ID  0x1111 
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001

#define MANUFACTURER Ozone
#define PRODUCT      Tactical
#define DESCRIPTION  Description

// Key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6 } 
#define MATRIX_ROW_PINS { D11, D10, D9, D8, D7 }

// Connects each switch in the dip switch to the GPIO pin of the MCU
#define DIP_SWITCH_PINS { D4 }

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed 
#define DEBOUNCE 5

// RGB config
#define LED_MATRIX_ROWS         MATRIX_ROWS
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW      (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)

// From top down: row1 RGB, row2 RGB (3 pins for each row)
#define LED_MATRIX_ROW_PINS     { C4, C5, C6,  C7, C8, C9,  C10, C11, C12,  C13, C14, B13,  D3, B15, B14 }
#define LED_MATRIX_COLS         MATRIX_COLS
#define LED_MATRIX_COL_PINS     MATRIX_COL_PINS
#define DRIVER_LED_TOTAL        69
#define RGB_DISABLE_TIMEOUT     60000 //1min without input => turn off LEDs
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 //maximum brightness allowed

#define RGB_MATRIX_STARTUP_VAL 40 //low brightness
#define RGB_MATRIX_STARTUP_SPD 80

#define TAPPING_TERM 200

// RGB Matrix Effects
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// #define ENABLE_RGB_MATRIX_ALPHAS_MODS
// #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define ENABLE_RGB_MATRIX_HUE_BREATHING
