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

#include "serial_console.h"
#include "led.h"
#include "spi_flex.h"

#include "CleO.hpp"
#include "ad5541.hpp"
#include "ad5544.hpp"
#include "ad5621.hpp"
#include "ad5290.hpp"
#include "max11100.hpp"
#include "ad7921.hpp"
#include "amo3.hpp"


int main(void) {
    // ////////////////////////////////////////////////////////////////////////
    // initialization
    // ////////////////////////////////////////////////////////////////////////
    
    // LED
    led_init();
    
    // initialize serial console and redirect printf(), getchar() etc. to it
    serial_console_init();  // enables interrupt!
    
    // AMO3
    amo3_init();
    
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
    printf("%s\n", device_name);
    printf("Device ID : %s\n", device_id);
    printf("Hardware ID : %s\n", hardware_id);
    printf("Firmware ID : %s\n", firmware_id);
    printf("Device Ready\n");
    
    uint16_t counter=0;
    /*uint8_t  motor_counter = 0;
    uint8_t  microstep_counter = 0;*/
    bool no_op=1;
    for (;;) {
        /*if (counter%3==0) {
            if (step_queue[0] != 0){
                if (new_motor){
                    move_config();
                }
                if (new_ms){
                    motor_config();
                }
                if (need_to_step){
                    move_motor(step_queue[motor_counter], 1);
                    move_array[step_queue[motor_counter]][microstep_counter] -= 1;
                }
                if (end_of_motor){
                    forward_step_queue();
                }
            }
        }*/
        if (counter%90==0) {
            amo3_fault_check();
            no_op=0;
        }
        if (counter%100==0) {
            amo6_buttons_update();
            amo6_serial_update();
            amo6_screen_update();
            no_op=0;
        }
        if (counter%250==0) {
            amo3_hardware_update();
            no_op=0;
        }
        if (no_op) _delay_ms(1);
        else no_op=1;
        counter++;
    }
    
    return 0;
}
