#ifndef AMO2_H
#define AMO2_H 1

#include <math.h>

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
uint8_t   amo2_fault = 0;
uint32_t  amo2_temp = 0;
void amo2_init ();
void amo2_process_fault ();
void amo2_execute ();

// VT
const float amo2_vt_uv_to_cnts = 0.0131072;
uint16_t amo2_vt_cnts_max = 65535;
uint32_t amo2_vt_uv = 123456;
double amo2_vt_degC = 25;
double amo2_vt_degC_prev = 0;
AD5541   amo2_VT_dac(SPI_FLEX_AMO2_VT);
void amo2_VT_init ();
void amo2_VT_set_uv (uint32_t val);
void amo2_VT_set_degC (float degC);

// VILM
const float amo2_vilm_ma_to_cnts = 0.65536;
uint16_t amo2_vilm_ma = 123;
double amo2_vilm_amps = 0;
double amo2_vilm_amps_prev = 0;
AD5621   amo2_VILM_dac(SPI_FLEX_AMO2_VILM);
void amo2_VILM_init ();
void amo2_VILM_set_ma (uint16_t val);

// PID
uint8_t amo2_pid_p=128;
uint8_t amo2_pid_p_prev = 0;
uint8_t amo2_pid_i=128;
uint8_t amo2_pid_i_prev = 0;
uint8_t amo2_pid_d=128;
uint8_t amo2_pid_d_prev = 0;
AD5290   amo2_PID_rpot(SPI_FLEX_AMO2_PID);
void amo2_PID_init ();
void amo2_PID_set_cnts (uint8_t p, uint8_t i, uint8_t d);

// VPp
const float amo2_vpp_cnts_to_uv = 76.29395;
uint16_t amo2_vpp_cnts_max = 65535;
uint32_t amo2_vpp_uv = 0;
double amo2_vpp_degC = 0;
MAX11100 amo2_VPP_adc(SPI_FLEX_AMO2_VPP);
void amo2_VPP_init();
uint32_t amo2_VPP_read_uv ();
double amo2_VPP_read_degC ();

// FET
const float amo2_fet_cnts_to_mv = 3.476743;
const float amo2_fet_cnts_to_ma = 4.34593;
uint32_t amo2_fet_mv;
uint32_t amo2_fet_ma;
uint32_t amo2_fet_mw;
bool amo2_fet_bridge;
AD7921   amo2_FET_adc(SPI_FLEX_AMO2_FET);
void amo2_FET_init ();
uint32_t amo2_FET_read ();
uint32_t amo2_FET_read_mw ();

// Heater

// Boost

// Buttons
static int8_t amo6_encoder_val = 0;
//static char amo2_sw1_pushed = 0;
//static char amo2_sw2_pushed = 0;
void amo6_buttons_init ();

// Screen
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
uint32_t amo1_screen_text_color = MY_BLACK;
uint32_t amo1_screen_line_color = MY_DARKBLUE;

enum {
  amo2_screen_null_tag	       , // 0
  amo2_screen_temp_set_tag     , // 1
  amo2_screen_temp_min_tag     , // 2
  amo2_screen_temp_max_tag     , // 3
  amo2_screen_sensor_tag       , // 4
  amo2_screen_sensor_temp_tag  , // 5
  amo2_screen_tec_ilimit_tag   , // 6
  amo2_screen_pid_p_tag        , // 7
  amo2_screen_pid_i_tag        , // 8
  amo2_screen_pid_d_tag        , // 9
  amo2_screen_tec_heater_tag   , // 10
  amo2_screen_tec_boost_tag    , // 11
  amo2_screen_enable_tag       , // 12
};

#define AMO2_SCREEN_TAGS	13
bool amo2_screen_select[AMO2_SCREEN_TAGS];

enum {
  AMO6_SCREEN_TOUCH 	,	//0
};

int16_t amo1_screen_x, amo1_screen_y;
int16_t amo1_screen_current_dur;
int amo1_screen_last_dur = 0;
int16_t amo1_screen_current_tag;
bool amo1_screen_short_press_detected = 0;

void amo2_screen_debug ();
void amo2_screen_init ();
void amo2_screen_refresh ();
void amo2_screen_draw ();
void amo2_screen_touch ();
void amo2_screen_processButtons ();
void amo2_screen_shortPress (bool *press_detected);
void amo2_screen_processShortPress ();

void amo2_screen_execute ();

//////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////

// AMO2
void amo2_init()
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
  amo2_screen_init();
  amo6_buttons_init();
//  _delay_ms(5000);
}

void amo2_process_fault()
{
}

void amo2_execute()
{
  if((amo2_pid_p!=amo2_pid_p_prev)||(amo2_pid_i!=amo2_pid_i_prev)||(amo2_pid_d!=amo2_pid_d_prev)) {
    amo2_PID_set_cnts(amo2_pid_p, amo2_pid_i, amo2_pid_d);
    amo2_pid_p_prev=amo2_pid_p;
    amo2_pid_i_prev=amo2_pid_i;
    amo2_pid_d_prev=amo2_pid_d;
  }
  if(amo2_vt_degC!=amo2_vt_degC_prev) {
    amo2_VT_set_degC(amo2_vt_degC);
    amo2_vt_degC_prev=amo2_vt_degC;
  }
  if(amo2_vilm_amps!=amo2_vilm_amps_prev) {
    amo2_VILM_set_ma(amo2_vilm_amps*1000);
    amo2_vilm_amps_prev=amo2_vilm_amps;
  }
}

//VT
void amo2_VT_init()
{
  amo2_VT_dac.setCounts(32768); //mid
  
  // testing
  //amo2_VT_dac.setcounts(0);     //low
  //amo2_VT_dac.setcounts(32768); //mid
  //amo2_VT_dac.setcounts(65535); //high
}

void amo2_VT_set_uv(uint32_t val)
{
  amo2_vt_uv = val;
  val = amo2_vt_uv * amo2_vt_uv_to_cnts;
  if (val > 65535) val = 65535;
  amo2_VT_dac.setCounts(val);
}

void amo2_VT_set_degC(float degC)
{
  uint16_t r_ref = 20000;
  float r25c = 10103.9;
  float beta = 3813.85;
  float r = r25c * exp(beta*(1/(degC+273.15)-1/298.15));
  r = (r/r_ref+1);
  if (r<1) r=1;
  uint32_t counts = amo2_vt_cnts_max / r;
  //amo2_temp = counts;
  amo2_VT_dac.setCounts(counts);
}

//VILM
void amo2_VILM_init()
{
  amo2_VILM_dac.setCounts(0); //low
  
  // testing
  //amo2_VILM_dac.setCounts(0);    //low
  //amo2_VILM_dac.setCounts(2048); //mid
  //amo2_VILM_dac.setCounts(4095); //high
  //amo2_VILM_dac.setCounts(820);  //1.25A
}

void amo2_VILM_set_ma(uint16_t val)
{
  amo2_vilm_ma = val;
  val = amo2_vilm_ma * amo2_vilm_ma_to_cnts;
  if (val > 4095) val = 4095;
  amo2_VILM_dac.setCounts(val);
}

//PID
void amo2_PID_init()
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

void amo2_PID_set_cnts(uint8_t p, uint8_t i, uint8_t d)
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
void amo2_VPP_init()
{
}

uint32_t amo2_VPP_read_uv()
{
  uint32_t val = amo2_VPP_adc.readCounts();
  amo2_vpp_uv = val * amo2_vpp_cnts_to_uv;
  return amo2_vpp_uv;
}

double amo2_VPP_read_degC()
{
  // NTCALUG02A103F constants from -5C to 35C
  double a = 0.001135517850;
  double b = 0.0002330724285;
  double c = 0.00000009192831104;
  uint16_t r_ref = 20000;
  
  // calculate temperature
  double val = amo2_VPP_adc.readCounts();
  val = log((amo2_vpp_cnts_max/val-1)*r_ref);
  //amo2_vpp_degC = val;
  //amo2_vpp_degC = (a+b*val+c*val*val*val);
  amo2_vpp_degC = 1/(a+b*val+c*val*val*val)-273.15;
  return amo2_vpp_degC;
}

//FET
void amo2_FET_init()
{
  // testing
  //amo2_FET_adc.readCounts();
}

uint32_t amo2_FET_read_mw()
{
  uint32_t val = amo2_FET_adc.readCounts();
  amo2_fet_ma = (val & 0xFFF) * amo2_fet_cnts_to_ma;
  amo2_fet_mv = ((val>>16) & 0xFFF) * amo2_fet_cnts_to_mv;
  amo2_fet_mw = (amo2_fet_ma * amo2_fet_mv)/1000;
  amo2_fet_bridge = (AMO2_BRIDGE_PIN >> AMO2_BRIDGE) & 0x01;
  return amo2_fet_mw;
}

//Buttons
void amo6_buttons_init()
{
  // ENC_A
  DDRD   &= ~_BV(PD2);   //input
  PORTD  |=  _BV(PD2);   //enable pullup
  EICRA  |=  _BV(ISC20); //enable any edge interrupt
  EIMSK  |=  _BV(INT2);  //enable interrupt

  // ENC_B
  DDRD   &= ~_BV(PD1);   //input
  PORTD  |=  _BV(PD1);   //enable pullup
  EICRA  |=  _BV(ISC10); //enable any edge interrupt
  EIMSK  |=  _BV(INT1);  //enable interrupt
  
  // ENC_SW
  DDRD   &= ~_BV(PD3);   //input
  PORTD  |=  _BV(PD3);   //enable pullup
  EICRA  |=  _BV(ISC31); //enable falling edge interrupt
  EIMSK  |=  _BV(INT3);  //enable interrupt
  
  // SW1
  DDRB   &= ~_BV(PB6);   //input
  PORTB  |=  _BV(PB6);   //enable pullup
  
  // SW2
  DDRB   &= ~_BV(PB5);   //input
  PORTB  |=  _BV(PB5);   //enable pullup
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

//Screen
void amo2_screen_debug()
{
  printf("CleO Version = %d\n", CleO.Version());
  printf("CleO ID = %d\n", CleO.ModuleIdentifier());
  CleO.Noop();
  printf("CleO Noop() Echo = %d\n", CleO.Echo());
  //printf("spi_flex_read_byte = 0x%x\n", spi_flex_read_byte(0));
  //printf("spi_flex_read_write_byte = 0x%x\n", spi_flex_read_write_byte(0, 0x8e));
}

void amo2_screen_init()
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
  sprintf(buf_text,"TEC Temperature Controller");
  CleO.StringExt(FONT_SANS_4, AMO6_SCREEN_W/2, 30, amo1_screen_text_color, MM, 0, 0, buf_text);
  sprintf(buf_text,"Device ID : AMO2");
  CleO.StringExt(FONT_BIT_3, 10, 100, amo1_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Hardware ID : 0.0.0");
  CleO.StringExt(FONT_BIT_3 , 10 , 120 , amo1_screen_text_color , ML , 0 , 0, buf_text);
  sprintf(buf_text,"Firmware ID : 0.0.0");
  CleO.StringExt(FONT_BIT_3, 10, 140, amo1_screen_text_color, ML, 0, 0, buf_text);
//  sprintf(buf_text,"%lu,%2.2f,%0.5f,%lu", amo1_iout_max_set_ua/1000, amo1_iout_res, amo1_iout_ua_to_cnts, amo1_pfet_max_mw);
  CleO.StringExt(FONT_BIT_3, 10, 180, amo1_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Starting Up ... ");
  CleO.StringExt(FONT_BIT_4 , 10 , 220 , amo1_screen_text_color , ML , 0 , 0, buf_text);
  CleO.Show();
  
  CleO.DisplayRotate(2, 0);
  CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo2_screen_refresh()
{
    amo2_screen_draw();
    amo2_screen_touch();
}

#define AMO6_SCREEN_ROW1_Y	45
#define AMO6_SCREEN_ROW1_H	90
#define AMO6_SCREEN_ROW2_Y	125
#define AMO6_SCREEN_ROW2_H	70
#define AMO6_SCREEN_ROW3_Y	195
#define AMO6_SCREEN_ROW3_H	70
#define AMO6_SCREEN_ROW4_Y	275
#define AMO6_SCREEN_ROW4_H	90

void amo2_screen_draw()
{ 
  char text_buf[50];
    
  // Start Drawing Screen
  CleO.Start();
  CleO.LineWidth(1);
  CleO.RectangleJustification(MM);
  CleO.LineColor(amo1_screen_line_color);
    
  // Temperature Set
  CleO.Tag(amo2_screen_temp_set_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_temp_set_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(150, AMO6_SCREEN_ROW1_Y, 300, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%02.3f C", amo2_vt_degC);
  CleO.StringExt(FONT_SANS_6, 150, AMO6_SCREEN_ROW1_Y, amo1_screen_text_color, MM, 0, 0, text_buf);
  CleO.Line(300, 0, 300, AMO6_SCREEN_ROW1_H);
    
  // Temperature Min
  CleO.Tag(amo2_screen_temp_min_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_temp_min_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleXY(345, AMO6_SCREEN_ROW1_Y, 90, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%d", amo2_screen_select[amo2_screen_temp_min_tag]);
  CleO.StringExt(FONT_SANS_6 , 345, AMO6_SCREEN_ROW1_Y, amo1_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(390, 0, 390, AMO6_SCREEN_ROW1_H);
    
  // Temperature Max
  CleO.Tag(amo2_screen_temp_max_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_temp_max_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(435, AMO6_SCREEN_ROW1_Y, 90, AMO6_SCREEN_ROW1_H);
  sprintf(text_buf, "%d", amo2_screen_select[amo2_screen_temp_max_tag]);
  CleO.StringExt(FONT_SANS_6 , 435, AMO6_SCREEN_ROW1_Y, amo1_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(0, AMO6_SCREEN_ROW1_Y+AMO6_SCREEN_ROW1_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW1_Y+AMO6_SCREEN_ROW1_H/2);
    
  // Sensor Type
  CleO.Tag(amo2_screen_sensor_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_sensor_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(50, AMO6_SCREEN_ROW2_Y, 100, AMO6_SCREEN_ROW2_H);
  //sprintf(text_buf, "%d", amo2_screen_sensor_sel);
  CleO.StringExt(FONT_SANS_2 , 50, 125, amo1_screen_text_color , MM , 0 , 0, "NTC10K");
  CleO.Line(100, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2, 100, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
    
  // Sensor Temperature
  CleO.Tag(amo2_screen_sensor_temp_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_sensor_temp_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleXY(200, AMO6_SCREEN_ROW2_Y, 200, AMO6_SCREEN_ROW2_H);
  //sprintf(text_buf, "%lu", amo2_vpp_uv);
  sprintf(text_buf, "%03.3f C", amo2_vpp_degC);
  CleO.StringExt(FONT_SANS_4 , 300-20, AMO6_SCREEN_ROW2_Y, amo1_screen_text_color, MR, 0, 0, text_buf);
  CleO.CircleExt(300-43, AMO6_SCREEN_ROW2_Y-15, 3, 4, amo1_screen_text_color, MM, 0, 0); //BUG: froze the program
  CleO.Line(300, AMO6_SCREEN_ROW2_Y-AMO6_SCREEN_ROW2_H/2, 300, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // TEC iLimit
  CleO.Tag(amo2_screen_tec_ilimit_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_tec_ilimit_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(390, AMO6_SCREEN_ROW2_Y, 180, AMO6_SCREEN_ROW2_H);
  sprintf(text_buf, "%1.1f A", amo2_vilm_amps);
  CleO.StringExt(FONT_SANS_5 , 390, AMO6_SCREEN_ROW2_Y, amo1_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(0, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW2_Y+AMO6_SCREEN_ROW2_H/2);
  
  // PID P
  CleO.Tag(amo2_screen_pid_p_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_pid_p_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(50, AMO6_SCREEN_ROW3_Y, 100, AMO6_SCREEN_ROW3_H);
  CleO.StringExt(FONT_SANS_3 , 5, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2+5, amo1_screen_text_color, TL, 0, 0, "P");
  sprintf(text_buf, "%d", amo2_pid_p);
  CleO.StringExt(FONT_SANS_5 , 50+4, AMO6_SCREEN_ROW3_Y+6, amo1_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(100, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 100, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // PID I
  CleO.Tag(amo2_screen_pid_i_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_pid_i_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleXY(150, AMO6_SCREEN_ROW3_Y, 100, AMO6_SCREEN_ROW3_H);
  CleO.StringExt(FONT_SANS_3 , 105, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2+6, amo1_screen_text_color, TL, 0, 0, "I");
  sprintf(text_buf, "%d", amo2_pid_i);
  CleO.StringExt(FONT_SANS_5 , 150+4, AMO6_SCREEN_ROW3_Y+5, amo1_screen_text_color , MM , 0 , 0, text_buf);
  CleO.Line(200, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 200, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // PID D
  CleO.Tag(amo2_screen_pid_d_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_pid_d_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(250, AMO6_SCREEN_ROW3_Y, 100, AMO6_SCREEN_ROW3_H);
  CleO.StringExt(FONT_SANS_3 , 205, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2+6, amo1_screen_text_color, TL, 0, 0, "D");
  sprintf(text_buf, "%d", amo2_pid_d);
  CleO.StringExt(FONT_SANS_5 , 250+4, AMO6_SCREEN_ROW3_Y+5, amo1_screen_text_color, MM, 0 , 0, text_buf);
  CleO.Line(300, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 300, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Heater
  CleO.Tag(amo2_screen_tec_heater_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_tec_heater_tag] ? MY_GREEN : MY_YELLOW);
  CleO.RectangleXY(345, AMO6_SCREEN_ROW3_Y, 90, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%d", amo2_screen_tec_heater_sel);
  CleO.StringExt(FONT_SANS_3 , 345, AMO6_SCREEN_ROW3_Y, amo1_screen_text_color , MM , 0 , 0, "Heater");
  CleO.Line(390, AMO6_SCREEN_ROW3_Y-AMO6_SCREEN_ROW3_H/2, 390, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Boost
  CleO.Tag(amo2_screen_tec_boost_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_tec_boost_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(435, AMO6_SCREEN_ROW3_Y, 90, AMO6_SCREEN_ROW3_H);
  //sprintf(text_buf, "%d", amo2_screen_tec_boost_sel);
  CleO.StringExt(FONT_SANS_3 , 435, AMO6_SCREEN_ROW3_Y, amo1_screen_text_color , MM , 0 , 0, "Boost");
  CleO.Line(0, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2, AMO6_SCREEN_W, AMO6_SCREEN_ROW3_Y+AMO6_SCREEN_ROW3_H/2);
  
  // Enable
  CleO.Tag(amo2_screen_enable_tag);
  CleO.RectangleColor(amo2_screen_select[amo2_screen_enable_tag] ? MY_GREEN : MY_WHITE);
  CleO.RectangleXY(240, AMO6_SCREEN_ROW4_Y, 480, AMO6_SCREEN_ROW4_H);
  //sprintf(text_buf, "%d", amo2_screen_enable_sel);
  sprintf(text_buf, "vf=%lu, if=%lu, mwf=%lu, heat=%d", amo2_fet_mv, amo2_fet_ma, amo2_fet_mw, amo2_fet_bridge); 
  CleO.StringExt(FONT_SANS_3 , 240, AMO6_SCREEN_ROW4_Y, amo1_screen_text_color , MM , 0 , 0, text_buf);
  
  // Update Screen
  CleO.Show();
}

void amo2_screen_touch()
{
  if (amo2_fault==0) {
    amo2_screen_processButtons();
    if (amo1_screen_short_press_detected) amo2_screen_processShortPress();
  }
}

void amo2_screen_processButtons()
{
  // Collet Tags
  //NOTE: for more than 13 tags, you must manually tag!
  CleO.TouchCoordinates(amo1_screen_x, amo1_screen_y, amo1_screen_current_dur, amo1_screen_current_tag);
  
  // Process Short Press
  amo2_screen_shortPress(&amo1_screen_short_press_detected);
  amo1_screen_last_dur = amo1_screen_current_dur;
}

void amo2_screen_shortPress (bool *press_detected)
{
  if (amo1_screen_current_dur==1 && amo1_screen_last_dur==0 && !*press_detected) {
    *press_detected = 1;
    //SerialUSB.println("Short press!");
  }
  else {
    *press_detected = 0;
  }
}

void amo2_screen_processShortPress() {
  int i;
  bool sel;

  switch (amo1_screen_current_tag) {
    case amo2_screen_temp_set_tag	:
      sel = !amo2_screen_select[amo2_screen_temp_set_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_temp_set_tag] = sel;
      break;
    case amo2_screen_temp_min_tag	:
      sel = !amo2_screen_select[amo2_screen_temp_min_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_temp_min_tag] = sel;
      break;
    case amo2_screen_temp_max_tag	:
      sel = !amo2_screen_select[amo2_screen_temp_max_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_temp_max_tag] = sel;
      break;
    case amo2_screen_sensor_tag	:
      sel = !amo2_screen_select[amo2_screen_sensor_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_sensor_tag] = sel;
      break;
    case amo2_screen_sensor_temp_tag	:
      sel = !amo2_screen_select[amo2_screen_sensor_temp_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_sensor_temp_tag] = sel;
      break;
    case amo2_screen_tec_ilimit_tag	:
      sel = !amo2_screen_select[amo2_screen_tec_ilimit_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_tec_ilimit_tag] = sel;
      break;
    case amo2_screen_pid_p_tag	:
      sel = !amo2_screen_select[amo2_screen_pid_p_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_pid_p_tag] = sel;
      break;
    case amo2_screen_pid_i_tag	:
      sel = !amo2_screen_select[amo2_screen_pid_i_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_pid_i_tag] = sel;
      break;
    case amo2_screen_pid_d_tag	:
      sel = !amo2_screen_select[amo2_screen_pid_d_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_pid_d_tag] = sel;
      break;
    case amo2_screen_tec_heater_tag	:
      sel = !amo2_screen_select[amo2_screen_tec_heater_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_tec_heater_tag] = sel;
      break;
    case amo2_screen_tec_boost_tag	:
      sel = !amo2_screen_select[amo2_screen_tec_boost_tag];
      for(i=0;i<AMO2_SCREEN_TAGS-1;i++) amo2_screen_select[i]=0;
      amo2_screen_select[amo2_screen_tec_boost_tag] = sel;
      break;
    case amo2_screen_enable_tag	:
      sel = !amo2_screen_select[amo2_screen_enable_tag];
      amo2_screen_select[amo2_screen_enable_tag] = sel;
      break;
  }
}

void amo2_screen_execute() 
{
  int i;
  float tmp;
  
  // encoder turn
  static int8_t amo6_encoder_val_prev;
  if (amo6_encoder_val_prev == amo6_encoder_val) {
    amo6_encoder_val = 0;
  }
  else {
    for (i=0;i<AMO2_SCREEN_TAGS-1;i++) {
      if (amo2_screen_select[i]==1) break;
    }
    int8_t val = amo6_encoder_val - amo6_encoder_val_prev;
    switch (i) {
      case amo2_screen_temp_set_tag	:
	tmp = amo2_vt_degC + val*0.1;
	if (tmp>35) tmp=35;
	if (tmp<-5) tmp=-5;
	amo2_vt_degC = tmp;
	break;
      case amo2_screen_temp_min_tag	:
	break;
      case amo2_screen_temp_max_tag	:
	break;
      case amo2_screen_sensor_tag	:
	break;
      case amo2_screen_sensor_temp_tag	:
	break;
      case amo2_screen_tec_ilimit_tag	:
	tmp = amo2_vilm_amps + val*0.1;
	if (tmp>5) tmp=5;
	if (tmp<0) tmp=0;
	amo2_vilm_amps = tmp;
	break;
      case amo2_screen_pid_p_tag	:
	tmp = amo2_pid_p + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_p = tmp;
	break;
      case amo2_screen_pid_i_tag	:
	tmp = amo2_pid_i + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_i = tmp;
	break;
      case amo2_screen_pid_d_tag	:
	tmp = amo2_pid_d + val;
	if (tmp>255) tmp=255;
	if (tmp<0) tmp=0;
	amo2_pid_d = tmp;
	break;
      case amo2_screen_tec_heater_tag	:
	break;
      case amo2_screen_tec_boost_tag	:
	break;
    }
    amo6_encoder_val_prev = 0;
    amo6_encoder_val = 0;
  }
}

#endif // AMO2_H