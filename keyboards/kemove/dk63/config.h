/* Copyright 2018 Jack Humbert
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0C45
#define PRODUCT_ID      0x766B
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kemove_Dierya
#define PRODUCT         DK63
#define DESCRIPTION     DK63 Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5 }
#define MATRIX_ROW_PINS { D7, D6, D5, D4, D3 }
// #define MATRIX_ROW_PINS { D4, D4, D4, D4, D3 } // Need to disable cols for SWD

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)
#define LED_MATRIX_ROW_PINS { C15, C0, C1, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14 }

#define LED_MATRIX_COLS 14
#define LED_MATRIX_COL_PINS MATRIX_COL_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 0

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT
#define DRIVER_LED_TOTAL 63
#define RGB_MATRIX_ENABLE 1
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_LED_PROCESS_LIMIT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 0 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
