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
#include "ch.h"
#include "hal.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "led_matrix.h"

// set counter reset on MRn (setting MRn to the full period) and set the other MRs to the PWM duty cycle you want for that pin
// on period interrupt update all the PWM MRs to the values for the next LED
// the only issue is that when you do that, the timer has reset and may count during the ISR, so you'll have to detect low or 0 values and set the pin accordingly

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
// static const pin_t led_row_pins[MATRIX_ROWS][3] = LED_MATRIX_ROW_PINS;
// LED COL pins are the same as the keyboard matrix

static matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
static matrix_row_t matrix[MATRIX_ROWS]; //debounced values

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void select_col(uint8_t col) {
    setPinInput(col_pins[col]);
}

static void unselect_col(uint8_t col) {
    setPinOutput(col_pins[col]);
}

static void select_row(uint8_t row) {
    //Disable led row
    // led_row_pins[row][0]
    // SN_CT16B1->PWMIOENB = (0<<(led_row_pins[row][0] + 8));//Enable PWM19 IO
    // SN_CT16B1->PWMIOENB = (0<<(led_row_pins[row][1] + 8));//Enable PWM19 IO
    // SN_CT16B1->PWMIOENB = (0<<(led_row_pins[row][2] + 8));//Enable PWM19 IO
    // setPinOutput(row_pins[row]);
    // writePinLow(row_pins[row]);

    setPinOutput(row_pins[row]);
}

static void unselect_row(uint8_t row) {
    // setPinInputHigh(row_pins[row]);

    setPinInput(row_pins[row]);

    // enable led row
    // SN_CT16B1->PWMIOENB = (1<<(led_row_pins[row][0] + 8));//Enable PWM19 IO
    // SN_CT16B1->PWMIOENB = (1<<(led_row_pins[row][1] + 8));//Enable PWM19 IO
    // SN_CT16B1->PWMIOENB = (1<<(led_row_pins[row][2] + 8));//Enable PWM19 IO
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        // setPinInputHigh(row_pins[x]);

        setPinInput(row_pins[x]);
    }
}

static void init_pins(void) {

    setup_led_pwm();

    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        // setPinInputHigh(col_pins[x]);
        setPinOutput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    // wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

        // Set pin to input
        select_col(col_index);

        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Set pin to output
        unselect_col(col_index);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
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
}

uint8_t matrix_scan(void) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return (uint8_t)changed;
}
