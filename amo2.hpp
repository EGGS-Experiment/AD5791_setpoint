#ifndef AMO2_H
#define AMO2_H 1

#include <stdlib.h>
#include <math.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////
// Tracking
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "TEC Temperature Controller";
const char device_id[]   = "AMO2";
const char hardware_id[] = "0.0.0";
const char firmware_id[] = "0.0.6";

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

#define AMO2_PWR_nOK		PK0
#define AMO2_PWR_nOK_PIN   	PINK
#define AMO2_PWR_nOK_DDR   	DDRK
#define AMO2_PWR_nOK_PORT  	PORTK

#define AMO2_SW1		PK2
#define AMO2_SW1_DDR   		DDRK
#define AMO2_SW1_PORT  		PORTK

#define AMO2_SW2		PK4
#define AMO2_SW2_DDR   		DDRK
#define AMO2_SW2_PORT  		PORTK

#define AMO2_SW3		PA6
#define AMO2_SW3_DDR   		DDRA
#define AMO2_SW3_PORT  		PORTA

#define AMO2_SW4		PA4
#define AMO2_SW4_DDR   		DDRA
#define AMO2_SW4_PORT  		PORTA

#define AMO2_SW5		PA2
#define AMO2_SW5_DDR   		DDRA
#define AMO2_SW5_PORT  		PORTA

#define AMO2_SW6		PJ5
#define AMO2_SW6_DDR   		DDRJ
#define AMO2_SW6_PORT  		PORTJ

#define AMO2_SW7		PJ7
#define AMO2_SW7_DDR   		DDRJ
#define AMO2_SW7_PORT  		PORTJ

#define AMO2_SW8		PK6
#define AMO2_SW8_DDR   		DDRK
#define AMO2_SW8_PORT  		PORTK

#define AMO2_SW9		PA0
#define AMO2_SW9_DDR   		DDRA
#define AMO2_SW9_PORT  		PORTA

#define AMO2_HEAT		PH6
#define AMO2_HEAT_DDR   	DDRH
#define AMO2_HEAT_PORT  	PORTH

#define AMO2_GDRV_BOOST		PH7
#define AMO2_GDRV_BOOST_DDR   	DDRH
#define AMO2_GDRV_BOOST_PORT  	PORTH

#define AMO2_TEMP_OK		PH4
#define AMO2_TEMP_OK_PIN   	PINH
#define AMO2_TEMP_OK_DDR   	DDRH
#define AMO2_TEMP_OK_PORT  	PORTH

#define AMO2_BRIDGE		PH5
#define AMO2_BRIDGE_PIN   	PINH
#define AMO2_BRIDGE_DDR   	DDRH
#define AMO2_BRIDGE_PORT  	PORTH

// AMO2
uint32_t  amo2_temp = 0;
bool amo2_tec_state = false;
bool amo2_tec_state_latched = false;
enum{
  amo2_fault_none		, //0
  amo2_fault_sensor		, //1
  amo2_fault_tec		, //2
  amo2_fault_tec_pol		, //3
  amo2_fault_tec_open		, //4
};
const char* amo2_fault_string[] = {
  "TEC Off"				,
  "Sensor Out of Range"		,
  "TEC Current Out of Range"    ,
  "TEC Polarity Reversed"	,
  "TEC Not Connected"		,
};
uint8_t amo2_fault = amo2_fault_none;
uint8_t amo2_fault_prev = amo2_fault_none;
const float amo2_fault_check_degC_delta = 0.2;
bool amo2_fault_check_tec_pol = false;

void amo2_init ();
void amo2_fault_check ();
void amo2_hardware_update ();

// Sensor
//  NTCALUG02A103F constants from 10C to 35C
uint16_t amo2_sensor_r_ref = 20000;
double amo2_sensor_r25c = 10000.0;
double amo2_sensor_beta = 3862.14;
double amo2_sensor_a = 0.001136099080;
double amo2_sensor_b = 0.0002329786514;
double amo2_sensor_c = 0.00000009228611999;
//  NTCALUG02A103F constants from -5C to 35C
//uint16_t amo2_sensor_r_ref = 20000;
//double amo2_sensor_r25c = 10103.9;
//double amo2_sensor_beta = 3813.85;
//double amo2_sensor_a = 0.001135517850;
//double amo2_sensor_b = 0.0002330724285;
//double amo2_sensor_c = 0.00000009192831104;

// VT
const float amo2_vt_uv_to_cnts = 0.0131072;
uint16_t amo2_vt_cnts_max = 65535;
uint32_t amo2_vt_uv = 123456;
double amo2_vt_degC = 25; //initial value
double amo2_vt_degC_latched = -1000;
int amo2_vt_degC_max = 35;
int amo2_vt_degC_min = 10;
AD5541   amo2_VT_dac(SPI_FLEX_AMO2_VT);

void amo2_VT_init ();
void amo2_VT_set_uv (uint32_t val);
void amo2_VT_set_degC (float degC);

// VILM
const float amo2_vilm_ma_to_cnts = 0.07091;
uint16_t amo2_vilm_ma = 123;
double amo2_vilm_amps = 5; //initial value
double amo2_vilm_amps_latched = 0;
int amo2_vilm_amps_max = 5;
AD5621   amo2_VILM_dac(SPI_FLEX_AMO2_VILM);

void amo2_VILM_init ();
void amo2_VILM_set_ma (uint16_t val);

// PID
uint8_t amo2_pid_p=100; //initial value
uint8_t amo2_pid_p_latched = 0;
uint8_t amo2_pid_i=16; //initial value
uint8_t amo2_pid_i_latched = 0;
uint8_t amo2_pid_d=16; //initial value
uint8_t amo2_pid_d_latched = 0;
AD5290   amo2_PID_rpot(SPI_FLEX_AMO2_PID);

void amo2_PID_init ();
void amo2_PID_set_cnts (uint8_t p, uint8_t i, uint8_t d);

// VPp
const float amo2_vpp_cnts_to_uv = 76.29395;
uint16_t amo2_vpp_cnts_max = 65535;
uint32_t amo2_vpp_uv = 0;
double amo2_vpp_degC = 0;
double amo2_vpp_degC_start = 0;
MAX11100 amo2_VPP_adc(SPI_FLEX_AMO2_VPP);

void amo2_VPP_init();
uint32_t amo2_VPP_read_uv ();
double amo2_VPP_read_degC ();

// FET
const float amo2_fet_cnts_to_mv = 3.476743;
const float amo2_fet_cnts_to_ma = 40.1657;
const uint32_t amo2_fet_vtec_mv = 5000;
uint32_t amo2_fet_mv;
uint32_t amo2_fet_ma;
uint32_t amo2_fet_mw;
bool amo2_fet_bridge;
AD7921   amo2_FET_adc(SPI_FLEX_AMO2_FET);

void amo2_FET_init ();
uint32_t amo2_FET_read_mw ();

// Heater

// Boost

// Buttons (AMO6)
static int8_t amo6_encoder_val = 0;
static bool amo6_sw1_pushed = false;
static bool amo6_sw2_pushed = false;

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
  amo6_screen_null_tag	       , // 0
  amo6_screen_temp_set_tag     , // 1
  amo6_screen_temp_min_tag     , // 2
  amo6_screen_temp_max_tag     , // 3
  amo6_screen_sensor_tag       , // 4
  amo6_screen_sensor_temp_tag  , // 5
  amo6_screen_tec_ilimit_tag   , // 6
  amo6_screen_pid_p_tag        , // 7
  amo6_screen_pid_i_tag        , // 8
  amo6_screen_pid_d_tag        , // 9
  amo6_screen_tec_heater_tag   , // 10
  amo6_screen_tec_boost_tag    , // 11
  amo6_screen_enable_tag       , // 12
  amo6_screen_last_tag         , // 13
};
#define AMO6_SCREEN_TAGS	14
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

//AMO2 
void amo2_init ()
{
  // hardware i/o config
  AMO6_CLEO_nPWR_DDR  |=  _BV(AMO6_CLEO_nPWR);//output
  AMO6_CLEO_nPWR_PORT |=  _BV(AMO6_CLEO_nPWR); //1
  
  AMO2_PWR_nOK_DDR  &= ~_BV(AMO2_PWR_nOK); //input
  AMO2_PWR_nOK_PORT &= ~_BV(AMO2_PWR_nOK); //disable pullup
  amo2_VT_dac.init();
  amo2_VILM_dac.init();
  amo2_PID_rpot.init();
  amo2_VPP_adc.init();
  amo2_FET_adc.init();
  AMO2_SW1_DDR  |=  _BV(AMO2_SW1); //output
  AMO2_SW1_PORT &= ~_BV(AMO2_SW1); //0
  AMO2_SW2_DDR  |=  _BV(AMO2_SW2); //output
  AMO2_SW2_PORT |=  _BV(AMO2_SW2); //1
  AMO2_SW3_DDR  |=  _BV(AMO2_SW3); //output
  AMO2_SW3_PORT &= ~_BV(AMO2_SW3); //0
  AMO2_SW4_DDR  |=  _BV(AMO2_SW4); //output
  AMO2_SW4_PORT &= ~_BV(AMO2_SW4); //0
  AMO2_SW5_DDR  |=  _BV(AMO2_SW5); //output
  AMO2_SW5_PORT &= ~_BV(AMO2_SW5); //0
  AMO2_SW6_DDR  |=  _BV(AMO2_SW6); //output
  AMO2_SW6_PORT &= ~_BV(AMO2_SW6); //0
  AMO2_SW7_DDR  |=  _BV(AMO2_SW7); //output
  AMO2_SW7_PORT &= ~_BV(AMO2_SW7); //0
  AMO2_SW8_DDR  |=  _BV(AMO2_SW8); //output
  AMO2_SW8_PORT &= ~_BV(AMO2_SW8); //0
  AMO2_SW9_DDR  |=  _BV(AMO2_SW9); //output
  AMO2_SW9_PORT &= ~_BV(AMO2_SW9); //0
  
  AMO2_HEAT_DDR |=  _BV(AMO2_HEAT);  //output
  AMO2_HEAT_PORT &= ~_BV(AMO2_HEAT); //0
  AMO2_GDRV_BOOST_DDR |=  _BV(AMO2_GDRV_BOOST);  //output
  AMO2_GDRV_BOOST_PORT &= ~_BV(AMO2_GDRV_BOOST); //0
  AMO2_TEMP_OK_DDR  &= ~_BV(AMO2_TEMP_OK); //input
  AMO2_TEMP_OK_PORT &= ~_BV(AMO2_TEMP_OK); //disable pullup
  AMO2_BRIDGE_DDR  &= ~_BV(AMO2_BRIDGE); //input
  AMO2_BRIDGE_PORT &= ~_BV(AMO2_BRIDGE); //disable pullup
  
  AMO6_EXT1_nEN_DDR  |=  _BV(AMO6_EXT1_nEN); //output
  AMO6_EXT1_nEN_PORT &= ~_BV(AMO6_EXT1_nEN); //0
  AMO6_EXT2_nEN_DDR  |=  _BV(AMO6_EXT2_nEN); //output
  AMO6_EXT2_nEN_PORT &= ~_BV(AMO6_EXT2_nEN); //0
  AMO6_BUZZER_nEN_DDR  |=  _BV(AMO6_BUZZER_nEN); //output
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
  
  // hardware init
  amo2_VT_init();
  amo2_VILM_init();
  amo2_PID_init();
  amo2_VPP_init();
  amo2_FET_init();
  amo6_screen_init();
  amo6_buttons_init();
//  _delay_ms(5000);
}

void amo2_fault_check ()
{
  if ((amo2_vpp_degC>(amo2_vt_degC_max+2)) || (amo2_vpp_degC<(amo2_vt_degC_min-2))) {
    amo2_fault = amo2_fault_sensor;
    amo2_fault_prev = amo2_fault_sensor;
    if ( amo2_tec_state_latched) {
      amo2_VILM_set_ma(0);
      amo2_tec_state = false;
    }
  }
  else if(amo2_fet_ma>((amo2_vilm_amps+1)*1000)) {
    amo2_fault = amo2_fault_tec;
    amo2_fault_prev = amo2_fault_tec;
    if ( amo2_tec_state_latched) {
      amo2_VILM_set_ma(0);
      amo2_tec_state = false;
    }
  }
  else if(amo2_tec_state_latched) {
    if(amo2_fet_mv==0 && amo2_fet_ma==0) {
      amo2_fault = amo2_fault_tec_open;
      amo2_fault_prev = amo2_fault_tec_open;
      amo2_VILM_set_ma(0);
      amo2_tec_state = false;
    }
    else if(amo2_fault_check_tec_pol) {
      if(amo2_vt_degC_latched > amo2_vpp_degC_start) {
        if((amo2_vpp_degC_start-amo2_vpp_degC)>amo2_fault_check_degC_delta) {
	  amo2_fault = amo2_fault_tec_pol;
          amo2_fault_prev = amo2_fault_tec_pol;
	  amo2_VILM_set_ma(0);
          amo2_tec_state = false;
	  amo2_fault_check_tec_pol = false;
        }
        else if((amo2_vpp_degC-amo2_vpp_degC_start)>amo2_fault_check_degC_delta) {
	  amo2_fault_check_tec_pol = false;
        }
      }
      else {
        if((amo2_vpp_degC-amo2_vpp_degC_start)>amo2_fault_check_degC_delta) {
	  amo2_fault = amo2_fault_tec_pol;
          amo2_fault_prev = amo2_fault_tec_pol;
	  amo2_VILM_set_ma(0);
          amo2_tec_state = false;
	  amo2_fault_check_tec_pol = false;
        }
        else if((amo2_vpp_degC_start-amo2_vpp_degC)>amo2_fault_check_degC_delta) {
	  amo2_fault_check_tec_pol = false;
        }
      }
    }
  }
  else {
    amo2_fault = amo2_fault_none;
    if (amo2_fault_prev == amo2_fault_sensor) amo2_fault_prev = amo2_fault_none; //clear previous error from screen
  }
}

void amo2_hardware_update ()
{
  if((amo2_pid_p!=amo2_pid_p_latched)||(amo2_pid_i!=amo2_pid_i_latched)||(amo2_pid_d!=amo2_pid_d_latched)) { //PID
    amo2_PID_set_cnts(amo2_pid_p, amo2_pid_i, amo2_pid_d);
    amo2_pid_p_latched=amo2_pid_p;
    amo2_pid_i_latched=amo2_pid_i;
    amo2_pid_d_latched=amo2_pid_d;
  }
  if(amo2_vt_degC!=amo2_vt_degC_latched) { //vt
    amo2_VT_set_degC(amo2_vt_degC);
    amo2_vt_degC_latched=amo2_vt_degC;
  }
  if(amo2_vilm_amps!=amo2_vilm_amps_latched) { //vilm
    if ((amo2_tec_state) && (amo2_fault==amo2_fault_none)) amo2_VILM_set_ma(amo2_vilm_amps*1000); //change only when TEC is on
    amo2_vilm_amps_latched=amo2_vilm_amps;
  }
  if(amo2_tec_state != amo2_tec_state_latched) { //tec on/off
    if ((amo2_tec_state) && (amo2_fault==amo2_fault_none)) {
      amo2_fault_check_tec_pol = true;
      amo2_vpp_degC_start = amo2_vpp_degC;
      amo2_VILM_set_ma(amo2_vilm_amps*1000);
    }
    else {
      amo2_fault_check_tec_pol = false;
      amo2_VILM_set_ma(0);
      amo2_tec_state = false;
    }
    amo2_tec_state_latched = amo2_tec_state;
  }
}

//VT
void amo2_VT_init ()
{
  amo2_VT_dac.setCounts(32768); //mid
  //amo2_VT_dac.setCounts(0); //offset test
  
  // testing
  //amo2_VT_dac.setcounts(0);     //low
  //amo2_VT_dac.setcounts(32768); //mid
  //amo2_VT_dac.setcounts(65535); //high
}

void amo2_VT_set_uv (uint32_t val)
{
  amo2_vt_uv = val;
  val = amo2_vt_uv * amo2_vt_uv_to_cnts;
  if (val > 65535) val = 65535;
  amo2_VT_dac.setCounts(val);
}

void amo2_VT_set_degC (float degC)
{
  float r = amo2_sensor_r25c * exp(amo2_sensor_beta*(1/(degC+273.15)-1/298.15));
  r = (r/amo2_sensor_r_ref+1);
  if (r<1) r=1;
  uint32_t counts = amo2_vt_cnts_max / r;
  amo2_VT_dac.setCounts(counts);
  //amo2_VT_dac.setCounts(0); //offset test
}

//VILM
void amo2_VILM_init ()
{
  amo2_VILM_dac.setCounts(0); //low
  
  // testing
  //amo2_VILM_dac.setCounts(0);    //low
  //amo2_VILM_dac.setCounts(2048); //mid
  //amo2_VILM_dac.setCounts(4095); //high
  //amo2_VILM_dac.setCounts(820);  //1.25A
}

void amo2_VILM_set_ma (uint16_t val)
{
  amo2_vilm_ma = val;
  val = amo2_vilm_ma * amo2_vilm_ma_to_cnts;
  if (val > 4095) val = 4095;
  amo2_VILM_dac.setCounts(val);
}

//PID
void amo2_PID_init ()
{
  amo2_PID_rpot.setCounts(0x000000); //low
  
  // testing
  //amo2_PID_rpot.setCounts(0x000000); //low
  //amo2_PID_rpot.setCounts(0x808080); //mid
  //amo2_PID_set_cnts(128, 128, 128); //mid
  //amo2_PID_rpot.setCounts(0xFFFFFF); //high
  //amo2_PID_rpot.setCounts(0xFF8000); //P=FF I=80 D=00
  //amo2_PID_rpot.setCounts(0x808000); //P=80 I=90 D=00
  
}

void amo2_PID_set_cnts (uint8_t p, uint8_t i, uint8_t d)
{
  amo2_pid_p = p;
  amo2_pid_i = i;
  amo2_pid_d = d;
  uint32_t val = p & 0xFF;
  val = val << 8;
  val |= i & 0xFF;
  val = val << 8;
  val |= d & 0xFF; 
  amo2_PID_rpot.setCounts(val);
}

//VPp
void amo2_VPP_init ()
{
}

uint32_t amo2_VPP_read_uv ()
{
  uint32_t val = amo2_VPP_adc.readCounts();
  amo2_vpp_uv = val * amo2_vpp_cnts_to_uv;
  return amo2_vpp_uv;
}

double amo2_VPP_read_degC ()
{
  // calculate temperature
  double val = amo2_VPP_adc.readCounts();
  val = log((amo2_vpp_cnts_max/val-1)*amo2_sensor_r_ref);
  //amo2_vpp_degC = val;
  //amo2_vpp_degC = (a+b*val+c*val*val*val);
  amo2_vpp_degC = 1/(amo2_sensor_a+amo2_sensor_b*val+amo2_sensor_c*val*val*val)-273.15;
  return amo2_vpp_degC;
}

//FET
void amo2_FET_init ()
{
  // testing
  //amo2_FET_adc.readCounts();
}

uint32_t amo2_FET_read_mw ()
{
  static uint8_t size = 5;
  static uint8_t idx = 0;
  static uint32_t amo2_fet_ma_buf[5];
  static uint32_t amo2_fet_mv_buf[5];
  
  uint32_t val = amo2_FET_adc.readCounts();
  //amo2_fet_ma = (val & 0xFFF) * amo2_fet_cnts_to_ma;
  //amo2_fet_mv = ((val>>16) & 0xFFF) * amo2_fet_cnts_to_mv;
  
  if (idx>=size) idx=0;
  amo2_fet_ma_buf[idx] = (val & 0xFFF) * amo2_fet_cnts_to_ma;
  amo2_fet_mv_buf[idx] = ((val>>16) & 0xFFF) * amo2_fet_cnts_to_mv;
  idx++;
  
  amo2_fet_ma = 0;
  amo2_fet_mv = 0;
  uint8_t i = 0;
  for (i=0;i<size;i++) {
    amo2_fet_ma += amo2_fet_ma_buf[i];
    amo2_fet_mv += amo2_fet_mv_buf[i];
  }
  amo2_fet_ma = amo2_fet_ma/size;
  amo2_fet_mv = amo2_fet_mv/size;
  if(amo2_fet_mv > amo2_fet_vtec_mv) amo2_fet_mv=amo2_fet_vtec_mv;
  
  amo2_fet_mw = (amo2_fet_ma * amo2_fet_mv)/1000;
  amo2_fet_bridge = (AMO2_BRIDGE_PIN >> AMO2_BRIDGE) & 0x01;
  return amo2_fet_mw;
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
  
  for (tag=0;tag<AMO6_SCREEN_TAGS-1;tag++) { //find active screen tag
    if (amo6_screen_select[tag]==1) break;
  };
  
  // sw1 pressed
  if (amo6_sw1_pushed) {
    if (!sw1_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
      switch (tag) {
        case amo6_screen_temp_set_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = (int) amo2_vt_degC - 1;
	  if (tmp>amo2_vt_degC_max) tmp=amo2_vt_degC_max;
	  if (tmp<amo2_vt_degC_min) tmp=amo2_vt_degC_min;
	  amo2_vt_degC = tmp;
	  break;
        case amo6_screen_temp_min_tag	:
	  break;
        case amo6_screen_temp_max_tag	:
	  break;
        case amo6_screen_sensor_tag	:
	  break;
        case amo6_screen_sensor_temp_tag	:
	  break;
        case amo6_screen_tec_ilimit_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_vilm_amps - 1;
	  if (tmp>amo2_vilm_amps_max) tmp=amo2_vilm_amps_max;
	  if (tmp<0) tmp=0;
	  amo2_vilm_amps = tmp;
	  break;
        case amo6_screen_pid_p_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_p - 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_p = tmp;
	  break;
        case amo6_screen_pid_i_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_i - 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_i = tmp;
	  break;
        case amo6_screen_pid_d_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_d - 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_d = tmp;
	  break;
        case amo6_screen_tec_heater_tag	:
	  break;
        case amo6_screen_tec_boost_tag	:
	  break;
      }
      AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
    }
    amo6_sw1_pushed = false;
  }
  
  // sw2 pressed
  if (amo6_sw2_pushed) {
    if (!sw2_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
      switch (tag) {
        case amo6_screen_temp_set_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = (int) amo2_vt_degC + 1;
	  if (tmp>amo2_vt_degC_max) tmp=amo2_vt_degC_max;
	  if (tmp<amo2_vt_degC_min) tmp=amo2_vt_degC_min;
	  amo2_vt_degC = tmp;
	  break;
        case amo6_screen_temp_min_tag	:
	  break;
        case amo6_screen_temp_max_tag	:
	  break;
        case amo6_screen_sensor_tag	:
	  break;
        case amo6_screen_sensor_temp_tag	:
	  break;
        case amo6_screen_tec_ilimit_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_vilm_amps + 1;
	  if (tmp>amo2_vilm_amps_max) tmp=amo2_vilm_amps_max;
	  if (tmp<0) tmp=0;
	  amo2_vilm_amps = tmp;
	  break;
        case amo6_screen_pid_p_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_p + 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_p = tmp;
	  break;
        case amo6_screen_pid_i_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_i + 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_i = tmp;
	  break;
        case amo6_screen_pid_d_tag	:
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(5);
	  tmp = amo2_pid_d + 10;
	  if (tmp>255) tmp=255;
	  if (tmp<0) tmp=0;
	  amo2_pid_d = tmp;
	  break;
        case amo6_screen_tec_heater_tag	:
	  break;
        case amo6_screen_tec_boost_tag	:
	  break;
      }
      AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
    }
    amo6_sw2_pushed = false;
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
      case amo6_screen_temp_set_tag	:
	val = val/4;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo2_vt_degC + val*0.005;
	if (tmp>amo2_vt_degC_max) tmp=amo2_vt_degC_max;
	if (tmp<amo2_vt_degC_min) tmp=amo2_vt_degC_min;
	amo2_vt_degC = tmp;
	break;
      case amo6_screen_temp_min_tag	:
	break;
      case amo6_screen_temp_max_tag	:
	break;
      case amo6_screen_sensor_tag	:
	break;
      case amo6_screen_sensor_temp_tag	:
	break;
      case amo6_screen_tec_ilimit_tag	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo2_vilm_amps + val*0.1;
	if (tmp>amo2_vilm_amps_max) tmp=amo2_vilm_amps_max;
	if (tmp<0) tmp=0;
	amo2_vilm_amps = tmp;
	break;
      case amo6_screen_pid_p_tag	:
	_delay_ms(1);
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo2_pid_p + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_p = tmp;
	break;
      case amo6_screen_pid_i_tag	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo2_pid_i + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_i = tmp;
	break;
      case amo6_screen_pid_d_tag	:
	val = val/10;
	if (val!=0) {
	  AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
	  _delay_ms(1);
	}
	tmp = amo2_pid_d + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_d = tmp;
	break;
      case amo6_screen_tec_heater_tag	:
	break;
      case amo6_screen_tec_boost_tag	:
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
  float tmp;
  
  token[0] = strtok(amo6_serial_string, delimiters);
  i++;
  while(i<8) {
    token[i] = strtok (NULL, delimiters);
    if(token[i] == NULL) break;
    i++;
  }
  
  if(strcmp(token[0],"out.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if(tmp==0) {
	if ( amo2_tec_state_latched) amo2_tec_state = false;
      }
      else if(tmp==1) {
        if ((!amo2_tec_state_latched) && (amo2_fault==amo2_fault_none)) { //only when prev state is off and no faults
	  amo2_tec_state = true; 
	  amo2_fault_prev = amo2_fault_none;
        }
      }
    }
  }
  else if(strcmp(token[0],"iout.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if (tmp>amo2_vilm_amps_max) tmp=amo2_vilm_amps_max;
      if (tmp<0) tmp=0;
      amo2_vilm_amps = tmp;
    }
  }
  else if(strcmp(token[0],"temp.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if (tmp>amo2_vt_degC_max) tmp=amo2_vt_degC_max;
      if (tmp<amo2_vt_degC_min) tmp=amo2_vt_degC_min;
      amo2_vt_degC = tmp;
    }
  }
  else if(strcmp(token[0],"temp.r")==0) {
    if(i==1) {
      printf("temp = %03.3f C\n", amo2_vpp_degC);
    }
  }
  else if(strcmp(token[0],"p.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if (tmp>255) tmp=255;
      if (tmp<0) tmp=0;
      amo2_pid_p = tmp;
    }
  }
  else if(strcmp(token[0],"i.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if (tmp>255) tmp=255;
      if (tmp<0) tmp=0;
      amo2_pid_i = tmp;
    }
  }
  else if(strcmp(token[0],"d.w")==0) {
    if(i==2) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      tmp=atof(token[1]);
      if (tmp>255) tmp=255;
      if (tmp<0) tmp=0;
      amo2_pid_d = tmp;
    }
  }
  else if(strcmp(token[0],"sensor.r")==0) {
    if(i==1) {
      printf("r_ref=%u, r25c=%f, beta=%f, a=%0.10f, b=%0.10f, c=%0.10f\n", amo2_sensor_r_ref, amo2_sensor_r25c, amo2_sensor_beta, amo2_sensor_a*1000, amo2_sensor_b*10000, amo2_sensor_c*10000000);
    }
  }
  else if(strcmp(token[0],"sensor.w")==0) {
    if(i==7) {
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      if ( amo2_tec_state_latched) amo2_tec_state = false;
      amo2_sensor_r_ref = atof(token[1]);
      amo2_sensor_r25c  = atof(token[2]);
      amo2_sensor_beta  = atof(token[3]);
      amo2_sensor_a     = atof(token[4])/1000;
      amo2_sensor_b     = atof(token[5])/10000;
      amo2_sensor_c     = atof(token[6])/10000000;
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
#define AMO6_SCREEN_ROW3_Y	195
#define AMO6_SCREEN_ROW3_H	70
#define AMO6_SCREEN_ROW4_Y	275
#define AMO6_SCREEN_ROW4_H	90

void amo6_screen_draw ()
{ 
  char text_buf[50];
    
  // Start Drawing Screen
  CleO.Start();
  CleO.LineWidth(1);
  CleO.RectangleJustification(MM);
  CleO.LineColor(amo6_screen_line_color);
    
  // Temperature Set
  CleO.Tag(amo6_screen_temp_set_tag);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_temp_set_tag] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(150, AMO6_SCREEN_ROW1_Y, 300, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%02.3f C", amo2_vt_degC);
  CleO.StringExt(FONT_SANS_6, 150, AMO6_SCREEN_ROW1_Y, amo6_screen_text_color, MM, 0, 0, text_buf);
  CleO.Line(300, 0, 300, AMO6_SCREEN_ROW1_H);
    
  // Temperature Min
  CleO.Tag(amo6_screen_temp_min_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_temp_min_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleColor(MY_WHITE);
  CleO.RectangleXY(345, AMO6_SCREEN_ROW1_Y, 90, AMO6_SCREEN_ROW1_H);
  CleO.StringExt(FONT_SANS_4 , 345, AMO6_SCREEN_ROW1_Y-20, amo6_screen_text_color , MM , 0 , 0, "min");
  sprintf(text_buf, "%d C", amo2_vt_degC_min);
  CleO.StringExt(FONT_SANS_4 , 345, AMO6_SCREEN_ROW1_Y+20, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(390, 0, 390, AMO6_SCREEN_ROW1_H);
    
  // Temperature Max
  CleO.Tag(amo6_screen_temp_max_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_temp_max_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleColor(MY_WHITE);
  CleO.RectangleXY(435, AMO6_SCREEN_ROW1_Y, 90, AMO6_SCREEN_ROW1_H);
  CleO.StringExt(FONT_SANS_4 , 435, AMO6_SCREEN_ROW1_Y-20, amo6_screen_text_color , MM , 0 , 0, "max");
  sprintf(text_buf, "%d C", amo2_vt_degC_max);
  CleO.StringExt(FONT_SANS_4 , 435, AMO6_SCREEN_ROW1_Y+20, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(0, AMO6_SCREEN_ROW1_Y+AMO6_SCREEN_ROW1_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW1_Y+AMO6_SCREEN_ROW1_H/2);
  
  // PID P
  CleO.Tag(amo6_screen_pid_p_tag);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_pid_p_tag] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(50, AMO6_SCREEN_ROW2_Y, 100, AMO6_SCREEN_ROW2_H);
  CleO.StringExt(FONT_SANS_3 , 5, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2+5, amo6_screen_text_color, TL, 0, 0, "P");
  sprintf(text_buf, "%d", amo2_pid_p);
  CleO.StringExt(FONT_SANS_5 , 50+4, AMO6_SCREEN_ROW2_Y+6, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(100, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2, 100, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // PID I
  CleO.Tag(amo6_screen_pid_i_tag);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_pid_i_tag] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(150, AMO6_SCREEN_ROW2_Y, 100, AMO6_SCREEN_ROW2_H);
  CleO.StringExt(FONT_SANS_3 , 105, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2+6, amo6_screen_text_color, TL, 0, 0, "I");
  sprintf(text_buf, "%d", amo2_pid_i);
  CleO.StringExt(FONT_SANS_5 , 150+4, AMO6_SCREEN_ROW2_Y+5, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(200, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2, 200, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // PID D
  CleO.Tag(amo6_screen_pid_d_tag);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_pid_d_tag] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(250, AMO6_SCREEN_ROW2_Y, 100, AMO6_SCREEN_ROW2_H);
  CleO.StringExt(FONT_SANS_3 , 205, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2+6, amo6_screen_text_color, TL, 0, 0, "D");
  sprintf(text_buf, "%d", amo2_pid_d);
  CleO.StringExt(FONT_SANS_5 , 250+4, AMO6_SCREEN_ROW2_Y+5, amo6_screen_text_color, MM, 0 , 0, text_buf);
  CleO.Line(300, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2, 300, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // TEC iLimit
  CleO.Tag(amo6_screen_tec_ilimit_tag);
  CleO.RectangleColor(amo6_screen_select[amo6_screen_tec_ilimit_tag] ? CLEO_SELECT : MY_WHITE);
  CleO.RectangleXY(390, AMO6_SCREEN_ROW2_Y, 180, AMO6_SCREEN_ROW2_H);
  sprintf(text_buf, "%1.2f A", amo2_vilm_amps);
  CleO.StringExt(FONT_SANS_5 , 390, AMO6_SCREEN_ROW2_Y, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(0, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // Sensor Type
  CleO.Tag(amo6_screen_sensor_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_sensor_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleColor(MY_WHITE);
  CleO.RectangleXY(50, AMO6_SCREEN_ROW3_Y, 100, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%d", amo6_screen_sensor_sel);
  CleO.StringExt(FONT_SANS_2 , 50, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color , MM , 0 , 0, "NTC10K");
  CleO.Line(100, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 100, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
    
  // Sensor Temperature
  CleO.Tag(amo6_screen_sensor_temp_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_sensor_temp_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleColor(MY_YELLOW);
  CleO.RectangleXY(200, AMO6_SCREEN_ROW3_Y, 200, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%lu", amo2_vpp_uv);
  sprintf(text_buf, "%03.3f C", amo2_vpp_degC);
  CleO.StringExt(FONT_SANS_4 , 300-20, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color, MR, 0, 0, text_buf);
  CleO.CircleExt(300-43, AMO6_SCREEN_ROW3_Y-15, 3, 4, amo6_screen_text_color, MM, 0, 0); //BUG: froze the program
  CleO.Line(300, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 300, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Heater or Debug
  CleO.Tag(amo6_screen_tec_heater_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_tec_heater_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleColor(MY_WHITE);
  CleO.RectangleXY(345, AMO6_SCREEN_ROW3_Y, 90, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%d", amo6_screen_select[amo6_screen_tec_heater_tag]);
  //sprintf(text_buf, "%d", amo6_screen_current_tag);
  //sprintf(text_buf, "%lu", amo2_temp);
  //CleO.StringExt(FONT_SANS_3 , 345, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(390, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 390, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Boost
  CleO.Tag(amo6_screen_tec_boost_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_tec_boost_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleColor(MY_WHITE);
  CleO.RectangleXY(435, AMO6_SCREEN_ROW3_Y, 90, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%d", amo6_screen_tec_boost_sel);
  //CleO.StringExt(FONT_SANS_3 , 435, AMO6_SCREEN_ROW3_Y, amo6_screen_text_color , MM , 0 , 0, "Boost");
  CleO.Line(0, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Enable
  CleO.Tag(amo6_screen_enable_tag);
  //CleO.RectangleColor(amo6_screen_select[amo6_screen_enable_tag] ? MY_GREEN : MY_RED);
  CleO.RectangleColor(amo2_tec_state ? CLEO_TEC_ON : CLEO_TEC_OFF);
  CleO.RectangleXY(240, AMO6_SCREEN_ROW4_Y, 480, AMO6_SCREEN_ROW4_H);
  //sprintf(text_buf, "%d", amo6_screen_enable_sel);
  if (amo2_tec_state) {
    if(amo2_fet_bridge) sprintf(text_buf, "TEC = %02.2fA, %02.2fV", (double) amo2_fet_ma/1000, (double) (amo2_fet_vtec_mv-amo2_fet_mv)/-1000);
    else                sprintf(text_buf, "TEC = %02.2fA, %02.2fV", (double) amo2_fet_ma/1000, (double) (amo2_fet_vtec_mv-amo2_fet_mv)/1000);
  }
  else {
    sprintf(text_buf, "%s", amo2_fault_string[amo2_fault_prev]);
  }
  CleO.StringExt(FONT_SANS_5, 240, AMO6_SCREEN_ROW4_Y, amo6_screen_text_color , MM , 0 , 0, text_buf);
  
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
    case amo6_screen_temp_set_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_temp_set_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_temp_set_tag] = sel;
      break;
    case amo6_screen_temp_min_tag	:
      sel = !amo6_screen_select[amo6_screen_temp_min_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_temp_min_tag] = sel;
      break;
    case amo6_screen_temp_max_tag	:
      sel = !amo6_screen_select[amo6_screen_temp_max_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_temp_max_tag] = sel;
      break;
    case amo6_screen_sensor_tag	:
      sel = !amo6_screen_select[amo6_screen_sensor_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_sensor_tag] = sel;
      break;
    case amo6_screen_sensor_temp_tag	:
      sel = !amo6_screen_select[amo6_screen_sensor_temp_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_sensor_temp_tag] = sel;
      break;
    case amo6_screen_tec_ilimit_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_tec_ilimit_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_tec_ilimit_tag] = sel;
      break;
    case amo6_screen_pid_p_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_pid_p_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_pid_p_tag] = sel;
      break;
    case amo6_screen_pid_i_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_pid_i_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_pid_i_tag] = sel;
      break;
    case amo6_screen_pid_d_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(2);
      sel = !amo6_screen_select[amo6_screen_pid_d_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_pid_d_tag] = sel;
      break;
    case amo6_screen_tec_heater_tag	:
      sel = !amo6_screen_select[amo6_screen_tec_heater_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_tec_heater_tag] = sel;
      break;
    case amo6_screen_tec_boost_tag	:
      sel = !amo6_screen_select[amo6_screen_tec_boost_tag];
      for(i=0;i<AMO6_SCREEN_TAGS-1;i++) amo6_screen_select[i]=0;
      amo6_screen_select[amo6_screen_tec_boost_tag] = sel;
      break;
    case amo6_screen_enable_tag	:
      AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
      _delay_ms(5);
      if ( amo2_tec_state_latched) amo2_tec_state = false;
      if ((!amo2_tec_state_latched) && (amo2_fault==amo2_fault_none)) { //only when prev state is off and no faults
	amo2_tec_state = true; 
	amo2_fault_prev = amo2_fault_none;
      }
      break;
  }
  AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

#endif // AMO2_H