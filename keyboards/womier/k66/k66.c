/* Copyright 2019 Stephen Peery
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

#include "k66.h"

/* clang-format off */
led_config_t g_led_config = { {
{ 0  , 1   , 2  , 3      , 4      , 5  , 6      , 7      , 8  , 9  , 10 , 11 , 12 , 13 } ,
{ 14 , 15  , 16 , 17     , 18     , 19 , 20     , 21     , 22 , 23 , 24 , 25 , 26 , 27 } ,
{ 28 , 29  , 30 , 31     , 32     , 33 , 34     , 35     , 36 , 37 , 38 , 39 , 40 , 41 } ,
{ 42 , 43  , 44 , 45     , 46     , 47 , 48     , 49     , 50 , 51 , 52 , 53 , 54 , 55 } ,
{ 56 , 57  , 58 , NO_LED , NO_LED , 59 , NO_LED , NO_LED , 60 , 61 , 62 , 63 , 64 , 65 }
}    , {
{0   , 0}  ,{16  , 0}  ,{31  , 0}  ,{48  , 0}  ,{64  , 0}  ,{80  , 0}  ,{96  , 0}  ,{112 , 0}  ,{128 , 0}  ,{144 , 0}  ,{159 , 0}  ,{176 , 0}  ,{191 , 0}  ,{215 , 0}  ,
{5   , 16} ,{24  , 16} ,{40  , 16} ,{57  , 16} ,{72  , 16} ,{89  , 16} ,{104 , 16} ,{120 , 16} ,{136 , 16} ,{152 , 16} ,{167 , 16} ,{183 , 16} ,{199 , 16} ,{218 , 16} ,
{9   , 32} ,{28  , 32} ,{46  , 32} ,{61  , 32} ,{76  , 32} ,{93  , 32} ,{109 , 32} ,{124 , 32} ,{139 , 32} ,{155 , 32} ,{172 , 32} ,{187 , 32} ,{213 , 32} ,{241 , 0 } ,
{12  , 48} ,{37  , 48} ,{53  , 48} ,{68  , 48} ,{84  , 48} ,{100 , 48} ,{117 , 48} ,{132 , 48} ,{148 , 48} ,{163 , 48} ,{179 , 48} ,{202 , 48} ,{226 , 48} ,{241 , 16} ,
{3   , 64} ,{22  , 64} ,{38  , 64} ,                        {98  , 64} ,                        {157 , 64} ,{175 , 64} ,{193 , 64} ,{210 , 64} ,{226 , 64} ,{241 , 64} ,
}, {

    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 4, 1, 1, 1
} };

/* clang-format on */

void matrix_init_kb(void) {
    // matrix_init_user();
}
