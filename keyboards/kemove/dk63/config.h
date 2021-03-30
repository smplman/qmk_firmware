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

// 1.5(40), 1.4(38), 1.3(37), 1.2(36), 1.1(35), 1.0(34), 0.15(32), 0.14(31), 0.13(30), 0.12(29), 0.11(28), 0.10(27), 0.9(26), 0.8(25)
// #define MATRIX_COL_PINS { GPIOB_PIN5, GPIOB_PIN4, GPIOB_PIN3, GPIOB_PIN2, GPIOB_PIN1, GPIOB_PIN0, GPIOA_PIN15, GPIOA_PIN14, GPIOA_PIN13, GPIOA_PIN12, GPIOA_PIN11, GPIOA_PIN10, GPIOA_PIN9, GPIOA_PIN8 }
// 3.3(50), 3.4(51), 3.5(57), 3.6(58), 3.7(59)
// #define MATRIX_ROW_PINS { GPIOC_PIN3, GPIOC_PIN4, GPIOC_PIN5, GPIOC_PIN6, GPIOC_PIN7 }

// #define MATRIX_COL_PINS { B5, B4, B3, B2, B1, B0, A15, A14, A13, A12, A11, A10, A9, A8 }
// #define MATRIX_ROW_PINS { C3, C4, C5, C6, C7 }
// #define MATRIX_ROW_PINS { D3, D4, D3, D3, D7 }
#define MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5 }
#define MATRIX_ROW_PINS { D7, D6, D5, D4, D3 }
// #define MATRIX_ROW_PINS { D7, D6, D3, D3, D3 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

// #define EEPROM_DRIVER vendor

/* Backlight configuration
 */
#define BACKLIGHT_LEVELS 8

// #define LED_MATRIX_ROWS 14
// #define LED_MATRIX_ROW_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5 }

#define LED_MATRIX_ROWS 15
#define LED_MATRIX_ROW_PINS { C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0, C15}
// #define LED_MATRIX_ROWS 1
// G B R
// #define LED_MATRIX_ROW_PINS { C15 } //{ C15, C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0 }

// #define LED_MATRIX_ROW_PINS { {14, 13, 12}, {11, 10, 9}, {8, 7, 6}, {5, 4, 3}, {1, 0, 15 } }

// #define LED_MATRIX_ROWS 3
// #define LED_MATRIX_ROW_PINS { C15, C14, C13 }
// #define LED_MATRIX_ROW_PINS { C15, C12, C9, C6, C3} // B
// #define LED_MATRIX_ROW_PINS { C14, C11, C8, C5, C1} // R?
// #define LED_MATRIX_ROW_PINS { C13, C10, C7, C4, C0} // G

#define LED_MATRIX_COLS 14
#define LED_MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5 }

// #define LED_MATRIX_COLS 15
// #define LED_MATRIX_COL_PINS { C15, C14, C13, C12, C11, C10, C9, C8, C7, C6, C5, C4, C3, C1, C0 }

// #define LED_MATRIX_COLS 1
// #define LED_MATRIX_COL_PINS { B5 }

#define LED_DRIVER_LED_COUNT 63 // * 3(rgb)
#define DRIVER_LED_TOTAL 63
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

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

// #define WS2812_LED_N 2
// #define RGBLED_NUM WS2812_LED_N
// #define WS2812_TIM_N 2
// #define WS2812_TIM_CH 2
// #define PORT_WS2812     GPIOA
// #define PIN_WS2812      1
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA stream for TIMx_UP (look up in reference manual under DMA Channel selection)
// #define WS2812_DMA_CHANNEL 7                  // DMA channel for TIMx_UP
// #define WS2812_EXTERNAL_PULLUP
