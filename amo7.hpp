#ifndef AMO3_H
#define AMO3_H 1

#include <stdlib.h>
#include <math.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////
// Tracking
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "Stepper Motor Controller";
const char device_id[]   = "AMO7";
const char hardware_id[] = "1.0.0";
const char firmware_id[] = "1.0.0";

//////////////////////////////////////////////////////////////////////////////////////
// Declaration
//////////////////////////////////////////////////////////////////////////////////////
#define AMO6_EXT1_nEN		PG1
#define AMO6_EXT1_nEN_DDR   	DDRG
#define AMO6_EXT1_nEN_PORT  	PORTG

#define AMO6_EXT2_nEN		PG3
#define AMO6_EXT2_nEN_DDR   	DDRG
#define AMO6_EXT2_nEN_PORT  	PORTG

#define AMO6_BUZZER_nEN		PD7
#define AMO6_BUZZER_nEN_DDR   	DDRD
#define AMO6_BUZZER_nEN_PORT  	PORTD

#define AMO3_PWR_nOK		PH2
#define AMO3_PWR_nOK_PIN   	PINH
#define AMO3_PWR_nOK_DDR   	DDRH
#define AMO3_PWR_nOK_PORT  	PORTH

#define AMO7_DRV_CLEAR      PA0
#define AMO7_DRV_CLOCK      PA1
#define AMO7_DRV_LOAD       PA2
#define AMO7_DRV_INPUT      PA3    

#define AMO7_DAC_LOAD       PA4
#define AMO7_DAC_CLOCK      PA5
#define AMO7_DAC_INPUT      PA6
#define AMO7_DAC_CLEAR      PA7

//  AMO3
bool    debugging_power         = false;
bool    amo3_pwr_state          = true;
bool    amo3_pwr_state_latched  = true;  

enum {
    amo3_fault_none	, //0
    amo3_fault_pwr	, //1
};
uint8_t  amo3_fault       = amo3_fault_none;
uint8_t  amo3_fault_prev  = amo3_fault_none;
uint8_t   amo3_save_flag  = 0;

void  amo7_init             ();

//  Buttons (AMO6)
static int8_t  amo6_encoder_val       = 0;
static bool    amo6_sw1_pushed        = false;
static bool    amo6_sw2_pushed        = false;
static bool    amo6_count_latch  [2]  = {false, false};
uint8_t        amo6_hold_count  [2]   = {0, 0};
const uint8_t  amo6_hold_threshold    = 7;  //decrease hold_threshold for faster incrementing

void  amo6_buttons_init    ();
void  amo6_buttons_update  ();

//  Serial (AMO6)
const int  amo6_serial_buffer_size  = 100;
char       amo6_serial_buffer  [amo6_serial_buffer_size+1];
char       amo6_serial_string  [amo6_serial_buffer_size+1];

void  amo6_serial_update  ();
void  amo6_serial_parse   ();

//  Screen (AMO6)
#define AMO6_CLEO_nPWR		PG0
#define AMO6_CLEO_nPWR_DDR	DDRG
#define AMO6_CLEO_nPWR_PORT	PORTG

#define AMO6_SCREEN_H		320
#define AMO6_SCREEN_W		480

#define MY_ORANGE   0xfa7626UL
#define MY_MAGENTA  0xff0086UL
#define MY_RED      0xff6666UL
#define MY_GREEN    0x89df87UL
#define MY_BLUE     0xadd8e6UL
#define MY_YELLOW   0xfffacdUL
#define MY_DARKBLUE 0x004166UL
#define MY_PINK     0xe9d3ebUL
#define MY_BLACK    0x000000UL
#define MY_WHITE    0xffffffUL
#define MY_PURPLE   0xb3b3ccUL
#define MY_REDRED   0xff0000UL
#define CLEO_SELECT		0xADD8E6UL
#define CLEO_TEC_ON		0x98FB98UL
#define CLEO_TEC_OFF		0xFF7256UL
uint32_t amo6_screen_text_color = MY_BLACK;
uint32_t amo6_screen_line_color = MY_DARKBLUE;

enum {
    amo6_screen_null_tag         , // 0
    moving_voltge_output         , // 1
    coarse_display               , // 2
    step_counter                 , // 3
    on_off_switch                , // 4
    calibrate_button             , // 5
    move_button                  , // 6
    holding_voltage_output       , // 7
    fine_step_adjustment         , // 8
    stepper_motor_counter        , // 9
    screen_bug                   , // 10
};
#define AMO6_SCREEN_TAGS 11	
bool amo6_screen_select[AMO6_SCREEN_TAGS];

int16_t  amo6_screen_x  , amo6_screen_y  ;
int16_t  amo6_screen_current_dur  ;
int      amo6_screen_last_dur              = 0;
int16_t  amo6_screen_current_tag  ;
bool     amo6_screen_short_press_detected  = 0;

void  amo6_screen_debug              ();
void  amo6_screen_init               ();
void  amo6_screen_update             ();
void  amo6_screen_draw               ();
void  amo6_screen_touch              ();
void  amo6_screen_processButtons     ();
void  amo6_screen_shortPress         (bool *press_detected);
void  amo6_screen_processShortPress  ();

//Stepper Motors (AMO7)
        //Global constants
int          amo7_max_stepper_motor_number   = 11;
int          amo7_max_microstep_number       = 3;
int          amo7_max_steps                  = 2000;
int          amo7_max_V                      = 255;
float        amo7_step_size[12]              = {1.8,1.8,1.8,1.8,1.8,1.8,1.8,1.8,1.8,1.8,1.8,1.8};  //Only used to display total steps
int          amo7_base_delay                 = 3000;//in us, measures main loop step interval
int          amo7_min_step_width             = 500; //also in us
        //Individual motor variables
int          amo7_microstep_number           = 0;    //Tracks microstepping config
int          amo7_stepper_motor_number       = 0;    //Tracks active stepper motor
int          amo7_step_array[12][4]           ;      //Holds total steps
int          amo7_move_array[12][4]           ;      //Holds steps to move
int          amo7_moving_voltage[12]         = {0,0,0,0,0,0,0,0,0,0,0,0};
int          amo7_holding_voltage[12]        = {0,0,0,0,0,0,0,0,0,0,0,0};
int          amo7_pfd_voltage[12]            = {0,0,0,0,0,0,0,0,0,0,0,0};
bool         amo7_stepper_enable [12]        = {0,0,0,0,0,0,0,0,0,0,0,0};
long         amo7_speed_delay[12]            = {2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000};
        //Background stepping functionality
bool         amo7_dir_arr[4]                 = {0,0,0,0};
int          amo7_step_queue[12]             ;       //Queues motors to run in background
int          amo7_queue_index                = 0;    //Tracks how many motors are queued up
bool         amo7_new_microstep              = 1;
bool         amo7_new_motor                  = 0;
int          amo7_queued_microstep_counter   = 0;    //Tracks background microstepping
bool         amo7_move_enable[12]            = {1,1,1,1,1,1,1,1,1,1,1,1};

void amo7_dac_init               ();
void amo7_stepper_dac_update     (int motor_num, int mode);
void amo7_board_config           (int motor_num);
void amo7_motor_config           (int motor_num, bool dir, int msn);
void amo7_move_config            ();
void amo7_move_motor             (int motor_num, int steps, int delaytime);

//////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// AMO3 (edited for AMO7)
void amo7_init ()
{
    // hardware i/o config
    AMO6_CLEO_nPWR_DDR  |=  _BV(AMO6_CLEO_nPWR);//output
    AMO6_CLEO_nPWR_PORT |=  _BV(AMO6_CLEO_nPWR); //1
    
    AMO3_PWR_nOK_DDR  &= ~_BV(AMO3_PWR_nOK); //input
    AMO3_PWR_nOK_PORT &= ~_BV(AMO3_PWR_nOK); //disable pullup
    
    AMO6_EXT1_nEN_DDR  |=  _BV(AMO6_EXT1_nEN); //output
    AMO6_EXT1_nEN_PORT &= ~_BV(AMO6_EXT1_nEN); //0
    AMO6_EXT2_nEN_DDR  |=  _BV(AMO6_EXT2_nEN); //output
    AMO6_EXT2_nEN_PORT &= ~_BV(AMO6_EXT2_nEN); //0
    AMO6_BUZZER_nEN_DDR  |=  _BV(AMO6_BUZZER_nEN); //output
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
    
    //motors init (AMO7)
    DDRA = 0xff; //PORTA is shift register & DAC
    DDRJ = 0xf0; //J4-J7 are motor step output
    DDRC = 0x0f; //C0-C3 enable digital isolators, C4-C7 are motor feedback
    PORTA = 0x91;//set A0 (drv_clear), A4 (dac_load), A7 (dac_clear) high
    PORTC = 0x00;
    
    // hardware init
    amo6_screen_init();
    amo6_buttons_init();
    _delay_ms(100);   //just in case, to prevent "power-on reset glitch"
    amo7_dac_init(); //AMO7
    amo7_board_config(amo7_stepper_motor_number); //start at board 0, motor 0
    _delay_ms(100);    
}

// Buttons (AMO6)
void amo6_buttons_init ()
{
    // ENC_A
    DDRD   &= ~_BV(PD2);   //input
    PORTD  |=  _BV(PD2);   //enable pullup
    EICRA  &= ~_BV(ISC21); //enable any edge interrupt
    EICRA  |=  _BV(ISC20); //enable any edge interrupt
    EIMSK  |=  _BV(INT2);  //enable interrupt
    
    // ENC_B
    DDRD   &= ~_BV(PD1);   //input
    PORTD  |=  _BV(PD1);   //enable pullup
    EICRA  &= ~_BV(ISC11); //enable any edge interrupt
    EICRA  |=  _BV(ISC10); //enable any edge interrupt
    EIMSK  |=  _BV(INT1);  //enable interrupt for the pin
    
    // ENC_SW
    DDRD   &= ~_BV(PD3);   //input
    PORTD  |=  _BV(PD3);   //enable pullup
    EICRA  |=  _BV(ISC31); //enable falling edge interrupt
    EICRA  &= ~_BV(ISC30); //enable falling edge interrupt
    EIMSK  |=  _BV(INT3);  //enable interrupt for the pin
    
    // SW1
    DDRB   &= ~_BV(PB6);   //input
    PORTB  |=  _BV(PB6);   //enable pullup
    PCICR  |=  _BV(PCIE0); //enable pin change interrupt enable 0
    PCMSK0 |=  _BV(PCINT6);//enable interrupt for the pin
    
    // SW2
    DDRB   &= ~_BV(PB5);   //input
    PORTB  |=  _BV(PB5);   //enable pullup
    PCICR  |=  _BV(PCIE0); //enable pin change interrupt enable 0
    PCMSK0 |=  _BV(PCINT5);//enable interrupt for the pin
    
}

ISR(INT2_vect, ISR_ALIASOF(INT5_vect)); //map ENC_A to unused INT5
ISR(INT1_vect, ISR_ALIASOF(INT5_vect)); //map ENC_B to unused INT5
ISR(INT5_vect) //ENC_TURN
{
    static uint8_t old_AB = 0;  //lookup table index  
    static const int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table
    
    old_AB <<= 2;  //store previous state
    old_AB |= (  ( (((PIND>>PD2)&0x01)<<1) | ((PIND>>PD1)&0x01) )  &  0x03  ); //add current state
    amo6_encoder_val += enc_states[( old_AB & 0x0f )];
}

ISR(INT3_vect) //ENC_SW
{
}

ISR(PCINT0_vect) //SW1 SW2
{
    static bool sw1_old = true;
    static bool sw2_old = true;
    
    bool sw1_now = (PINB>>PB6) & 0x01;
    if (sw1_old && !sw1_now) {
        amo6_sw1_pushed = true;
    }
    sw1_old = sw1_now;
    
    bool sw2_now = (PINB>>PB5) & 0x01;
    if (sw2_old && !sw2_now) {
        amo6_sw2_pushed = true;
    }
    sw2_old = sw2_now;
}

void amo6_buttons_update () {
    static int tag_old = 0;
    int tag;
    float tmp;
    bool sw1_now = (PINB>>PB6) & 0x01;
    bool sw2_now = (PINB>>PB5) & 0x01;
    if (!amo3_pwr_state)
        return;
    
    for (tag=0;tag<AMO6_SCREEN_TAGS-1;tag++) { //find active screen tag
        if (amo6_screen_select[tag]==1) break;
    };
    
    // (+) both buttons are pressed
    if (amo6_sw1_pushed && amo6_sw2_pushed){
        switch (tag) {
            // do not do anything if something is selected
            case moving_voltge_output 	:
            case holding_voltage_output     :
            case coarse_display	            :
            case step_counter             	:
            case fine_step_adjustment         :
            case stepper_motor_counter        :
                break;
                // save the state if nothing is selected
            default :
                //display save flag for 4 loops/iterations
                amo3_save_flag = 4;
                // BEEP
                AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                _delay_ms(60);
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
                // save to EEPROM
        }
        // reset long-press variables
        amo6_count_latch[1] = false;
        amo6_hold_count[1] = 0;
        amo6_count_latch[0] = false;
        amo6_hold_count[0] = 0;
        // set buttons to not pressed
        amo6_sw1_pushed = false;
        amo6_sw2_pushed = false;
        return;
    }
    
    // sw1 pressed (red)
    if (amo6_sw1_pushed) {
        // (+) only update if other button is not pressed
        if (!amo6_count_latch[1]){
            amo6_count_latch[0] = true; // start counting hold time
            if (!sw1_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
                switch (tag) {
                    case moving_voltge_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_moving_voltage[amo7_stepper_motor_number] - 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_moving_voltage[amo7_stepper_motor_number] = tmp;
                        break;
                    case holding_voltage_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_holding_voltage[amo7_stepper_motor_number] - 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_holding_voltage[amo7_stepper_motor_number] = tmp;
                        amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                        break;
                    case coarse_display	:
                        break;
                    case step_counter	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] - 1;
                        if (tmp>amo7_max_steps) tmp=amo7_max_steps;
                        if (tmp<(amo7_max_steps*-1)) tmp=(amo7_max_steps*-1);
                        amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] = tmp;
                        break;
                    case stepper_motor_counter         :
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_stepper_motor_number - 1;
                        if (tmp>amo7_max_stepper_motor_number) tmp=0;
                        if (tmp<0) tmp=amo7_max_stepper_motor_number;
                        amo7_stepper_motor_number = tmp;
                        break;
                    case fine_step_adjustment         :
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_microstep_number - 1;
                        if (tmp>amo7_max_microstep_number) tmp=0;
                        if (tmp<0) tmp=amo7_max_microstep_number;
                        amo7_microstep_number = tmp;
                        break;
                }
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            }
        }
        else{
            // (+) reset long-press variables
            amo6_count_latch[1] = false;
            amo6_hold_count[1] = 0;
        }
        amo6_sw1_pushed = false;
    }
    
    // sw2 pressed (black)
    if (amo6_sw2_pushed) {
        // (+) only update if other button is not pressed
        if (!amo6_count_latch[0]){
            amo6_count_latch[1] = true; // start counting hold time
            if (!sw2_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
                switch (tag) {
                    case moving_voltge_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_moving_voltage[amo7_stepper_motor_number] + 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_moving_voltage[amo7_stepper_motor_number] = tmp;
                        break;
                    case holding_voltage_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_holding_voltage[amo7_stepper_motor_number] + 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_holding_voltage[amo7_stepper_motor_number] = tmp;
                        amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                        break;
                    case coarse_display	:
                        break;
                    case step_counter	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] + 1;
                        if (tmp>amo7_max_steps) tmp=amo7_max_steps;
                        if (tmp<(amo7_max_steps*-1)) tmp=(amo7_max_steps*-1);
                        amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] = tmp;
                        break;
                    case stepper_motor_counter         :
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_stepper_motor_number + 1;
                        if (tmp>amo7_max_stepper_motor_number) tmp=0;
                        if (tmp<0) tmp=amo7_max_stepper_motor_number;
                        amo7_stepper_motor_number = tmp;
                        break;
                    case fine_step_adjustment         :
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_microstep_number + 1;
                        if (tmp>amo7_max_microstep_number) tmp=0;
                        if (tmp<0) tmp=amo7_max_microstep_number;
                        amo7_microstep_number = tmp;
                        break;
                }
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            }
        }
        else{
            // (+) reset long-press variables
            amo6_count_latch[0] = false;
            amo6_hold_count[0] = 0;
        }
        amo6_sw2_pushed = false;
    }
    
    // (+) sw2 held (black)
    if (amo6_count_latch[1]){
        // increment hold_counter
        if (amo6_hold_count[1] < amo6_hold_threshold)
            ++(amo6_hold_count[1]);
        // update values
        if (amo6_hold_count[1] >= amo6_hold_threshold){
            switch (tag) {
                case moving_voltge_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_moving_voltage[amo7_stepper_motor_number] + 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_moving_voltage[amo7_stepper_motor_number] = tmp;
                    break;
                case holding_voltage_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_holding_voltage[amo7_stepper_motor_number] + 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_holding_voltage[amo7_stepper_motor_number] = tmp;
                    amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                    break;
                case coarse_display	:
                    break;
                case step_counter               	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] + 10;
                    if (tmp>amo7_max_steps) tmp=amo7_max_steps;
                    if (tmp<(amo7_max_steps*-1)) tmp=(amo7_max_steps*-1);
                    amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] = tmp;
                    break;
                case stepper_motor_counter       	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_stepper_motor_number + 2;
                    if (tmp>amo7_max_stepper_motor_number) tmp=0;
                    if (tmp<0) tmp=amo7_max_stepper_motor_number;
                    amo7_stepper_motor_number = tmp;
                    break;
                case fine_step_adjustment         :
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_microstep_number + 1;
                    if (tmp>amo7_max_microstep_number) tmp=0;
                    if (tmp<0) tmp=amo7_max_microstep_number;
                    amo7_microstep_number = tmp;
                    break;
            }
            AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            amo6_hold_count[1] = 0;
        }
        if (sw2_now){
            // reset long-press variables
            amo6_count_latch[1] = false;
            amo6_hold_count[1] = 0;
        }
    }
    // (+) sw1 held (red)
    if (amo6_count_latch[0]){
        // increment hold_counter
        if (amo6_hold_count[0] < amo6_hold_threshold)
            ++(amo6_hold_count[0]);
        // update values
        if (amo6_hold_count[0] >= amo6_hold_threshold){
            switch (tag) {
                case moving_voltge_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_moving_voltage[amo7_stepper_motor_number] - 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_moving_voltage[amo7_stepper_motor_number] = tmp;
                    break;
                case holding_voltage_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_holding_voltage[amo7_stepper_motor_number] - 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_holding_voltage[amo7_stepper_motor_number] = tmp;
                    amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                    break;
                case coarse_display	:
                    break;
                case step_counter	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] - 10;
                    if (tmp>amo7_max_steps) tmp=amo7_max_steps;
                    if (tmp<(amo7_max_steps*-1)) tmp=(amo7_max_steps*-1);
                    amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] = tmp;
                    break;
                case stepper_motor_counter       	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_stepper_motor_number - 2;
                    if (tmp>amo7_max_stepper_motor_number) tmp=0;
                    if (tmp<0) tmp=amo7_max_stepper_motor_number;
                    amo7_stepper_motor_number = tmp;
                    break;
                case fine_step_adjustment         :
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_microstep_number - 1;
                    if (tmp>amo7_max_microstep_number) tmp=0;
                    if (tmp<0) tmp=amo7_max_microstep_number;
                    amo7_microstep_number = tmp;
                    break;
            }
            AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            amo6_hold_count[0] = 0;
        }
        if (sw1_now){
            // reset long-press variables
            amo6_count_latch[0] = false;
            amo6_hold_count[0] = 0;
        }
    }
    
    // encoder turn
    static int8_t amo6_encoder_val_prev;
    if ((amo6_encoder_val_prev == amo6_encoder_val) || (tag != tag_old)) {
        //if (tag != tag_old) {
        amo6_encoder_val_prev = 0;
        amo6_encoder_val = 0;
    }
    else {
        int8_t val = amo6_encoder_val - amo6_encoder_val_prev;
        //int8_t val = amo6_encoder_val;
        switch (tag) {
            case moving_voltge_output	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_moving_voltage[amo7_stepper_motor_number] + val/200.0;
                if (tmp>amo7_max_V) tmp=amo7_max_V;
                if (tmp<0) tmp=0;
                amo7_moving_voltage[amo7_stepper_motor_number] = tmp;
                break;
            case holding_voltage_output	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_holding_voltage[amo7_stepper_motor_number] + val/200.0;
                if (tmp>amo7_max_V) tmp=amo7_max_V;
                if (tmp<0) tmp=0;
                amo7_holding_voltage[amo7_stepper_motor_number] = tmp;
                amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                break;
            case coarse_display	:
                break;
            case step_counter	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] + val/200.0;
                if (tmp>amo7_max_steps) tmp=amo7_max_steps;
                if (tmp<(amo7_max_steps*-1)) tmp=(amo7_max_steps*-1);
                amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] = tmp;
                break;
            case stepper_motor_counter    	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_stepper_motor_number + val/200.0;
                if (tmp>amo7_max_stepper_motor_number) tmp=0;
                if (tmp<0) tmp=amo7_max_stepper_motor_number;
                amo7_stepper_motor_number = tmp;
                break;
            case fine_step_adjustment       	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_microstep_number + val/200.0;
                if (tmp>amo7_max_microstep_number) tmp=0;
                if (tmp<0) tmp=amo7_max_microstep_number;
                amo7_microstep_number = tmp;
                break;
        }
        if ((val<=-1)||(val>=1)) {
            amo6_encoder_val_prev = 0;
            amo6_encoder_val = 0;
        }
        else {
        }
        AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
    }
    
    tag_old = tag;
}

// Serial (AMO6) (edited for AMO7)
void amo6_serial_update () {
    char getchar;
    static int i=0;
    static int j_prev=0;
    while (1) {
        getchar = uart_trygetchar();
        if(getchar == 0) {
            break;
        }
        else if(getchar=='\r'||getchar=='\n') {
            if(i>0) {
                int j=0;
                while(j<i) {
                    amo6_serial_string[j] = amo6_serial_buffer[j];
                    amo6_serial_buffer[j] = 0;
                    j++;
                }
                while(j<j_prev) {
                    amo6_serial_string[j] = 0;
                    j++;
                }
                j_prev = i;
                i = 0;
                amo6_serial_parse();
            }
        }
        else {
            if(i>=amo6_serial_buffer_size) {
                while(i>0) {
                    amo6_serial_buffer[i]=0;
                    i--;
                }
                amo6_serial_buffer[i]=0;
            }
            amo6_serial_buffer[i] = getchar;
            i++;
        }
    }
}

void amo6_serial_parse ()
{
    char delimiters[] = " ";
    char *token[8];
    int i=1;
    token[0] = strtok(amo6_serial_string, delimiters);
    while(i<8) {
        token[i] = strtok(NULL, delimiters);
        if(token[i] == NULL) break;
        i++;
    }
    if(strcmp(token[0],"vout.w")==0 && i == 4) {      //write moving voltage
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);
        double tmp = atof(token[3]);
        if (channel <= 12 && channel >=1){
            if (tmp >= 4.08) tmp = 4.08;
            if (tmp < 0) tmp = 0;
            tmp *= 256/4.096;
            if (strcmp(token[2], "m")||strcmp(token[2], "M")){
                amo7_moving_voltage[channel-1] = (int) tmp;
                double voltage_output = amo7_moving_voltage[channel-1]*4.096/256;
                printf("voutm.w : set motor #%d to moving at %1.3fV\n", channel,voltage_output);
            }
            else if (strcmp(token[2], "h")||strcmp(token[2], "H")){
                amo7_holding_voltage[channel-1] = (int) tmp;
                double voltage_output = amo7_holding_voltage[channel-1]*4.096/256;
                printf("vouth.w : set motor #%d to holding at %1.3fV\n", channel, voltage_output);
                amo7_stepper_dac_update(channel-1, 0);
            }
            else if (strcmp(token[2], "p")||strcmp(token[2], "P")){
                amo7_pfd_voltage[channel-1] = (int) tmp;
                double voltage_output = amo7_pfd_voltage[channel-1]*4.096/256;
                printf("voutp.w : set motor #%d pfd to %1.3fV\n", channel,voltage_output);
                amo7_stepper_dac_update(amo7_stepper_motor_number, 2);
            }
        }
    }
    else if(strcmp(token[0],"vout.r")==0 && i==3) { //read moving voltage
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            double tmp = 0;
            if (strcmp(token[2], "m")||strcmp(token[2], "M")){
                tmp = amo7_moving_voltage[channel-1]*4.096/256;
            }
            else if (strcmp(token[2], "h")||strcmp(token[2], "H")){
                tmp = amo7_holding_voltage[channel-1]*4.096/256;
            }
            else if (strcmp(token[2], "p")||strcmp(token[2], "P")){
                tmp = amo7_pfd_voltage[channel-1]*4.096/256;
            }
            printf("%1.3fV\n", tmp);
        }
    }
    else if(strcmp(token[0],"out.w")==0 && i == 3) {  //write on/off
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);
        int tmp = atoi(token[2]);
        if (channel <= 12 && channel >=1){
            if (tmp == 0){
                amo7_stepper_enable[channel-1]=false;
                printf("out.w : motor %d disabled\n", channel);
            }
            else if (tmp == 1){
                amo7_stepper_enable[channel-1]=true;
                printf("out.w : motor %d enabled\n", channel);
            }
            amo7_motor_config(channel-1, 1, 0);
        }
    }
    else if(strcmp(token[0],"out.r")==0 && i == 2) {  //read on/off
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            printf("%d\n", amo7_stepper_enable[channel-1]);
        }
    }
    else if(strcmp(token[0],"move.w")==0 && i == 3) { //write move
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);     
        if (channel <= 12 && channel >=1){
            bool queuedup = false;
            for(int j=0; j < amo7_queue_index; j++){  //make sure motor isn't queued up
                if (channel-1 == amo7_step_queue[j]) queuedup = true;
            }
            if (queuedup == false){
                int previous_motor = amo7_stepper_motor_number;
                amo7_stepper_motor_number = channel-1;
                char *move_tmp[4];                       //split input into steps
                move_tmp[0] = strtok(token[2], ",");
                amo7_step_array[amo7_stepper_motor_number][0] = atoi(move_tmp[0]);
                for(int j = 1; j <= amo7_max_microstep_number; j++) {
                    move_tmp[j] = strtok(NULL, ",");
                    amo7_step_array[amo7_stepper_motor_number][j] = atoi(move_tmp[j]);
                }
                for(int j = 0; j <= amo7_max_microstep_number; j++) {//prevent move too far
                    if (abs(amo7_step_array[amo7_stepper_motor_number][j]) > amo7_max_steps){
                        amo7_step_array[amo7_stepper_motor_number][j] = amo7_max_steps;
                    }
                }
                amo7_move_config();
                amo7_stepper_motor_number = previous_motor;
                printf("move.w: motor #%d set to %s,%s,%s,%s\n", channel, move_tmp[0],move_tmp[1],move_tmp[2],move_tmp[3]);
            }
            else {
                printf("move.w invalid: motor currently queued up to move\n");
            }
        }
    }
    else if(strcmp(token[0],"move.r")==0 && i == 2) { //read step array
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            printf("%d steps: %d", 1, amo7_step_array[channel-1][0]);
            for (int j = 1; j<= amo7_max_microstep_number; j++){
                printf(" , %0.3f steps: %d", pow(2,-j), amo7_step_array[channel-1][j]);
            }
            printf("\n");
        }
    }
    else if(strcmp(token[0],"calib.w")==0 && i == 2) {  //calibrate array
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);
        if (channel<=12 && channel >=1){
            bool queuedup = false;
            for(int j=0; j< amo7_queue_index; j++){  //make sure motor isn't queued up
                if (channel-1 == amo7_step_queue[j]) queuedup = true;
            }
            if (queuedup == false){
                for (int k=0; k<=amo7_max_microstep_number; k++){ //reset step array of motor
                    amo7_move_array[channel-1][k] = 0;
                    amo7_step_array[channel-1][k] = 0;
                }
                printf("calib.w : calibrated motor #%d\n", channel);
            }
            else {
                printf("calib.w invalid: motor currently queued up to move\n");
            }
        }
    }
    else if(strcmp(token[0],"speed.w")==0 && i == 3) {  //write speed in steps/s
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);
        double tmp = atof(token[2]);
        if (channel <= 12 && channel >=1){
            double max_delay = 1000000/(amo7_base_delay + amo7_min_step_width);
            if (tmp > max_delay) tmp = max_delay;
            if (tmp < 0) tmp = 0;
            tmp = 1000000/tmp - amo7_base_delay;
            amo7_speed_delay[channel-1] = (long) tmp;
            double speed = 1000000/(amo7_speed_delay[channel-1] + amo7_base_delay);
            printf("speed.w : set motor #%d speed to %.2lf steps/s\n", channel, speed);
        }
    }
    else if(strcmp(token[0],"speed.r")==0 && i==2) { //read speed
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            double tmp = 1000000/(amo7_speed_delay[channel-1]+amo7_base_delay);
            printf("%.2lf steps/s\n", tmp);
        }
    }
    else if(strcmp(token[0],"id?")==0 && i == 1) {
        printf("%s\n", device_name);
        printf("Device ID : %s\n", device_id);
        printf("Hardware ID : %s\n", hardware_id);
        printf("Firmware ID : %s\n", firmware_id);
    }
    else if(strcmp(token[0],"help")==0) {
        printf("Commands:\nvout.w [mode] [motor number] [voltage]\nvout.r [mode] [motor number]\nout.w [motor number] [enable]\nout.r [motor number]\nmove.w [motor number] [full steps,0.5 steps,0.25 steps,0.125 steps]\nmove.r [motor number]\ncalib.w [motor number]\nspeed.w [motor number] [speed]\nspeed.r [motor number]\nid?\n");
    }
    else {
        printf("Command not recognized.\nType 'help' for list of commands.\n");
    }
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

//Screen (AMO6)
void amo6_screen_debug () {
    printf("CleO Version = %d\n", CleO.Version());
    printf("CleO ID = %d\n", CleO.ModuleIdentifier());
    CleO.Noop();
    printf("CleO Noop() Echo = %d\n", CleO.Echo());
    //printf("spi_flex_read_byte = 0x%x\n", spi_flex_read_byte(0));
    //printf("spi_flex_read_write_byte = 0x%x\n", spi_flex_read_write_byte(0, 0x8e));
}

void amo6_screen_init () {
    char buf_text[20];
    AMO6_CLEO_nPWR_DDR  |=  _BV(AMO6_CLEO_nPWR); //output
    AMO6_CLEO_nPWR_PORT |=  _BV(AMO6_CLEO_nPWR); //1
    _delay_ms(1000);
    AMO6_CLEO_nPWR_PORT &= ~_BV(AMO6_CLEO_nPWR); //0
    _delay_ms(1000);
    
    CleO.begin();
    CleO.Display(100); //brightness max=255
    CleO.Start();
    CleO.RectangleJustification(MM);
    CleO.SetBackgroundcolor(0xe9d3ebUL);
    sprintf(buf_text,device_name);
    CleO.StringExt(FONT_SANS_4, AMO6_SCREEN_W/2, 30, amo6_screen_text_color, MM, 0, 0, buf_text);
    sprintf(buf_text,"Device ID      : %s", device_id);
    CleO.StringExt(FONT_BIT_3, 10, 100, amo6_screen_text_color, ML, 0, 0, buf_text);
    sprintf(buf_text,"Hardware ID    : %s", hardware_id);
    CleO.StringExt(FONT_BIT_3 , 10 , 120 , amo6_screen_text_color , ML , 0 , 0, buf_text);
    sprintf(buf_text,"Firmware ID    : %s", firmware_id);
    CleO.StringExt(FONT_BIT_3, 10, 140, amo6_screen_text_color, ML, 0, 0, buf_text);
    sprintf(buf_text,"Starting Up ... ");
    CleO.StringExt(FONT_BIT_4 , 10 , 220 , amo6_screen_text_color , ML , 0 , 0, buf_text);
    CleO.Show();
    
    CleO.DisplayRotate(2, 0);
    CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo6_screen_update () {
    amo6_screen_draw();
    amo6_screen_touch();
}

#define AMO6_SCREEN_ROW1_Y	45
#define AMO6_SCREEN_ROW1_H	90
#define AMO6_SCREEN_ROW2_Y	125
#define AMO6_SCREEN_ROW2_H	70
#define AMO6_SCREEN_ROW3_Y	205
#define AMO6_SCREEN_ROW3_H	90
#define AMO6_SCREEN_ROW4_Y	285
#define AMO6_SCREEN_ROW4_H	70
#define AMO6_SCREEN_OFFSET  1

void amo6_screen_draw () { 
    // Start Drawing Screen
    CleO.Start();
    CleO.RectangleJustification(MM);
    CleO.SetBackgroundcolor(MY_BLACK);
    
    char text_buf[50];
    
    // Draw Boxes and Strings
    
    //Moving Voltage
    CleO.Tag(moving_voltge_output);
    CleO.RectangleColor(amo6_screen_select[moving_voltge_output] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 200-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    double output_volts = amo7_moving_voltage[amo7_stepper_motor_number]*4.096/256;
    sprintf(text_buf, "%1.3f", output_volts);
    CleO.StringExt(FONT_SANS_1, 160+3, 160+2, amo6_screen_text_color, TL, 0, 0, "Moving");
    CleO.StringExt(FONT_SANS_4, 280, 200, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_3, 290, 200+2, amo6_screen_text_color, MM, 0, 0, "V");
    
    //Holding Voltage
    CleO.Tag(holding_voltage_output);
    CleO.RectangleColor(amo6_screen_select[holding_voltage_output] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 280-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    double holding_volts = amo7_holding_voltage[amo7_stepper_motor_number]*4.096/256;
    sprintf(text_buf, "%1.3f", holding_volts);
    CleO.StringExt(FONT_SANS_1, 160+3, 240+2, amo6_screen_text_color, TL, 0, 0, "Holding");
    CleO.StringExt(FONT_SANS_4, 280, 280, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_3, 290, 280+2, amo6_screen_text_color, MM, 0, 0, "V");
    
    //Move Button
    CleO.Tag(move_button);
    CleO.RectangleColor(amo7_move_enable[amo7_stepper_motor_number] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    if (amo7_move_enable[amo7_stepper_motor_number]){
        CleO.StringExt(FONT_SANS_5, 400, 240, amo6_screen_text_color, MM, 0, 0, "MOVE");
    }
    else if (!amo7_move_enable[amo7_stepper_motor_number]  && amo7_step_queue[0] == amo7_stepper_motor_number) {
        CleO.StringExt(FONT_SANS_4, 400, 240, amo6_screen_text_color, MM, 0, 0, "MOVING");
    }
    else {
        CleO.StringExt(FONT_SANS_4, 400, 240, amo6_screen_text_color, MM, 0, 0, "QUEUED");
    }
    
    //Coarse Steps
    CleO.Tag(coarse_display);
    CleO.RectangleColor(amo6_screen_select[coarse_display] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 40-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    double total_angle=0;
    for (int i=0;i<=amo7_max_microstep_number;i++){
        total_angle +=amo7_step_array[amo7_stepper_motor_number][i]*(amo7_step_size[amo7_stepper_motor_number]/pow(2,i));
    }
    sprintf(text_buf, "%.2f", total_angle);
    if (total_angle >= 1000){
        CleO.StringExt(FONT_SANS_4, 459, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    else {
        CleO.StringExt(FONT_SANS_5, 459, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    CleO.StringExt(FONT_SANS_2, 465, 20, amo6_screen_text_color, MM, 0, 0, "o");
    
    //Calibrate Button
    CleO.Tag(calibrate_button);
    CleO.RectangleColor(amo7_move_enable[amo7_stepper_motor_number] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 120-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_3, 400, 120, amo6_screen_text_color, MM, 0, 0, "CALIBRATE");
    
    //Fine Steps
    CleO.Tag(step_counter);
    CleO.RectangleColor(amo6_screen_select[step_counter] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 40-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    sprintf(text_buf, "%d", amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number]);
    if (amo7_step_array[amo7_stepper_motor_number][amo7_microstep_number] >= 1000){
        CleO.StringExt(FONT_SANS_4, 248, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    else {
        CleO.StringExt(FONT_SANS_5, 248, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    CleO.StringExt(FONT_SANS_2, 280, 40+8, amo6_screen_text_color, MM, 0, 0, "steps");
    
    //Fine Step Adjustment
    CleO.Tag(fine_step_adjustment);
    CleO.RectangleColor(amo6_screen_select[fine_step_adjustment] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 120-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    sprintf(text_buf, "1/%.f ", pow(2,amo7_microstep_number));
    CleO.StringExt(FONT_SANS_6, 240, 120, amo6_screen_text_color, MM, 0, 0, text_buf);
    sprintf(text_buf, "%.3f", amo7_step_size[amo7_stepper_motor_number]/pow(2,amo7_microstep_number));
    CleO.StringExt(FONT_SANS_1, 305, 150, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_TINY, 305, 142, amo6_screen_text_color, ML, 0, 0, " o");
    
    //Stepper Motor Counter
    CleO.Tag(stepper_motor_counter);
    CleO.RectangleColor(amo6_screen_select[stepper_motor_counter] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(80-2*AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    sprintf(text_buf, "#%d", amo7_stepper_motor_number+1);
    CleO.StringExt(FONT_SANS_6, 80, 80, amo6_screen_text_color, MM, 0, 0, text_buf);

    //ON/OFF Switch
    CleO.Tag(on_off_switch);
    CleO.RectangleColor(amo7_stepper_enable[amo7_stepper_motor_number] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(80-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    strcpy(text_buf, amo7_stepper_enable[amo7_stepper_motor_number]? "ON" : "OFF");
    CleO.StringExt(FONT_SANS_5, 80, 240, amo6_screen_text_color, MM, 0, 0, text_buf);
    
    // Update Screen
    CleO.Show();
}

void amo6_screen_touch () {
    amo6_screen_processButtons();
    if (amo6_screen_short_press_detected) amo6_screen_processShortPress();
}

void amo6_screen_processButtons () {
    // Collect Tags
    //NOTE: for more than 13 tags, you must manually tag!
    CleO.TouchCoordinates(amo6_screen_x, amo6_screen_y, amo6_screen_current_dur, amo6_screen_current_tag);
    
    // Process Short Press
    amo6_screen_shortPress(&amo6_screen_short_press_detected);
    amo6_screen_last_dur = amo6_screen_current_dur;
}

void amo6_screen_shortPress (bool *press_detected) {
    if (amo6_screen_current_dur==1 && amo6_screen_last_dur==0 && !*press_detected) {
        *press_detected = 1;
        //SerialUSB.println("Short press!");
    }
    else {
        *press_detected = 0;
    }
}

void amo6_screen_processShortPress () {
    int i;
    bool sel;
    if(!amo3_pwr_state)
        return;
    
    switch (amo6_screen_current_tag) {
        case moving_voltge_output	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[moving_voltge_output];
            for(i=0;i<AMO6_SCREEN_TAGS;i++)amo6_screen_select[i]=0;
            amo6_screen_select[moving_voltge_output] = sel;
            break;
        case holding_voltage_output	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[holding_voltage_output];
            for(i=0;i<AMO6_SCREEN_TAGS;i++)amo6_screen_select[i]=0;
            amo6_screen_select[holding_voltage_output] = sel;
            break;
        case on_off_switch	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            amo7_stepper_enable[amo7_stepper_motor_number] = !amo7_stepper_enable[amo7_stepper_motor_number];
            amo7_motor_config(amo7_stepper_motor_number, false, 0);
            sel = !amo6_screen_select[on_off_switch];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            break;
        case move_button	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            for(i=0;i<move_button;i++) amo6_screen_select[i]=0;
            for(i=move_button+1;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            if (amo7_move_enable[amo7_stepper_motor_number]) amo7_move_config();
            break;
        case calibrate_button	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            for(i=0;i<calibrate_button;i++) amo6_screen_select[i]=0;
            for(i=calibrate_button+1;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            if (amo7_move_enable[amo7_stepper_motor_number]){
                for (i=0; i<=amo7_max_microstep_number; i++){ //reset step array of motor
                    amo7_move_array[amo7_stepper_motor_number][i] = 0;
                    amo7_step_array[amo7_stepper_motor_number][i] = 0;
                }
            }
            break;
        case coarse_display	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[coarse_display];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            amo6_screen_select[coarse_display] = sel;
            break;
        case step_counter	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[step_counter];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            amo6_screen_select[step_counter] = sel;
            break;
        case fine_step_adjustment	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[fine_step_adjustment];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            amo6_screen_select[fine_step_adjustment] = sel;
            break;
        case stepper_motor_counter	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[stepper_motor_counter];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            amo6_screen_select[stepper_motor_counter] = sel;
            break;
    }
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

//Motors (AMO7)
void amo7_dac_init(){
    uint32_t init_input = 8;                    //command code 0001 in reverse
    init_input |= (15 << 4);                    //all dac address code
    PORTA &= ~(_BV(AMO7_DAC_LOAD));             //CS/LD low to begin serial input
    for (int i=0; i<=23; i++){
        PORTA &= ~(_BV(AMO7_DAC_CLOCK));        //dac clocks sdi in on rising edge
        if (init_input & _BV(0)){
            PORTA |= _BV(AMO7_DAC_INPUT);
        }
        else {
            PORTA &= ~(_BV(AMO7_DAC_INPUT));
        }
        PORTA |= _BV(AMO7_DAC_CLOCK);
        init_input >>= 1;
    }
    
    PORTA |= _BV(AMO7_DAC_LOAD);                //CS/LD high to finish serial input 
    _delay_ms(50);
    for (int i = 0; i<= amo7_max_stepper_motor_number; i++){  //set pfd for motors
        amo7_stepper_dac_update(i, 2);        
    }
}

void amo7_stepper_dac_update (int motor_num, int mode) {
    uint16_t dac_input = 0x3000;        //command code 0011
    uint8_t address_code = 2*(motor_num % 3);
    amo7_board_config(motor_num);
    switch (mode){                      //mode: 0 = holding, 1 = moving, 2 = pfd
        case 0:
            dac_input |= amo7_holding_voltage[motor_num];   
            break;
        case 1:
            dac_input |= amo7_moving_voltage[motor_num];
            break;
        case 2:
            address_code += 1;
            dac_input |= amo7_pfd_voltage[motor_num];
            break;
    }
    dac_input |= (address_code << 8);
    PORTA &= ~(_BV(AMO7_DAC_LOAD));     //CS/LD low to begin serial input
    for (int i=0; i<=15; i++){
        PORTA &= ~(_BV(AMO7_DAC_CLOCK));//dac clocks sdi in on rising edge
        if (dac_input & _BV(15)){
            PORTA |= _BV(AMO7_DAC_INPUT);        
        }
        else {
            PORTA &= ~(_BV(AMO7_DAC_INPUT));
        }
        PORTA |= _BV(AMO7_DAC_CLOCK);
        dac_input <<= 1;
    }
    PORTA &= ~(_BV(AMO7_DAC_INPUT));    //+8 don't-care bits since message must be 24b
    for (int i=0; i<=7; i++){           
        PORTA &= ~(_BV(AMO7_DAC_CLOCK));
        PORTA |= _BV(AMO7_DAC_CLOCK);
    }
    PORTA |= _BV(AMO7_DAC_LOAD);        //CS/LD high to finish serial input
}

void background_stepping (){
    if (amo7_queue_index != 0){
        if (amo7_new_motor){
            amo7_stepper_dac_update(amo7_step_queue[0], 1);
            amo7_new_motor = false;
        }
        if (amo7_new_microstep){
            amo7_motor_config(amo7_step_queue[0], amo7_dir_arr[amo7_queued_microstep_counter],amo7_queued_microstep_counter);
            amo7_new_microstep = false;
        }
        if (amo7_move_array[amo7_step_queue[0]][amo7_queued_microstep_counter] == 0 && (amo7_queued_microstep_counter < 3)) {
            amo7_queued_microstep_counter += 1;
            amo7_new_microstep = true;
        }
        else if (amo7_move_array[amo7_step_queue[0]][amo7_queued_microstep_counter] == 0 && amo7_queued_microstep_counter >= 3){    //end of current motor, reset & move on
            for (int k = 0; k <= amo7_max_microstep_number; k++){
                amo7_move_array[amo7_step_queue[0]][k]=amo7_step_array[amo7_step_queue[0]][k];
            }
            amo7_move_enable[amo7_step_queue[0]] = 1;
            amo7_step_queue[0] = 0;
            amo7_queued_microstep_counter = 0;
            amo7_stepper_dac_update(amo7_step_queue[0], 0);
            if (amo7_queue_index != 0) amo7_new_motor = true;
            for (int i = 1; i<= amo7_queue_index; i++){
                amo7_step_queue[i-1] = amo7_step_queue[i];
            }
            amo7_queue_index -= 1;
            amo7_new_microstep = true;
        }
        else if (amo7_move_array[amo7_step_queue[0]][amo7_queued_microstep_counter] != 0){ //move motor
            int tmp = amo7_dir_arr[amo7_queued_microstep_counter]? -1:1;
            amo7_move_motor(amo7_step_queue[0], 1, amo7_speed_delay[amo7_step_queue[0]]);
            amo7_move_array[amo7_step_queue[0]][amo7_queued_microstep_counter] += tmp;
        }
    }
}

void amo7_board_config(int motor_num) {
    uint8_t board_num = (motor_num-(motor_num%3))/3;
    uint8_t c_config = PORTC;    //C4-C7 are input, so maintain their values
    c_config |= 0x0f;
    c_config &= ~(_BV(board_num));
    PORTC = c_config;           
}

void amo7_motor_config(int motor_num, bool dir, int msn) {
    PORTA &= ~(_BV(AMO7_DRV_CLEAR));        //Reset shift registers
    PORTA |= _BV(AMO7_DRV_CLEAR);
    uint16_t reg_input = 2115;              //2^0(sleep)+2^1(rs3)+2^6(rs2)+2^11(rs1)
    int ms_shift = 14 - 5*(motor_num % 3);  //Shifts microstepping to appropriate pin output   
    amo7_board_config(motor_num);
    reg_input |= msn<<ms_shift;
    reg_input |= dir<<(ms_shift-1);
    reg_input |= 0x1084;                    //here, we enable motors in current board
    int board_num_min = motor_num-(motor_num%3);    
    for (int i = board_num_min; i <= board_num_min+2; i++){
        if (amo7_stepper_enable[i]){             
            int on_off_shift = 12-5*(i%3);  
            reg_input &= ~(_BV(on_off_shift)); 
        }
    }
    for (int i=0; i<=15; i++){
        PORTA &= ~(_BV(AMO7_DRV_CLOCK));    //drv clocks in on rising edge
        if (reg_input & _BV(0)){
            PORTA |= _BV(AMO7_DRV_INPUT);
        }
        else {
            PORTA &= ~(_BV(AMO7_DRV_INPUT));
        }
        PORTA |= _BV(AMO7_DRV_CLOCK);
        reg_input >>= 1;
    }
    PORTA |= _BV(AMO7_DRV_LOAD);
    PORTA &= 0xf1;                          //Set A1-A3 low
}

void amo7_move_config (){
    int rounding_steps = 0;
    bool detect_movement = false;
    int exp_bug = 1;                    //need int since float behaves weirdly
    for (int i = 0; i<=amo7_max_microstep_number; i++){
        amo7_move_array[amo7_stepper_motor_number][i] = amo7_step_array[amo7_stepper_motor_number][i]-amo7_move_array[amo7_stepper_motor_number][i];
        rounding_steps += amo7_step_array[amo7_stepper_motor_number][i]*8/ exp_bug;
        rounding_steps %= 8;
        exp_bug *= 2;
        if (amo7_move_array[amo7_stepper_motor_number][i] != 0){
            detect_movement = true;
        }
    }
    if (!detect_movement){              //update amo7_move_array and do nothing
            for (int i = 0; i <= amo7_max_microstep_number; i++){
                amo7_move_array[amo7_stepper_motor_number][i]=amo7_step_array[amo7_stepper_motor_number][i];
            }
         return;
    }
    if (rounding_steps != 0 && detect_movement){
        bool round_dir = rounding_steps > 0? false:true;        //move to nearest full step
        amo7_stepper_dac_update(amo7_stepper_motor_number, 1);  //change to moving voltage
        amo7_motor_config(amo7_stepper_motor_number, round_dir, 3);
        amo7_move_motor(amo7_stepper_motor_number, abs(rounding_steps), 2000);
        amo7_stepper_dac_update(amo7_stepper_motor_number, 0);  //back to holding voltage
        _delay_ms(50);
        amo7_move_array[amo7_stepper_motor_number][3] += rounding_steps;
    }
    for (int i = 0; i<=amo7_max_microstep_number; i++){              //set direction for background
        amo7_dir_arr[i] = amo7_move_array[amo7_stepper_motor_number][i]>0 ? true:false;
    }
    amo7_move_enable[amo7_stepper_motor_number] = 0;
    amo7_step_queue[amo7_queue_index] = amo7_stepper_motor_number; 
    if (amo7_queue_index == 0) amo7_new_motor = true;
    amo7_queue_index += 1;
}

void amo7_move_motor (int motor_num, int steps, int delaytime){
    int step_shift = (motor_num % 3) + 4;
    for (int j = 0; j<steps; j++){
        PORTJ |= _BV(step_shift);
        while (delaytime > 0){
            delaytime -= 10;
            _delay_us(10);
        }
        PORTJ &= ~(_BV(step_shift));
    }
}

#endif // AMO3_H