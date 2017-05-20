/*
 * front-panel LED
 *
 * Copyright 2013--2015 Christian Schneider <software(at)chschneider(dot)eu>
 *
 * This file is part of the MOTion trap control unit firmware
 * (called "program" in the following).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation, *not* any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LED_H
#define LED_H 1

void led_init();
void led_on();
void led_off();
void led_toggle();
void led_blink(const unsigned int n_times);

#endif  // LED_H
