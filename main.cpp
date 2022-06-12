/*
 * main program file
 *
 * Copyright 2013--2022
 *  Christian Schneider <software(at)chschneider(dot)eu>
 *  Peter Yu <ucla(dot)eshop(at)gmail(dot)com>
 *  Clayton Ho <claytonho(at)g(dot)ucla(dot)edu>
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

// ////////////////////////////////////////////////////////////////////////
// IMPORTS
// ////////////////////////////////////////////////////////////////////////

// AVR imports
#include "config.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Core Device imports
#include "serial_console.h"
#include "led.h"
#include "spi_flex.h"

// AMO Imports
#include "CleO/CleO.cpp"
#include "core/amo_core.hpp"
#include "amo7.hpp"


int main(void) {
    // ////////////////////////////////////////////////////////////////////////
    // initialization
    // ///////////////////////////////////////////////////////////////////////

    // LED
    led_init();

    // initialize serial console and redirect printf(), getchar() etc. to it
    serial_console_init();  // enables interrupt!

    // AMO Core
    amo6_ext_init();
    amo6_screen_init();
    amo6_buttons_init();

    // AMO7
    amo7_init();

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
    // give status message
    // ////////////////////////////////////////////////////////////////////////

    printf("%s\n", device_name);
    printf("Device ID : %s\n", device_id);
    printf("Hardware ID : %s\n", hardware_id);
    printf("Firmware ID : %s\n", firmware_id);
    printf("Device Ready\n");

    // ////////////////////////////////////////////////////////////////////////
    // main program loop
    // ////////////////////////////////////////////////////////////////////////

    uint16_t counter = 0;
    bool no_op=1;
    for (;;) {
        // update hardware every 50 loops
        if (counter % 50 == 0) {
            amo7_hardware_update();
            no_op = 0;
        }
        // update interface every 100 loops
        if (counter % 100 == 0) {
            amo6_buttons_update();
            amo6_screen_update();
            amo6_serial_update();
            no_op = 0;
        }
        // delay 1ms if nothing happened
        if (no_op) _delay_ms(1);
        else no_op=1;
        counter++;
    }
    return 0;
}
