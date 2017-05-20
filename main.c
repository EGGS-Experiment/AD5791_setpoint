/*
 * main program file
 *
 * Copyright 2013--2017 Christian Schneider <software(at)chschneider(dot)eu>
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

#include "config.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "serial_console.h"
#include "led.h"

int main(void) {
  // ////////////////////////////////////////////////////////////////////////
  // initialization
  // ////////////////////////////////////////////////////////////////////////

  // LED
  led_init();

  // initialize serial console and redirect printf(), getchar() etc. to it
  serial_console_init();  // enables interrupt!

  // ////////////////////////////////////////////////////////////////////////
  // boot indicator
  // ////////////////////////////////////////////////////////////////////////

  led_blink(3);
  led_on();

  // ////////////////////////////////////////////////////////////////////////
  // finally: turn on interrupts
  // ////////////////////////////////////////////////////////////////////////

  sei();

  // ////////////////////////////////////////////////////////////////////////
  // main program loop
  // ////////////////////////////////////////////////////////////////////////

  // give status message
  printf("Ready.\n");

  // echo
  char c;
  for (;;) {
    c = getchar();
    putchar(c);

    if (c == '1')
      led_on();
    if (c == '0')
      led_off();
  }

  return 0;
}
