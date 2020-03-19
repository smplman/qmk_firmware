/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Ported to QMK by Stephen Peery <https://github.com/smp4488/>
*/

#include <stdint.h>
#include <stdbool.h>
#include <SN32F240B.h>
#include "ch.h"
#include "hal.h"
#include "CT16.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
matrix_row_t last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t matrix[MATRIX_ROWS]; //debounced values

static bool matrix_changed = false;
static uint8_t current_col = 0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void init_pins(void) {

    //  Unselect ROWs
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinOutput(row_pins[x]);
        writePinHigh(row_pins[x]);
    }

    // Unselect COLs
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }
}

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();

    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    // PFPA - Set PWM to port B pins
    SN_PFPA->CT16B1 = 0xFFFF00;         // 8-9, 11-23 = top half 16 bits

    // Enable PWM function, IOs and select the PWM modes
    // Enable PWM8-PWM9, PWM11-PWM23 function
    SN_CT16B1->PWMENB   =   (mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM15EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN \
                            |mskCT16_PWM22EN_EN \
                            |mskCT16_PWM23EN_EN);

    // Enable PWM8-PWM9 PWM12-PWM23 IO
    SN_CT16B1->PWMIOENB =   (mskCT16_PWM8IOEN_EN  \
                            |mskCT16_PWM9IOEN_EN  \
                            |mskCT16_PWM11IOEN_EN \
                            |mskCT16_PWM12IOEN_EN \
                            |mskCT16_PWM13IOEN_EN \
                            |mskCT16_PWM14IOEN_EN \
                            |mskCT16_PWM15IOEN_EN \
                            |mskCT16_PWM16IOEN_EN \
                            |mskCT16_PWM17IOEN_EN \
                            |mskCT16_PWM18IOEN_EN \
                            |mskCT16_PWM19IOEN_EN \
                            |mskCT16_PWM20IOEN_EN \
                            |mskCT16_PWM21IOEN_EN \
                            |mskCT16_PWM22IOEN_EN \
                            |mskCT16_PWM23IOEN_EN);

    // Select as PWM mode 2
    SN_CT16B1->PWMCTRL =    (mskCT16_PWM8MODE_2  \
                            |mskCT16_PWM9MODE_2  \
                            |mskCT16_PWM11MODE_2 \
                            |mskCT16_PWM12MODE_2 \
                            |mskCT16_PWM13MODE_2 \
                            |mskCT16_PWM14MODE_2 \
                            |mskCT16_PWM15MODE_2);
    SN_CT16B1->PWMCTRL2 =   (mskCT16_PWM16MODE_2 \
                            |mskCT16_PWM17MODE_2 \
                            |mskCT16_PWM18MODE_2 \
                            |mskCT16_PWM19MODE_2 \
                            |mskCT16_PWM20MODE_2 \
                            |mskCT16_PWM21MODE_2 \
                            |mskCT16_PWM22MODE_2 \
                            |mskCT16_PWM23MODE_2);

    // Set match interrupts and TC rest
    SN_CT16B1->MCTRL = (mskCT16_MR1IE_EN);
    SN_CT16B1->MCTRL_b.MR1RST = 1;

    // COL match register
    SN_CT16B1->MR1 = 0xFF;

    // Set prescale value
    SN_CT16B1->PRE = 0x24;

    //Set CT16B1 as the up-counting mode.
	SN_CT16B1->TMRCTRL = (mskCT16_CRST);

    // Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    NVIC_ClearPendingIRQ(CT16B1_IRQn);
    nvicEnableVector(CT16B1_IRQn, 4);
}

uint8_t matrix_scan(void) {
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            // Determine if the matrix changed state
            if ((last_matrix[row_index] != raw_matrix[row_index])) {
                matrix_changed         = true;
                last_matrix[row_index] = raw_matrix[row_index];
            }
        }
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return matrix_changed;
}

/**
 * @brief   MR1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(Vector80) {

    OSAL_IRQ_PROLOGUE();

    SN_CT16B1->IC = mskCT16_MR1IC; // Clear match interrupt status

    // Turn COL off
    setPinInput(col_pins[current_col]);
    writePinHigh(col_pins[current_col]);

    // Read the key matrix
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // setPinOutput(row_pins[row_index]);
        writePinLow(row_pins[row_index]);

        // Check row pin state
        if (readPin(col_pins[current_col]) == 0) {
            // Pin LO, set col bit
            raw_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            raw_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
        // setPinInput(row_pins[row_index]);
        writePinHigh(row_pins[row_index]);
    }

    current_col = (current_col + 1) % MATRIX_COLS;

    // Turn COL ON
    setPinOutput(col_pins[current_col]);
    writePinLow(col_pins[current_col]);

    SN_CT16B1->MR23 = led_state[(current_col) + 0].r;
    SN_CT16B1->MR8  = led_state[(current_col) + 0].b;
    SN_CT16B1->MR9  = led_state[(current_col) + 0].g;

    SN_CT16B1->MR11 = led_state[(current_col) + 1].r;
    SN_CT16B1->MR12 = led_state[(current_col) + 1].b;
    SN_CT16B1->MR13 = led_state[(current_col) + 1].g;

    SN_CT16B1->MR14 = led_state[(current_col) + 2].r;
    SN_CT16B1->MR15 = led_state[(current_col) + 2].b;
    SN_CT16B1->MR16 = led_state[(current_col) + 2].g;

    SN_CT16B1->MR17 = led_state[(current_col) + 3].r;
    SN_CT16B1->MR18 = led_state[(current_col) + 3].b;
    SN_CT16B1->MR19 = led_state[(current_col) + 3].g;

    SN_CT16B1->MR20 = led_state[(current_col) + 4].r;
    SN_CT16B1->MR21 = led_state[(current_col) + 4].b;
    SN_CT16B1->MR22 = led_state[(current_col) + 4].g;

    SN_CT16B1->IC = SN_CT16B1->RIS;  // Clear all for now

    OSAL_IRQ_EPILOGUE();
}
