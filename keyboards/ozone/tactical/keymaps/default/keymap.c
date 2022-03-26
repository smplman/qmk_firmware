/*
Copyright 2020 Dimitris Mantzouranis
Copyright 2022 Philip Mourdjis
Copyright 2022 Pablo Martinez Bernal

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

*/
// Pablo (elpekenin): This keymap mimics the default config from the vendor, it is HIGHLY recommended to add a RESET key somewhere for bootloader

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 // Default layer
 // Column:        0        1          2          3          4          5          6          7          8          9          10         11         12         13         14         
 [_QWERTY] =  { {  KC_ESC,  KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      ES_QUOT,   ES_IEXL,   KC_BSPC,   ES_MORD   },
                {  KC_TAB,  KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      ES_GRV,    ES_PLUS,   XXXXXXX,   KC_DEL    },
                {  KC_CAPS, KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      ES_NTIL,   ES_ACUT,   ES_CCED,   KC_ENT,    KG_PGUP   },
                {  KC_LSFT, ES_LABK,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      ES_COMM,   ES_DOT,    ES_MINS,   KC_RSFT,   KC_UP,     KC_PGDN   },
                {  KC_LCTL, KC_LGUI,   KC_LALT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_SPC,    XXXXXXX,   XXXXXXX,   KC_ALGR,   MO(_FN),   KC_RCTRL,  KC_LEFT,   KC_DOWN,   KC_RGHT   }
              },


 // _FN Settings 
 // Column:        0          1          2          3          4          5          6          7          8          9          10         11         12         13         14                 
 [_FN] =     { {   XXXXXXX,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    XXXXXXX,   KC_PSCR   },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX   },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   RGB_MOD,   XXXXXXX,   XXXXXXX   },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   RGB_HUI,   XXXXXXX,   XXXXXXX,   RGB_VAI,   XXXXXXX   },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_TRNS,   XXXXXXX,   RGB_SPD,   RGB_VAD,   RGB_SPI   }
              },
};


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //4 debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}
