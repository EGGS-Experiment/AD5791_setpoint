#ifndef AMOCORE_H
#define AMOCORE_H 1

#include <stdlib.h>
#include <math.h>
#include <string.h>

//AVR
#include <avr/eeprom.h>
#include <avr/interrupt.h>

//AMO7
#include "../amo7.h"

//SPI
#include "../spi_flex.h"

//////////////////////////////////////////////////////////////////////////////////////
//AMO6 - EXTENSIONS
//////////////////////////////////////////////////////////////////////////////////////
//Hardware
#define AMO6_EXT1_nEN           PG1
#define AMO6_EXT1_nEN_DDR       DDRG
#define AMO6_EXT1_nEN_PORT      PORTG

#define AMO6_EXT2_nEN		PG3
#define AMO6_EXT2_nEN_DDR   	DDRG
#define AMO6_EXT2_nEN_PORT  	PORTG

void amo6_ext_init();

//////////////////////////////////////////////////////////////////////////////////////
//AMO6 - SCREEN
//////////////////////////////////////////////////////////////////////////////////////
//Hardware
#define AMO6_CLEO_nPWR        PG0
#define AMO6_CLEO_nPWR_DDR    DDRG
#define AMO6_CLEO_nPWR_PORT    PORTG

int         screen_chnl_nmbr = 0;   //holds the currently selected channel
int         tag = 0;
static int  tag_old = 0;
int16_t     amo6_screen_x, amo6_screen_y;
int16_t     amo6_screen_current_dur;
int         amo6_screen_last_dur = 0;
int16_t     amo6_screen_current_tag;
bool        amo6_screen_short_press_detected = 0;

//Display
#define AMO1_SCREEN_WIDTH       480
#define AMO6_SCREEN_ROW3_Y      200

//Functions
void amo6_core_init();
void amo6_screen_init();
void amo6_screen_update();
void amo6_screen_draw();
void amo6_screen_processButtons();
void amo6_screen_shortPress(bool *press_detected);
void amo6_screen_processShortPress();

//////////////////////////////////////////////////////////////////////////////////////
//AMO6 - SERIAL
//////////////////////////////////////////////////////////////////////////////////////
#define amo6_serial_buffer_size     100

char amo6_serial_buffer[amo6_serial_buffer_size + 1];
char amo6_serial_string[amo6_serial_buffer_size + 1];

void amo6_serial_update();
void amo6_serial_parse();

//////////////////////////////////////////////////////////////////////////////////////
//AMO6 - BUTTONS
//////////////////////////////////////////////////////////////////////////////////////
//Buzzer
#define AMO6_BUZZER_nEN         PD7
#define AMO6_BUZZER_nEN_DDR     DDRD
#define AMO6_BUZZER_nEN_PORT    PORTD

//Latch
#define AMO6_HOLD_THRESHOLD     7

//Holder variables
static int8_t   amo6_encoder_val        = 0;
static bool     amo6_sw1_pushed         = false;
static bool     amo6_sw2_pushed         = false;
static bool     amo6_count_latch[2]     = {false, false};
uint8_t         amo6_hold_count[2]      = {0, 0}; //decrease hold_threshold for faster incrementing

//Functions
void amo6_buttons_init();
void amo6_buttons_update();

#endif //AMOCORE_H
