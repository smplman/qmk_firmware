/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "hal.h"
#include "led_custom.h"
#include "keyboard.h"
#include "printf.h"

// static void breathing_callback(PWMDriver *pwmp);

// static PWMConfig pwmCFG = {
//   0xFFFF,                              /* PWM clock frequency  */
//   256,                              /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
//   NULL,                               /* No Callback */
//   {
//       {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 0 */
//       {PWM_OUTPUT_DISABLED, NULL},
//       {PWM_OUTPUT_DISABLED, NULL},
//       {PWM_OUTPUT_DISABLED, NULL}
//   },
//   0,                                  /* HW dependent part.*/
//   0
// };

// static PWMConfig pwmCFG_breathing = {
//   0xFFFF,                              /* 10kHz PWM clock frequency  */
//   256,                              /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
//   breathing_callback,                               /* Breathing Callback */
//   {
//       {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 0 */
//       {PWM_OUTPUT_DISABLED, NULL},
//       {PWM_OUTPUT_DISABLED, NULL},
//       {PWM_OUTPUT_DISABLED, NULL}
//   },
//   0,                                  /* HW dependent part.*/
//   0
// };
