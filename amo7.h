#ifndef AMO7_H
#define AMO7_H 1
//todo: understand makefiles and get toolchain on mac & windows
//STD
#include <stdlib.h>
#include <math.h>
#include <string.h>

//AVR
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

//CleO
#include "CleO/CleO.hpp"


//////////////////////////////////////////////////////////////////////////////////////
// TRACKING
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "Highly-Stable DAC Setpoint";
const char device_id[]   = "AMO7";
const char hardware_id[] = "1.0.0";
const char firmware_id[] = "1.0.0";


//////////////////////////////////////////////////////////////////////////////////////
// SCREEN
//////////////////////////////////////////////////////////////////////////////////////
//Colors
#define MY_ORANGE   0xfa7626UL
#define MY_MAGENTA  0xff0086UL
#define MY_RED      0xff6666UL
#define MY_GREEN    0x89df87UL
#define MY_BLUE     0xadd8e6UL
#define MY_YELLOW   0xfffacdUL
#define MY_DARKBLUE 0x004166UL
#define MY_PINK     0xe9d3ebUL
#define MY_BLACK    0x000000UL
#define MY_GREY     0x949494UL
#define MY_WHITE    0xffffffUL
#define MY_PURPLE   0xb3b3ccUL
#define MY_REDRED   0xff0000UL

#define AMO7_TEXT_COLOR         0x000000UL
#define AMO7_SCREEN_TEXT_COLOR  0x000000UL  //MY_BLACK
#define AMO7_SCREEN_LINE_COLOR  0x004166UL  //MY_DARKBLUE
#define CLEO_SELECT		        0xADD8E6UL


//Screen Layout
#define AMO6_SCREEN_H		320
#define AMO6_SCREEN_W		480
#define AMO6_SCREEN_OFFSET  1

//Screen elements
#define AMO6_SCREEN_TAGS 4
bool amo6_screen_select[AMO6_SCREEN_TAGS];  // used to select screen elements

enum{       //Labels for screen tags
    amo6_screen_null_tag            , // 0
    voltage_output                  , // 1
    on_off_switch                   , // 2
    screen_bug                      , // 3
};


//////////////////////////////////////////////////////////////////////////////////////
// AMO7 - DAC
//////////////////////////////////////////////////////////////////////////////////////
//Hardware
#define AMO7_DRV_DAC_PORT   PORTA
#define AMO7_DRV_DAC_DDR    DDRA

#define AMO7_DAC_LOAD       PA4
#define AMO7_DAC_SYNC       PA5
#define AMO7_DAC_CLOCK      PA6
#define AMO7_DAC_INPUT      PA7
//#define AMO7_DAC_CLEAR      PA7

//Default Values
#define      AMO7_VOUT_MAX              5           //determined by reference board positive voltage
#define      AMO7_VOUT_MIN              0
#define      AMO7_CNTS_MAX              1048575     //20 bit precision
#define      AMO7_CNTS_MIN              0
#define      AMO7_CNTS_TO_VOUT          0.00000476837613        // 5V / (2^20 - 1)
#define      AMO7_VOUT_TO_CNTS          209715                  // (2^20 - 1) / 5V

//Variables
    //Stores the DAC power state
bool        amo7_DAC_state = false, amo7_DAC_state_old = false;
    //Stores the DAC voltage
uint32_t    amo7_DAC_cnts = 0, amo7_DAC_cnts_old = 0;


//Functions
    //Initializes all the relevant ports, registers, pins, and hardware
void amo7_init                   ();
    //updates the voltage to each motor via the dac
void amo7_set_dac     (const uint32_t cnts);
    //Updates the AD5791 settings
void amo7_hardware_update();


#endif // AMO7_H
