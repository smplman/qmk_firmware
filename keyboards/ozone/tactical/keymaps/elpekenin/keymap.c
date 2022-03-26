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

/* Pablo (elpekenin):
    In my custom keymap i've added extra features:
        a) 2 extra layers
            - Numpad + media control
            - RESET
        
        b) Changed PGUP/PGDN to VOLU/VOLD as I never use the first two
            - This keys are also used for layer moving
                * In default layer, Shift + VOLU moves to next layer
                * Anywhere else, those positions in the matrix acts as LAYER_UP and LAYER_DOWN
        
        c) Added MY_4, works as a regular 4 most of the time, but as F4 when Alt is pressed
            This allows using Alt+4 to close a window, rather than Alt+FN+4 (which also works)

        d) Added tap dances for typing "{", "[" and "(" from a single key; same with "}", "]" and ")"  
            * ERROR: Round brackets () are not working at the moment

        e) Changed Fn+º from PrintScreen to Alt+PrintScreen 
            Since I have a 2-monitor setup, PrintScreen captures both of them, by adding Alt it only captures the active window    

        f) Lightning
            - White LED under Caps Lock when it's enabled
            - Lights go off on RESET layer, except for red indicator on RESET button, and blue on LAYER_DOWN
*/

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _FN,
    _LAYER2,
    _LAYER3,
};

enum my_keycodes {
    MY_VOLU = SAFE_RANGE,
    MY_4
};

enum {
    TD_1, 
    TD_2
};

bool activate_rgb = false; // disable/re-enable LEDs in reset layer


void td_left_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!(get_mods() & MOD_BIT(KC_ALGR))) { // if AlGr is NOT pressed, just act us usual
        for (int i=0; i<(state->count); i++) { // send the key as many times as it was pressed
            tap_code16(ES_ACUT);           
        }
        return;
    }

    // if we made it here, AlGr is pressed
    // NOTE: it behaves weird if AlGr is released in the middle of the multi-tap 
    switch (state->count) {
        case 1:
            tap_code16(ES_ACUT); // {
            break;

        case 2: 
            tap_code16(ES_GRV); // [
            break;

        case 3:
            unregister_code16(KC_ALGR); // AlGr + Shift + 8 wouldn't work
            tap_code16(S(KC_8)); // (
            break;

        default: // +3 times -> nothing
            break;
    }
    return;
}

void td_left_reset(qk_tap_dance_state_t *state, void *user_data) {
    return;
}


void td_rght_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!(get_mods() & MOD_BIT(KC_ALGR))) { // if r-alt is NOT pressed, just act us usual
        unregister_code16(KC_ALGR); // trying to fix weird behaviour
        for (int i=0; i<(state->count); i++) { // send the key as many times as it was pressed
            tap_code16(ES_CCED);
        }
        return;
    }
    
    // if we made it here, AlGr is pressed
    // NOTE: it behaves weird if AlGr is released in the middle of the multi-tap 
    switch (state->count) {
        case 1:
            tap_code16(ES_CCED); // }
            break;

        case 2: 
            tap_code16(ES_PLUS); // ]
            break;
            
        case 3: 
            unregister_code16(KC_ALGR); // AlGr + Shift + 9 wouldn't work
            tap_code16(S(KC_9)); // )
            break;

        default: // +3 times -> nothing
            break;
    }
    return;
    
}

void td_rght_reset(qk_tap_dance_state_t *state, void *user_data) {
    return;
}


// All tap dance functions go here
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_finished, td_left_reset),
    [TD_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rght_finished, td_rght_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 // Default layer
 // Column:        0        1          2          3          4          5          6          7          8          9          10         11         12         13         14         
 [_QWERTY] =  { {  KC_ESC,  KC_1,      KC_2,      KC_3,      MY_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      ES_QUOT,   ES_IEXL,   KC_BSPC,   ES_MORD   },
                {  KC_TAB,  KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      ES_GRV,    ES_PLUS,   XXXXXXX,   KC_DEL    },
                {  KC_CAPS, KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      ES_NTIL,   TD(TD_1),  TD(TD_2),  KC_ENT,    MY_VOLU   },
                {  KC_LSFT, ES_LABK,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      ES_COMM,   ES_DOT,    ES_MINS,   KC_RSFT,   KC_UP,     KC_VOLD   },
                {  KC_LCTL, KC_LGUI,   KC_LALT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_SPC,    XXXXXXX,   XXXXXXX,   KC_ALGR,   MO(_FN),   KC_RCTRL,  KC_LEFT,   KC_DOWN,   KC_RGHT   }
              },


 // _FN Settings 
 // Column:        0          1          2          3          4          5          6          7          8          9          10         11         12         13         14                 
 [_FN] =     { {   XXXXXXX,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    XXXXXXX,   A(KC_PSCR)   },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX      },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   RGB_MOD,   XXXXXXX,   XXXXXXX      },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   RGB_HUI,   XXXXXXX,   XXXXXXX,   RGB_VAI,   XXXXXXX      },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_TRNS,   XXXXXXX,   RGB_SPD,   RGB_VAD,   RGB_SPI      }
              },


 // _LAYER2 Settings
 // Column:        0          1          2          3          4          5          6          7          8          9          10         11         12         13         14               
 [_LAYER2] = { {   XXXXXXX,   KC_MPRV,   KC_MNXT,   KC_MPLY,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   XXXXXXX       },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_PPLS,   KC_7,      KC_8,      KC_9,      KC_PMNS,   XXXXXXX,   XXXXXXX,   XXXXXXX,   _______       },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_PAST,   KC_4,      KC_5,      KC_6,      KC_PSLS,   XXXXXXX,   XXXXXXX,   _______,   TO(_LAYER3)   }, //jump to L3
               {   _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_1,      KC_2,      KC_3,      XXXXXXX,   XXXXXXX,   XXXXXXX,   _______,   TO(_QWERTY)   }, //back to L1
               {   _______,   _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_0,      XXXXXXX,   XXXXXXX,   ES_DOT,    XXXXXXX,   XXXXXXX,   _______,   _______,   _______       }
              },


 // _LAYER3 Settings
 // Column:        0          1          2          3          4          5          6          7          8          9          10         11         12         13         14                 
 [_LAYER3] = { {   RESET,     XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX       },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX       },
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX       }, 
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   TO(_LAYER2)   }, //back to L2
               {   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX       }
              },
};


bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {        
        case MY_VOLU:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)){  // left shift+vol_up => layer up
                    layer_on(_LAYER2);
                } else {
                    register_code(KC_VOLU);          // else just vol_up
                }
            } else {                                   
                unregister_code(KC_VOLU); 
            }
            return false;
            break;

        case MY_4:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_ALGR)){ // spanish combo for tilde (~) 
                    tap_code16(ES_TILD);
                    return false;
                }
                if (get_mods() & MOD_BIT(KC_LALT)){ // alt+4 => alt+f4
                    tap_code16(A(KC_F4));
                    return false;
                }                
                tap_code(KC_4);
            }
            return true;
            break;
    }
    return true;
}


void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
        RGB MY_WHITE = hsv_to_rgb((HSV){HSV_WHITE}); 
        rgb_matrix_set_color(29, MY_WHITE.r, MY_WHITE.g, MY_WHITE.b); // white indicator on caps lock
    }

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            break;
        
        case _LAYER2:
            // back to layer 2 from layer 3, turn light back on
            if (activate_rgb) {
                rgb_matrix_sethsv(HSV_RED);
                rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
                activate_rgb = false;
            }
            break;

        case _LAYER3:
            // in layer 3 turn off lighting
            activate_rgb = true;
            rgb_matrix_sethsv(HSV_OFF);
            rgb_matrix_set_color(0, RGB_RED); // reset 
            rgb_matrix_set_color(58, RGB_BLUE); // layer down
            break;
        
        default:
            break;
    }

}


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //4 debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}
