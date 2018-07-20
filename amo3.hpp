#ifndef AMO3_H
#define AMO3_H 1

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <avr/eeprom.h>

//////////////////////////////////////////////////////////////////////////////////////
// Tracking
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "Piezo Controller";
const char device_id[]   = "AMO3";
const char hardware_id[] = "0.1.2";
const char firmware_id[] = "0.0.2";

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

//  AMO3
bool    debugging_power         = false;
bool    amo3_tec_state          = true;
bool    amo3_tec_state_latched  = true; 
double  amo3_voltage_out  [4]   = {0.0, 0.0, 0.0, 0.0}; 
bool    amo3_enable  [4]        = {false, false, false, false};
enum {
  amo3_fault_none	, //0
  amo3_fault_pwr	, //1
};
const char* amo3_fault_string[] = {
  "No faults"		,
  "nPower pin High"	
};
uint8_t  amo3_fault       = amo3_fault_none;
uint8_t  amo3_fault_prev  = amo3_fault_none;

uint16_t  EEMEM amo3_eeprom_vout1_mv_hi;
uint16_t  EEMEM amo3_eeprom_vout2_mv_hi;
uint16_t  EEMEM amo3_eeprom_vout3_mv_hi;
uint16_t  EEMEM amo3_eeprom_vout4_mv_hi;
uint16_t  EEMEM amo3_eeprom_vout1_mv_lo;
uint16_t  EEMEM amo3_eeprom_vout2_mv_lo;
uint16_t  EEMEM amo3_eeprom_vout3_mv_lo;
uint16_t  EEMEM amo3_eeprom_vout4_mv_lo;
uint8_t   amo3_save_flag  = 0;

void  amo3_init             ();
void  amo3_load_state       ();
void  amo3_save_state       ();
void  amo3_fault_check      ();
void  amo3_hardware_update  ();

//  VOUT
const float  amo3_vout_mv_to_cnts  [4]  = {0.4369,0.4369,0.4369,0.4369};
uint16_t     amo3_vout_cnts_max         = 65535;
uint32_t     amo3_vout_mv               = 123456;
uint32_t     amo3_mv_latched[4]         = {0,0,0,0};
float        max_V                      = 150.000;
AD5544       amo3_VOUT_dac  (SPI_FLEX_AMO3_VOUT);

void  amo3_VOUT_init    ();
void  amo3_VOUT_set_mv  (uint32_t val, uint32_t dac);

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
  amo6_screen_voltage_output1  , // 1
  amo6_screen_voltage_output2  , // 2
  amo6_screen_voltage_output3  , // 3
  amo6_screen_voltage_output4  , // 4
  amo6_screen_enable_output1   , // 5
  amo6_screen_enable_output2   , // 6
  amo6_screen_enable_output3   , // 7
  amo6_screen_enable_output4   , // 8
};
#define AMO6_SCREEN_TAGS 8	
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

//////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// AMO3 
void amo3_init ()
{
  // hardware i/o config
  AMO6_CLEO_nPWR_DDR  |=  _BV(AMO6_CLEO_nPWR);//output
  AMO6_CLEO_nPWR_PORT |=  _BV(AMO6_CLEO_nPWR); //1
  
  AMO3_PWR_nOK_DDR  &= ~_BV(AMO3_PWR_nOK); //input
  AMO3_PWR_nOK_PORT &= ~_BV(AMO3_PWR_nOK); //disable pullup
  amo3_VOUT_dac.init();

  AMO6_EXT1_nEN_DDR  |=  _BV(AMO6_EXT1_nEN); //output
  AMO6_EXT1_nEN_PORT &= ~_BV(AMO6_EXT1_nEN); //0
  AMO6_EXT2_nEN_DDR  |=  _BV(AMO6_EXT2_nEN); //output
  AMO6_EXT2_nEN_PORT &= ~_BV(AMO6_EXT2_nEN); //0
  AMO6_BUZZER_nEN_DDR  |=  _BV(AMO6_BUZZER_nEN); //output
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
  
  // hardware init
  amo3_VOUT_init(); //first call doesn't work
  amo6_screen_init();
  amo6_buttons_init();
  amo3_load_state();
  amo3_VOUT_init(); //need this second call to reset properly
  _delay_ms(5000);
}

void amo3_load_state ()
{
  // retrieve top 16 bit and bottom 16 bit from memory
  // convert top 16bit and bottom 16bit into integer
  uint32_t val = ((uint32_t)eeprom_read_word(&amo3_eeprom_vout1_mv_hi)<<16)|eeprom_read_word(&amo3_eeprom_vout1_mv_lo);
  // convert integer into float
  amo3_voltage_out[0] = val > 150000? 150: val/1000.0;

  val = ((uint32_t)eeprom_read_word(&amo3_eeprom_vout2_mv_hi)<<16)|eeprom_read_word(&amo3_eeprom_vout2_mv_lo);
  amo3_voltage_out[1] = val > 150000? 150: val/1000.0;

  val = ((uint32_t)eeprom_read_word(&amo3_eeprom_vout3_mv_hi)<<16)|eeprom_read_word(&amo3_eeprom_vout3_mv_lo);
  amo3_voltage_out[2] = val > 150000? 150: val/1000.0;

  val = ((uint32_t)eeprom_read_word(&amo3_eeprom_vout4_mv_hi)<<16)|eeprom_read_word(&amo3_eeprom_vout4_mv_lo);
  amo3_voltage_out[3] = val > 150000? 150: val/1000.0;
}

void amo3_save_state ()
{
  // convert float into integer
  uint32_t val = amo3_voltage_out[0]*1000;
  // split integer to top 16bit and bottom 16bit
  // save top 16bit and bottom 16bit into memory
  uint16_t hi_word = val >> 16;
  uint16_t lo_word = val & 0xFFFF;
  eeprom_update_word(&amo3_eeprom_vout1_mv_hi, hi_word);
  eeprom_update_word(&amo3_eeprom_vout1_mv_lo, lo_word);

  val = amo3_voltage_out[1]*1000;
  hi_word = val >> 16;
  lo_word = val & 0xFFFF;
  eeprom_update_word(&amo3_eeprom_vout2_mv_hi, hi_word);
  eeprom_update_word(&amo3_eeprom_vout2_mv_lo, lo_word);

  val = amo3_voltage_out[2]*1000;
  hi_word = val >> 16;
  lo_word = val & 0xFFFF;
  eeprom_update_word(&amo3_eeprom_vout3_mv_hi, hi_word);
  eeprom_update_word(&amo3_eeprom_vout3_mv_lo, lo_word);

  val = amo3_voltage_out[3]*1000;
  hi_word = val >> 16;
  lo_word = val & 0xFFFF;
  eeprom_update_word(&amo3_eeprom_vout4_mv_hi, hi_word);
  eeprom_update_word(&amo3_eeprom_vout4_mv_lo, lo_word);
}

void amo3_fault_check ()
{
  // NOTE: there is additional fault checking code in the hardware_update() function
  if (AMO6_CLEO_nPWR || debugging_power){
    if(amo3_fault != amo3_fault_pwr){
      amo3_fault = amo3_fault_pwr;
      if (amo3_tec_state){
        int i;
        //disable all output
        for (i = 0; i<4; ++i){ amo3_VOUT_set_mv(0, i); }
	for (i = 0; i<4; ++i){ amo3_voltage_out[i] = 0; }
        for (i = 0; i<4; ++i){ amo3_enable[i] = false; }
        amo3_tec_state = false;
      }
    }
  }
  else {
    if (amo3_fault != amo3_fault_none){
      amo3_fault_prev = amo3_fault;
      amo3_fault = amo3_fault_none;
      // NOTE, if the AMO6_CLEO_nPWR fault is turned to logiv low after being in logic high, we allow user to alter voltages again 
      if (!amo3_tec_state){
        amo3_tec_state = true;
      }
    }
  }
}

void amo3_hardware_update ()
{
  // sends voltage values
  uint8_t i;
  if (amo3_tec_state && (amo3_fault==amo3_fault_none)) { ;
    for (i=0;i<4;++i){
      uint32_t val = (amo3_enable[i])? (amo3_voltage_out[i]*1000.0) : 0;
      if (val != amo3_mv_latched[i]){
        amo3_mv_latched[i] = val;
        amo3_VOUT_set_mv(val, i);
      }
    }
    // we only want to display save flag for a fixed number of seconds
    if (amo3_save_flag)
      --amo3_save_flag;
  }
  // fault handling
  if(amo3_tec_state != amo3_tec_state_latched) { //tec on/off
    if (amo3_tec_state && (amo3_fault==amo3_fault_none)){ ;
      //IF FAULT -> NO FAULT
    }
    else{ ;
      //IF NO FAULT -> FAULT
    }
    amo3_tec_state_latched = amo3_tec_state;
  }
}

void amo3_VOUT_init ()
{
  uint8_t i;
  for (i = 0; i<4; ++i){ amo3_VOUT_set_mv(0, i); };
  for (i = 0; i<4; ++i){ amo3_enable[i] = false; }
  amo3_tec_state = true;

  // testing
  //amo3_VOUT_dac.setCounts(0, test_output); //test offset
}

void amo3_VOUT_set_mv (uint32_t val, uint32_t dac)
{
  //val is the value in [mv]
  //dac is which dac is being selected
  amo3_vout_mv = val;
  val = amo3_vout_mv * amo3_vout_mv_to_cnts[dac];
  if (val > 65535) val = 65535;
  amo3_VOUT_dac.setCounts(val, dac);
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

void amo6_buttons_update () 
{
  static int tag_old = 0;
  int tag;
  float tmp;
  bool sw1_now = (PINB>>PB6) & 0x01;
  bool sw2_now = (PINB>>PB5) & 0x01;
  if (!amo3_tec_state)
    return;
  
  for (tag=0;tag<AMO6_SCREEN_TAGS-1;tag++) { //find active screen tag
    if (amo6_screen_select[tag]==1) break;
  };

  // (+) both buttons are pressed
  if (amo6_sw1_pushed && amo6_sw2_pushed){
    switch (tag) {
      // do not do anything if something is selected
      case amo6_screen_voltage_output1	:
      case amo6_screen_voltage_output2	:
      case amo6_screen_voltage_output3	:
      case amo6_screen_voltage_output4	:
	break;
      // save the state is nothing is selected
      default :
	//display save flag for 4 loops/iterations
	amo3_save_flag = 4;
	// BEEP
	AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	_delay_ms(60);
	AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
	// save to EEPROM
	amo3_save_state();
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
  
  // sw1 pressed
  if (amo6_sw1_pushed) {
    // (+) only update if other button is not pressed
    if (!amo6_count_latch[1]){
      amo6_count_latch[0] = true; // start counting hold time
      if (!sw1_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
        switch (tag) {
        case amo6_screen_voltage_output1	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[0] - 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[0] = tmp;
          break;
        case amo6_screen_voltage_output2	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[1] - 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[1] = tmp;
          break;
        case amo6_screen_voltage_output3	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[2] - 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[2] = tmp;
          break;
        case amo6_screen_voltage_output4	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[3] - 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[3] = tmp;
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
  
  // sw2 pressed
  if (amo6_sw2_pushed) {
    // (+) only update if other button is not pressed
    if (!amo6_count_latch[0]){
      amo6_count_latch[1] = true; // start counting hold time
      if (!sw2_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
        switch (tag) {
        case amo6_screen_voltage_output1	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[0] + 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[0] = tmp;
          break;
        case amo6_screen_voltage_output2	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[1] + 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[1] = tmp;
          break;
        case amo6_screen_voltage_output3	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[2] + 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[2] = tmp;
          break;
        case amo6_screen_voltage_output4	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[3] + 1;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[3] = tmp;
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

  // (+) sw2 held
  if (amo6_count_latch[1]){
    // increment hold_counter
    if (amo6_hold_count[1] < amo6_hold_threshold)
      ++(amo6_hold_count[1]);
    // update values
    if (amo6_hold_count[1] >= amo6_hold_threshold){
      switch (tag) {
        case amo6_screen_voltage_output1	:
 	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
 	  _delay_ms(5);
	  tmp = amo3_voltage_out[0] + 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[0] = tmp;
          break;
        case amo6_screen_voltage_output2	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[1] + 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[1] = tmp;
          break;
        case amo6_screen_voltage_output3	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[2] + 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[2] = tmp;
          break;
        case amo6_screen_voltage_output4	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[3] + 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[3] = tmp;
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
  // (+) sw1 held
  if (amo6_count_latch[0]){
    // increment hold_counter
    if (amo6_hold_count[0] < amo6_hold_threshold)
      ++(amo6_hold_count[0]);
    // update values
    if (amo6_hold_count[0] >= amo6_hold_threshold){
      switch (tag) {
        case amo6_screen_voltage_output1	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[0] - 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[0] = tmp;
          break;
        case amo6_screen_voltage_output2	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[1] - 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[1] = tmp;
          break;
        case amo6_screen_voltage_output3	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[2] - 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[2] = tmp;
          break;
        case amo6_screen_voltage_output4	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo3_voltage_out[3] - 10;
	  if (tmp>max_V) tmp=max_V;
	  if (tmp<0) tmp=0;
	  amo3_voltage_out[3] = tmp;
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
      case amo6_screen_voltage_output1	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo3_voltage_out[0] + val/200.0;
	if (tmp>max_V) tmp=max_V;
	if (tmp<0) tmp=0;
	amo3_voltage_out[0] = tmp;
        break;
      case amo6_screen_voltage_output2	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo3_voltage_out[1] + val/200.0;
	if (tmp>max_V) tmp=max_V;
	if (tmp<0) tmp=0;
	amo3_voltage_out[1] = tmp;
        break;
      case amo6_screen_voltage_output3	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo3_voltage_out[2] + val/200.0;
	if (tmp>max_V) tmp=max_V;
	if (tmp<0) tmp=0;
	amo3_voltage_out[2] = tmp;
        break;
      case amo6_screen_voltage_output4	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo3_voltage_out[3] + val/200.0;
	if (tmp>max_V) tmp=max_V;
	if (tmp<0) tmp=0;
	amo3_voltage_out[3] = tmp;
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

// Serial (AMO6)
void amo6_serial_update ()
{
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
  int i=0;
  //float tmp;
  
  token[0] = strtok(amo6_serial_string, delimiters);
  i++;
  while(i<8) {
    token[i] = strtok (NULL, delimiters);
    if(token[i] == NULL) break;
    i++;
  }
  
  if(strcmp(token[0],"vout.w")==0) {
    if(i==3){
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
      _delay_ms(5);
      int channel = atoi(token[1]);
      float tmp = atof(token[2]);
      if (tmp > max_V) tmp = max_V; //tagasdf
      if (tmp < 0) tmp = 0;
      if (channel <= 4 && channel >=1)
        amo3_voltage_out[channel-1] = tmp;
      printf("vout.w : set output #%d to %0.3f\n", channel, amo3_voltage_out[channel-1]);
    }
  }
  else if(strcmp(token[0],"vout.r")==0) {
    if(i==2){
      int channel = atoi(token[1]);
      if (channel <= 4 && channel >=1){
	printf("%0.3f\n", amo3_mv_latched[channel-1]/1000.0);
      }
    }
  }
  else if(strcmp(token[0],"out.w")==0) {
    if(i==3){
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
      _delay_ms(5);
      int channel = atoi(token[1]);
      int tmp = atoi(token[2]);
      if (channel <= 4 && channel >=1)
      {
        if (tmp == 0){
          amo3_enable[channel-1]=false;
	  printf("out.w : output %d disabled\n", channel);
        }
        else if (tmp == 1){
          amo3_enable[channel-1]=true;
	  printf("out.w : output %d enabled\n", channel);
        }
      }
    }
  }
  else if(strcmp(token[0],"out.r")==0) {
    if(i==2){
      int channel = atoi(token[1]);
      if (channel <= 4 && channel >=1)
      {
	printf("%d\n", amo3_enable[channel-1]);
      }
    }
  }
  else if(strcmp(token[0],"id?")==0) {
    if(i==1) {
      printf("%s\n", device_name);
      printf("Device ID : %s\n", device_id);
      printf("Hardware ID : %s\n", hardware_id);
      printf("Firmware ID : %s\n", firmware_id);
    }
  }
  else if(strcmp(token[0],"help")==0) {
    printf("Commands:\nvout.w [channel] [voltage]\nout.w [channel] [enable]\nid?\n");
  }
  //for debugging... simulating fault handling
  else if(strcmp(token[0],"pwr.w")==0) {
    printf("PWR PIN: %d\n",AMO6_CLEO_nPWR);
  }
  else if(strcmp(token[0],"trigger_fault.w")==0) {
    debugging_power = !debugging_power;
    printf("Fault triggered: %d\n",!amo3_tec_state);
  }
  else {
    printf("Command not recognized.\nType 'help' for list of commands.\n");
  }
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

//Screen (AMO6)
void amo6_screen_debug ()
{
  printf("CleO Version = %d\n", CleO.Version());
  printf("CleO ID = %d\n", CleO.ModuleIdentifier());
  CleO.Noop();
  printf("CleO Noop() Echo = %d\n", CleO.Echo());
  //printf("spi_flex_read_byte = 0x%x\n", spi_flex_read_byte(0));
  //printf("spi_flex_read_write_byte = 0x%x\n", spi_flex_read_write_byte(0, 0x8e));
}

void amo6_screen_init ()
{
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
  sprintf(buf_text,"Device ID : %s", device_id);
  CleO.StringExt(FONT_BIT_3, 10, 100, amo6_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Hardware ID : %s", hardware_id);
  CleO.StringExt(FONT_BIT_3 , 10 , 120 , amo6_screen_text_color , ML , 0 , 0, buf_text);
  sprintf(buf_text,"Firmware ID : %s", firmware_id);
  CleO.StringExt(FONT_BIT_3, 10, 140, amo6_screen_text_color, ML, 0, 0, buf_text);
//  sprintf(buf_text,"%lu,%2.2f,%0.5f,%lu", amo1_iout_max_set_ua/1000, amo1_iout_res, amo1_iout_ua_to_cnts, amo1_pfet_max_mw);
//  CleO.StringExt(FONT_BIT_3, 10, 180, amo6_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Starting Up ... ");
  CleO.StringExt(FONT_BIT_4 , 10 , 220 , amo6_screen_text_color , ML , 0 , 0, buf_text);
  CleO.Show();
  
  CleO.DisplayRotate(2, 0);
  CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo6_screen_update ()
{
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
#define AMO6_SCREEN_OFFSET      1

void amo6_screen_draw ()
{ 
  // Start Drawing Screen
  CleO.Start();
  CleO.RectangleJustification(MM);
/*
  CleO.LineColor(MY_BLACK);

  CleO.LineWidth(2);
  CleO.Line(0, AMO6_SCREEN_ROW1_Y + AMO6_SCREEN_ROW1_H/2, 480, AMO6_SCREEN_ROW1_Y + AMO6_SCREEN_ROW1_H/2);
  CleO.Line(0, AMO6_SCREEN_ROW3_Y + AMO6_SCREEN_ROW3_H/2, 480, AMO6_SCREEN_ROW3_Y + AMO6_SCREEN_ROW3_H/2);
  CleO.LineWidth(3);
  CleO.Line(240, AMO6_SCREEN_ROW1_Y + AMO6_SCREEN_ROW1_H/2, 240, AMO6_SCREEN_ROW1_Y - AMO6_SCREEN_ROW1_H/2);
  CleO.Line(240, AMO6_SCREEN_ROW2_Y + AMO6_SCREEN_ROW2_H/2, 240, AMO6_SCREEN_ROW2_Y - AMO6_SCREEN_ROW2_H/2);
  CleO.Line(240, AMO6_SCREEN_ROW3_Y + AMO6_SCREEN_ROW3_H/2, 240, AMO6_SCREEN_ROW3_Y - AMO6_SCREEN_ROW3_H/2);
  CleO.Line(240, AMO6_SCREEN_ROW4_Y + AMO6_SCREEN_ROW4_H/2, 240, AMO6_SCREEN_ROW4_Y - AMO6_SCREEN_ROW4_H/2);
  CleO.Line(0, AMO6_SCREEN_ROW2_Y + AMO6_SCREEN_ROW2_H/2, 480, AMO6_SCREEN_ROW2_Y + AMO6_SCREEN_ROW2_H/2);
*/
  CleO.SetBackgroundcolor(MY_BLACK);

  char text_buf[50];

  // Draw the Voltage boxes
  // Draw the Voltage strings
  CleO.Tag(amo6_screen_voltage_output1);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output1] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW1_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW1_H-AMO6_SCREEN_OFFSET);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[0]);
  CleO.StringExt(FONT_SANS_6, 200, AMO6_SCREEN_ROW1_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 220, AMO6_SCREEN_ROW1_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW1_Y-30, amo6_screen_text_color, MM, 0, 0, "1");

  CleO.Tag(amo6_screen_voltage_output3);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output3] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW3_H-3*AMO6_SCREEN_OFFSET);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[2]);
  CleO.StringExt(FONT_SANS_6, 200, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 220, AMO6_SCREEN_ROW3_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW3_Y-30, amo6_screen_text_color, MM, 0, 0, "3");


  CleO.Tag(amo6_screen_voltage_output2);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output2] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW1_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW1_H-AMO6_SCREEN_OFFSET);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[1]);
  CleO.StringExt(FONT_SANS_6, 440, AMO6_SCREEN_ROW1_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 460, AMO6_SCREEN_ROW1_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW1_Y-30, amo6_screen_text_color, MM, 0, 0, "2");


  CleO.Tag(amo6_screen_voltage_output4);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output4] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW3_H-3*AMO6_SCREEN_OFFSET);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[3]);
  CleO.StringExt(FONT_SANS_6, 440, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 460, AMO6_SCREEN_ROW3_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW3_Y-30, amo6_screen_text_color, MM, 0, 0, "4");

  // Draw the ON/OFF boxes

  // (+) we write string "SAVED" if we write to EEPROM
  if (amo3_fault == amo3_fault_none){
    // Draw the ON/OFF strings
    CleO.Tag(amo6_screen_enable_output1);
    CleO.RectangleColor(amo3_enable[0] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW2_H-3*AMO6_SCREEN_OFFSET);
    if (!amo3_save_flag)
      strcpy(text_buf, amo3_enable[0]? "ON" : "OFF");
    else
      strcpy(text_buf, "Saved");
    CleO.StringExt(FONT_SANS_5, 120, AMO6_SCREEN_ROW2_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "1");
  
    CleO.Tag(amo6_screen_enable_output3);
    CleO.RectangleColor(amo3_enable[2] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW4_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW4_H-AMO6_SCREEN_OFFSET);
    if (!amo3_save_flag)
      strcpy(text_buf, amo3_enable[2]? "ON" : "OFF");
    else
      strcpy(text_buf, "Saved");
    CleO.StringExt(FONT_SANS_5, 120, AMO6_SCREEN_ROW4_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "3");

    CleO.Tag(amo6_screen_enable_output2);
    CleO.RectangleColor(amo3_enable[1] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW2_H-3*AMO6_SCREEN_OFFSET);
    if (!amo3_save_flag)
      strcpy(text_buf, amo3_enable[1]? "ON" : "OFF");
    else
      strcpy(text_buf, "Saved");
    CleO.StringExt(FONT_SANS_5, 360, AMO6_SCREEN_ROW2_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "2");
  
    CleO.Tag(amo6_screen_enable_output4);
    CleO.RectangleColor(amo3_enable[3] ? MY_GREEN : MY_RED);
    CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW4_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW4_H-AMO6_SCREEN_OFFSET);
    if (!amo3_save_flag)
      strcpy(text_buf, amo3_enable[3]? "ON" : "OFF");
    else
      strcpy(text_buf, "Saved");
    CleO.StringExt(FONT_SANS_5, 360, AMO6_SCREEN_ROW4_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "4");
  }
  else{
    // Draw the Power Fault Strings
    CleO.RectangleColor(MY_RED);
    CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW2_H-3*AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_3, 120, AMO6_SCREEN_ROW2_Y-15, amo6_screen_text_color, MM, 0, 0, "POWER");
    CleO.StringExt(FONT_SANS_3, 120, AMO6_SCREEN_ROW2_Y+15, amo6_screen_text_color, MM, 0, 0, "FAULT");
    CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "1");

    CleO.RectangleXY(120-2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW4_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW4_H-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_3, 120, AMO6_SCREEN_ROW4_Y-15, amo6_screen_text_color, MM, 0, 0, "POWER");
    CleO.StringExt(FONT_SANS_3, 120, AMO6_SCREEN_ROW4_Y+15, amo6_screen_text_color, MM, 0, 0, "FAULT");
    CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "3");

    CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW2_H-3*AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_3, 360, AMO6_SCREEN_ROW2_Y-15, amo6_screen_text_color, MM, 0, 0, "POWER");
    CleO.StringExt(FONT_SANS_3, 360, AMO6_SCREEN_ROW2_Y+15, amo6_screen_text_color, MM, 0, 0, "FAULT");
    CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "2");

    CleO.RectangleXY(360+2*AMO6_SCREEN_OFFSET, AMO6_SCREEN_ROW4_Y+AMO6_SCREEN_OFFSET, 240, AMO6_SCREEN_ROW4_H-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_3, 360, AMO6_SCREEN_ROW4_Y-15, amo6_screen_text_color, MM, 0, 0, "POWER");
    CleO.StringExt(FONT_SANS_3, 360, AMO6_SCREEN_ROW4_Y+15, amo6_screen_text_color, MM, 0, 0, "FAULT");
    CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "4");
  }

  // Update Screen
  CleO.Show();
}

void amo6_screen_touch ()
{
  amo6_screen_processButtons();
  if (amo6_screen_short_press_detected) amo6_screen_processShortPress();
}

void amo6_screen_processButtons ()
{
  // Collet Tags
  //NOTE: for more than 13 tags, you must manually tag!
  CleO.TouchCoordinates(amo6_screen_x, amo6_screen_y, amo6_screen_current_dur, amo6_screen_current_tag);
  
  // Process Short Press
  amo6_screen_shortPress(&amo6_screen_short_press_detected);
  amo6_screen_last_dur = amo6_screen_current_dur;
}

void amo6_screen_shortPress (bool *press_detected)
{
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
  if(!amo3_tec_state)
    return;
  
  switch (amo6_screen_current_tag) {
    case amo6_screen_voltage_output1	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_voltage_output1];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++)amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_voltage_output1] = sel;
      break;
    case amo6_screen_enable_output1	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      amo3_enable[0] = !amo3_enable[0];
      for(i=0;i<amo6_screen_voltage_output1;i++) amo6_screen_select[i]=0;
      for(i=amo6_screen_voltage_output1+1;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      break;
    case amo6_screen_voltage_output2	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_voltage_output2];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_voltage_output2] = sel;
      break;
    case amo6_screen_enable_output2	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      amo3_enable[1] = !amo3_enable[1];
      for(i=0;i<amo6_screen_voltage_output2;i++) amo6_screen_select[i]=0;
      for(i=amo6_screen_voltage_output2+1;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      break;
    case amo6_screen_voltage_output3	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_voltage_output3];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_voltage_output3] = sel;
      break;
    case amo6_screen_enable_output3	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      amo3_enable[2] = !amo3_enable[2];
      for(i=0;i<amo6_screen_voltage_output3;i++) amo6_screen_select[i]=0;
      for(i=amo6_screen_voltage_output3+1;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      break;
    case amo6_screen_voltage_output4	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_voltage_output4];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_voltage_output4] = sel;
      break;
    case amo6_screen_enable_output4	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      amo3_enable[3] = !amo3_enable[3];
      for(i=0;i<amo6_screen_voltage_output4;i++) amo6_screen_select[i]=0;
      for(i=amo6_screen_voltage_output4+1;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      break;
  }
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

#endif // AMO3_H
