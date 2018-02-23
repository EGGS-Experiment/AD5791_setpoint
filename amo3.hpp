/* Changes:
 * user interface screen is now a 4 output Voltage Settings
 * hardware startup stage only loads screen (no PID_init and such)
 * removed PID/Temp Control/etc. tags from amo_screen_select array
 * outputs and enable information are stored in the following arrays: 
 *	amo2_voltage [4]
 *	enable [4]
 *	Indices: 0 - top left
 *		 1 - top right
 *		 2 - bottom left
 *		 3 - bottom right
 * added //(+) //(end +) comments before and after all new code
*/ 

#ifndef AMO3_H
#define AMO3_H 1

#include <stdlib.h>
#include <math.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////
// Tracking
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "Piezo Controller";
const char device_id[]   = "AMO3";
const char hardware_id[] = "0.0.0";
const char firmware_id[] = "0.0.0";

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

// internal variables (amo3)
double amo3_voltage_out[4] = {0.0, 0.0, 0.0, 0.0}; 
bool enable[4] = {false, false, false, false};

void amo3_init ();
void amo3_fault_check ();
void amo3_hardware_update ();

// VOUT
// PREVIOUS: const float amo3_vout_mv_to_cnts = 0.0131072;
const float amo3_vout_mv_to_cnts[4] = {0.4369,0.4369,0.4369,0.4369};
uint16_t amo3_vout_cnts_max = 65535;
uint32_t amo3_vout_mv = 123456;
uint32_t amo3_mv_latched[4] = {0,0,0,0};
AD5544   amo3_VOUT_dac(SPI_FLEX_AMO3_VOUT);

void amo3_VOUT_init ();
void amo3_VOUT_set_mv (uint32_t val, uint32_t dac);

// Buttons (AMO6)
static int8_t amo6_encoder_val = 0;
static bool amo6_sw1_pushed = false;
static bool amo6_sw2_pushed = false;
static bool count_latch [2] = {false, false};
uint8_t hold_count [2] = {0, 0};
const uint8_t hold_threshold = 5;

void amo6_buttons_init ();
void amo6_buttons_update ();

// Serial (AMO6)
const int amo6_serial_buffer_size = 100;
char amo6_serial_buffer[amo6_serial_buffer_size+1];
char amo6_serial_string[amo6_serial_buffer_size+1];

void amo6_serial_update ();
void amo6_serial_parse ();

// Screen (AMO6)
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

int16_t amo6_screen_x, amo6_screen_y;
int16_t amo6_screen_current_dur;
int amo6_screen_last_dur = 0;
int16_t amo6_screen_current_tag;
bool amo6_screen_short_press_detected = 0;

void amo6_screen_debug ();
void amo6_screen_init ();
void amo6_screen_update ();
void amo6_screen_draw ();
void amo6_screen_touch ();
void amo6_screen_processButtons ();
void amo6_screen_shortPress (bool *press_detected);
void amo6_screen_processShortPress ();

//////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////

//AMO3 
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
  amo3_VOUT_init();

  amo6_screen_init();
  amo6_buttons_init();
  _delay_ms(5000);
}

void amo3_fault_check ()
{
  // TODO: THIS FUNCTION IS EMPTY!
}

void amo3_hardware_update ()
{
  // sends voltage values
  uint8_t i;
  for (i=0;i<4;++i){
/*
    if (enable[i]){
      val = amo3_voltage_out[i]*1000.0;
    }
    else {
      val = 0;
    }
*/
    uint32_t val = (enable[i])? (amo3_voltage_out[i]*1000.0) : 0;
    if (val != amo3_mv_latched[i]){
      amo3_mv_latched[i] = val;
      amo3_VOUT_set_mv(val, i);
    }
  }
}

void amo3_VOUT_init ()
{
  // TODO: THIS FUNCTION IS EMPTY!

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

//Buttons (AMO6)
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
  float max_V = 150.000;
  
  for (tag=0;tag<AMO6_SCREEN_TAGS-1;tag++) { //find active screen tag
    if (amo6_screen_select[tag]==1) break;
  };
  
  // sw1 pressed
  if (amo6_sw1_pushed) {
    count_latch[0] = true; // start counting hold time
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
    amo6_sw1_pushed = false;
  }
  
  // sw2 pressed
  if (amo6_sw2_pushed) {
    count_latch[1] = true; // start counting hold time
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
    amo6_sw2_pushed = false;
  }

  // sw2 held
  if (count_latch[1]){
    if (hold_count[1] < hold_threshold)
      ++(hold_count[1]);
    if (hold_count[1] >= hold_threshold){
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
      hold_count[1] = 0;
    }
    if (sw2_now){
      count_latch[1] = false;
      hold_count[1] = 0;
    }
  }

  // sw1 held
  if (count_latch[0]){
    if (hold_count[0] < hold_threshold)
      ++(hold_count[0]);
    if (hold_count[0] >= hold_threshold){
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
      hold_count[0] = 0;
    }
    if (sw1_now){
      count_latch[0] = false;
      hold_count[0] = 0;
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

//Serial (AMO6)
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
  
  if(strcmp(token[0],"id?")==0) {
    if(i==1) {
      printf("%s\n", device_name);
      printf("Device ID : %s\n", device_id);
      printf("Hardware ID : %s\n", hardware_id);
      printf("Firmware ID : %s\n", firmware_id);
    }
  }
  else {
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

void amo6_screen_draw ()
{ 
  // Start Drawing Screen
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.LineColor(amo6_screen_line_color);

  char text_buf[50];

  CleO.Tag(amo6_screen_voltage_output1);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output1] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(120, AMO6_SCREEN_ROW1_Y, 240, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[0]);
  CleO.StringExt(FONT_SANS_6, 200, AMO6_SCREEN_ROW1_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 220, AMO6_SCREEN_ROW1_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW1_Y-30, amo6_screen_text_color, MM, 0, 0, "1");
  
  CleO.Tag(amo6_screen_enable_output1);
  CleO.RectangleColor(enable[0] ? MY_GREEN : MY_RED);
  CleO.RectangleXY(120, AMO6_SCREEN_ROW2_Y, 240, AMO6_SCREEN_ROW2_H);
  strcpy(text_buf, enable[0]? "ON" : "OFF");
  CleO.StringExt(FONT_SANS_5, 120, AMO6_SCREEN_ROW2_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "1");

  CleO.Tag(amo6_screen_voltage_output3);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output3] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(120, AMO6_SCREEN_ROW3_Y, 240, AMO6_SCREEN_ROW3_H);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[2]);
  CleO.StringExt(FONT_SANS_6, 200, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 220, AMO6_SCREEN_ROW3_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW3_Y-30, amo6_screen_text_color, MM, 0, 0, "3");
  
  CleO.Tag(amo6_screen_enable_output3);
  CleO.RectangleColor(enable[2] ? MY_GREEN : MY_RED);
  CleO.RectangleXY(120, AMO6_SCREEN_ROW4_Y, 240, AMO6_SCREEN_ROW4_H);
  strcpy(text_buf, enable[2]? "ON" : "OFF");
  CleO.StringExt(FONT_SANS_5, 120, AMO6_SCREEN_ROW4_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_2, 228, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "3");

  CleO.Tag(amo6_screen_voltage_output2);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output2] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(360, AMO6_SCREEN_ROW1_Y, 240, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[1]);
  CleO.StringExt(FONT_SANS_6, 440, AMO6_SCREEN_ROW1_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 460, AMO6_SCREEN_ROW1_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW1_Y-30, amo6_screen_text_color, MM, 0, 0, "2");
  
  CleO.Tag(amo6_screen_enable_output2);
  CleO.RectangleColor(enable[1] ? MY_GREEN : MY_RED);
  CleO.RectangleXY(360, AMO6_SCREEN_ROW2_Y, 240, AMO6_SCREEN_ROW2_H);
  strcpy(text_buf, enable[1]? "ON" : "OFF");
  CleO.StringExt(FONT_SANS_5, 360, AMO6_SCREEN_ROW2_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW2_Y-20, amo6_screen_text_color, MM, 0, 0, "2");

  CleO.Tag(amo6_screen_voltage_output4);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_voltage_output4] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(360, AMO6_SCREEN_ROW3_Y, 240, AMO6_SCREEN_ROW3_H);
  sprintf(text_buf, "%3.3f", amo3_voltage_out[3]);
  CleO.StringExt(FONT_SANS_6, 440, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_4, 460, AMO6_SCREEN_ROW3_Y+8, amo6_screen_text_color, MM, 0, 0, "V");
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW3_Y-30, amo6_screen_text_color, MM, 0, 0, "4");
  
  CleO.Tag(amo6_screen_enable_output4);
  CleO.RectangleColor(enable[3] ? MY_GREEN : MY_RED);
  CleO.RectangleXY(360, AMO6_SCREEN_ROW4_Y, 240, AMO6_SCREEN_ROW4_H);
  strcpy(text_buf, enable[3]? "ON" : "OFF");
  CleO.StringExt(FONT_SANS_5, 360, AMO6_SCREEN_ROW4_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
  CleO.StringExt(FONT_SANS_2, 468, AMO6_SCREEN_ROW4_Y-20, amo6_screen_text_color, MM, 0, 0, "4");

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
      enable[0] = !enable[0];
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
      enable[1] = !enable[1];
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
      enable[2] = !enable[2];
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
      enable[3] = !enable[3];
      for(i=0;i<amo6_screen_voltage_output4;i++) amo6_screen_select[i]=0;
      for(i=amo6_screen_voltage_output4+1;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      break;
  }
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

#endif // AMO2_H
