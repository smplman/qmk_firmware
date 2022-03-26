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

// Matrix based on Keychron K6, and modified to fit the layout

#include "tactical.h"

// readability
#define NA NO_LED

__attribute__ ((weak))
led_config_t g_led_config = { {
{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
{ 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NA, 28 },
{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 },
{ 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 },
{ 59, 60, 61, NA, NA, NA, 62, NA, NA, 63, 64, 65, 66, 67, 68 }
}, {                                                                                                                                              
    {0  ,  0}, {15 ,  0}, {30 ,  0}, {45 ,  0}, {60 ,  0}, {75 ,  0}, {90 ,  0}, {105 ,  0}, {120,  0}, {135,  0}, {150,  0}, {165,  0}, {180,  0}, {202,  0}, {224,  0},
    {2  , 16}, {17 , 16}, {32 , 16}, {47 , 16}, {62 , 16}, {77 , 16}, {92 , 16}, {107 , 16}, {122, 16}, {137, 16}, {152, 16}, {167, 16}, {182, 16},            {224, 16},
    {3  , 32}, {18 , 32}, {33 , 32}, {48 , 32}, {63 , 32}, {78 , 32}, {93 , 32}, {108 , 32}, {123, 32}, {138, 32}, {153, 32}, {168, 32}, {183, 32}, {203, 32}, {224, 32},
    {1  , 48}, {16 , 48}, {31 , 48}, {46 , 48}, {61 , 48}, {76 , 48}, {91 , 48}, {106 , 48}, {121, 48}, {136, 48}, {151, 48}, {166, 48}, {187, 48}, {209, 48}, {224, 48},
    {1  , 64}, {20 , 64}, {40 , 64},                                  {90 , 64},                        {149, 64}, {164, 64}, {179, 64}, {194, 64}, {209, 64}, {224, 64},
}, {
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4,          4,       4, 4, 4, 4, 4, 4
} };