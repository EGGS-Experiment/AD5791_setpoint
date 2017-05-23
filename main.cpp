/*
 * main program file
 *
 * Copyright 2013--2017 
 *  Christian Schneider <software(at)chschneider(dot)eu>
 *  Peter Yu <ucla(dot)eshop(at)gmail(dot)com>
 *
 * This file is part of the AMO control unit firmware
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
#include "spi_flex.h"

#include "CleO.hpp"
#include "screen.hpp"

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
  //spi_flex_init(0);
  
  CleO.begin();
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.SetBackgroundcolor(0xe9d3ebUL);
  CleO.Show();
 
  CleO.DisplayRotate(2, 0);
  CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
  
  int counter=0;
  
  updateScreen();

  // echo
  //char c;
  //spi_flex_init(0);
  for (;;) {
    /*
    c = getchar();
    putchar(c);

    if (c == '1') {
      led_on();
    }
    if (c == '0') {
      led_off();
      printf("Version %u\n", CleO.Version());
    }*/
    if (counter%10==0) {
      updateScreen();
      printf("counter=%u\n", counter);
      printf("Version %d\n", CleO.Version());
      printf("ID %d\n", CleO.ModuleIdentifier());
      CleO.Noop();
      printf("Echo %d\n", CleO.Echo());
      //printf("Read 0x%x\n", spi_flex_read_byte(0));
      //printf("Echo 0x%x\n", spi_flex_read_write_lbyte(0, 0x8e));
    }
    counter++;
    //printf("counter=%u\n", counter);
  }

  return 0;
}
