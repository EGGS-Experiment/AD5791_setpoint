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

#ifndef LED_C
#define LED_C 1

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

#define LED_PIN  PINB
#define LED_DDR  DDRB
#define LED_PORT PORTB

#define LED      PB7

void led_init() {
  LED_DDR |= _BV(LED);
}

void led_on() {
  LED_PORT |= _BV(LED);
}

void led_off() {
  LED_PORT &= ~(_BV(LED));
}

void led_toggle() {
  LED_PIN |= _BV(LED);
}

void led_blink(const unsigned int n_times) {
  for (unsigned int i = 0; i < n_times; i++) {
    led_on();
    _delay_ms(125);
    led_off();
    _delay_ms(125);
  }
}

#endif  // LED_C
