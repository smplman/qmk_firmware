/*
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
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
 *
 * Ported to QMK by Stephen Peery <https://github.com/smp4488/>
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

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// static const pin_t led_row_pins[MATRIX_ROWS][3] = LED_MATRIX_ROW_PINS;
// static const pin_t led_row_pins[LED_MATRIX_ROWS] = LED_MATRIX_ROW_PINS;

// LED COL pins are the same as the keyboard matrix

matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
matrix_row_t matrix[MATRIX_ROWS];      // debounced values

void matrix_scan_kb (void) {
}

// __attribute__((weak)) void matrix_init_kb (void)
// {
// matrix_init_user();
// }

// __attribute__((weak)) void matrix_scan_kb (void)
// {
// matrix_scan_user();
// }

// __attribute__((weak)) void matrix_init_user (void)
// {
// }

// __attribute__((weak)) void matrix_scan_user (void)
// {
// }

inline matrix_row_t matrix_get_row (uint8_t row) {
    return matrix[row];
}

void matrix_print (void) {
}

static void select_col (uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col (uint8_t col) {
    setPinInputHigh(col_pins[col]);
}

static void unselect_cols (void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++)
    {
        setPinInputHigh(col_pins[x]);
    }
}

static void init_pins (void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++)
    {
        setPinInputHigh(row_pins[x]);
    }
}

static bool read_rows_on_col (matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    uint32_t rows[MATRIX_ROWS];

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(3);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        rows[row_index] = readPin(row_pins[row_index]);
    }

    // Unselect col
    unselect_col(current_col);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (rows[row_index] == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    return matrix_changed;
}

void matrix_init (void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

static uint16_t debouncing_time;
uint8_t matrix_scan (void) {
    bool   changed         = false;
    static debouncing_time = 0;        // timer_read();

    if ((timer_elapsed(debouncing_time) > 5))
    {
        debouncing_time = timer_read();
        unselect_cols();

        // memset(raw_matrix, 0, sizeof(raw_matrix));

        // Set col, read rows
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++)
        {
            changed |= read_rows_on_col(raw_matrix, current_col);
        }

        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++)
        {
            select_col(current_col);
        }

        debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

        matrix_scan_quantum();
    }

    return (uint8_t) changed;
}
