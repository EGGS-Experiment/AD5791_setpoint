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
#include <util/delay.h>

//#include "serial_console.h"
#include "led.h"
#include "spi_flex.h"

#include "CleO.hpp"
#include "ad5541.hpp"
#include "ad5621.hpp"
#include "ad5290.hpp"
#include "max11100.hpp"
#include "amo2.hpp"

int main(void) {
  // ////////////////////////////////////////////////////////////////////////
  // initialization
  // ////////////////////////////////////////////////////////////////////////
  
  // LED
  led_init();

  // initialize serial console and redirect printf(), getchar() etc. to it
  serial_console_init();  // enables interrupt!
  
  // AMO2
  amo2_init();

  // ////////////////////////////////////////////////////////////////////////
  // boot indicator
  // ////////////////////////////////////////////////////////////////////////

  led_blink(3);
  led_on();

  // ////////////////////////////////////////////////////////////////////////
  // finally: turn on interrupts
  // ////////////////////////////////////////////////////////////////////////

//  sei();

  // ////////////////////////////////////////////////////////////////////////
  // main program loop
  // ////////////////////////////////////////////////////////////////////////

  // give status message
  printf("Ready\n");
  
  // echo
  //char c;
  
  // serial
  //char string[33];
  //int readcnt=0;
  
  uint16_t counter=0;
  bool no_op=1;
  for (;;) {
    /*
    c = getchar();
    putchar(c);

    if (c == '1') {
      amo1_setVDD1cnts(0);
      led_blink(1);
    }
    if (c == '2') {
      amo1_setVDD1cnts(amo1_vdd1_cnts);
      led_blink(2);
    }
    if (c == '3') {
      amo1_setVDD1cnts(47850);
      led_blink(3);
    }
    */
    
    if (counter%100==0) {
      //amo1_readIOUTmA();
      //amo1_readVOUTmV();
//      amo1_adjVDD1();
//      amo1_processFault();
      no_op=0;
    }
    if (counter%100==0) {
//      amo1_setOUT();
      no_op=0;
    }
    if (counter%50==0) {
      amo2_screen_refresh();
      no_op=0;
    }
    
    if (no_op) _delay_ms(1);
    else       no_op=1;
    counter++;
  }

  return 0;
}
