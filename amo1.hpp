#ifndef AMO1_H
#define AMO1_H 1

//////////////////////////////////////////////////////////////////////////////////////
// Variables & Constants
//////////////////////////////////////////////////////////////////////////////////////

// Core Variables & Constants
#define AMO6_CLEO_PWR		PG0
#define AMO6_CLEO_PWR_DDR	DDRG
#define AMO6_CLEO_PWR_PORT	PORTG

#define AMO6_EXT1_EN		PG1
#define AMO6_EXT1_EN_DDR   	DDRG
#define AMO6_EXT1_EN_PORT  	PORTG

#define AMO1_VDD1_EN		PK3   //17>K3
#define AMO1_VDD1_EN_DDR   	DDRK
#define AMO1_VDD1_EN_PORT  	PORTK
AD5541 amo1_vdd1_dac(SPI_FLEX_AMO1_VDD1);

#define AMO1_OUT_EN		PA7   //05>A7
#define AMO1_OUT_EN_DDR   	DDRA
#define AMO1_OUT_EN_PORT  	PORTA
AD5541 amo1_out_dac(SPI_FLEX_AMO1_IOUT);

#define AMO1_IOUT               PK6   //03>K6>ADC14
#define AMO1_IOUT_DDR   	DDRK
#define AMO1_IOUT_PORT  	PORTK
#define AMO1_IOUT_ADMUX5_	0x08
#define AMO1_IOUT_ADMUX40	0x06

#define AMO1_VOUT               PK7   //01>K7>ADC15
#define AMO1_VOUT_PIN   	PINK
#define AMO1_VOUT_DDR   	DDRK
#define AMO1_VOUT_PORT  	PORTK
#define AMO1_VOUT_ADMUX5_	0x08
#define AMO1_VOUT_ADMUX40	0x07

// |----------+----------+----------|
// |  ADMUX5_ |  ADMUX40 | ADC MUX  |
// |----------+----------+----------|
// |   0x00   |   0x1E   |   1.1V   |
// |----------+----------+----------|
// |   0x00   |   0x1F   |   GND    |
// |----------+----------+----------|
// |   0x08   |   0x06   |  ADC14   |
// |----------+----------+----------|
// |   0x08   |   0x07   |  ADC15   |
// |----------+----------+----------|

#define AMO1_OUT_FET		PA6   //06>A6
#define AMO1_OUT_FET_DDR   	DDRA
#define AMO1_OUT_FET_PORT  	PORTA

#define AMO1_D1_4		PA0   //19>A0
#define AMO1_D1_4_DDR   	DDRA
#define AMO1_D1_4_PORT  	PORTA

#define AMO1_D2_4		PA4   //09>A4
#define AMO1_D2_4_DDR   	DDRA
#define AMO1_D2_4_PORT  	PORTA

uint8_t   amo1_fault = 0;

const uint32_t  amo1_vdd1_max_mv = 11000;
const uint32_t  amo1_vdd1_min_mv = 6000;
const float     amo1_vdd1_mv_to_cnts = 4.35;
const uint32_t  amo1_vdd1_cnts = 65535;

const uint32_t  amo1_iout_max_ua = 250000;
const uint32_t  amo1_iout_max_set_ua = 200000;
const float     amo1_iout_ua_to_cnts = 0.32071;
const uint32_t  amo1_iout_res = 20;
const uint32_t  amo1_iout_cnts = 65535;

const uint32_t  amo1_pfet_iout_trig_ma = 20;  //prevent pfet correction when output is off

const uint32_t  amo1_pfet_max_mw = 200;       //target pfet power when max_trig is trigged
const uint32_t  amo1_pfet_max_trig_mw = 260;  //pfet power trigger, hysteresis = (amo1_pfet_max_trig_mw-amo1_pfet_max_mw) should be above the noise of system
const uint8_t   amo1_pfet_pmax_trig_cnt_max = 2;
uint8_t         amo1_pfet_pmax_trig_cnt = 0;

const uint32_t  amo1_pfet_vdsmin_trig_mv = 1000; //pfet min voltage
const uint8_t   amo1_pfet_vdsmin_trig_cnt_max = 2;
uint8_t         amo1_pfet_vdsmin_trig_cnt = 0;

float     amo1_adc_vref = 0.0;
float     amo1_vout_cnts_to_mv = 0.106813;
float     amo1_iout_cnts_to_mv = 0.005341;

uint32_t  amo1_vout_mv = 0;
uint32_t  amo1_iout_ma = 0;
bool      amo1_out_state = 0;
uint32_t  amo1_prev_iout_ua = 0;
uint32_t  amo1_prev_vdd1_mv = 0;

// Screen Variables & Constants
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

#define AMO1_SCREEN_WIDTH  480
#define AMO1_SCREEN_HEIGHT 320
#define AMO1_SCREEN_NUM_OF_DIGITS 6

int amo1_screen_locationY[9] = {0, 40, 80, 120, 160 ,200 , 240, 280 , 320};
int amo1_screen_locationX[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 480, 480};

uint32_t amo1_screen_text_color = MY_BLACK;
uint32_t amo1_screen_line_color = MY_DARKBLUE;

enum {
    amo1_screen_tag_null    , // 0
    amo1_screen_tag_0i      , // 1
    amo1_screen_tag_1i      , // 2
    amo1_screen_tag_2i      , // 3
    amo1_screen_tag_3i      , // 4
    amo1_screen_tag_4i      , // 5
    amo1_screen_tag_5i      , // 6
    amo1_screen_tag_0d      , // 7
    amo1_screen_tag_1d      , // 8
    amo1_screen_tag_2d      , // 9
    amo1_screen_tag_3d      , // 10
    amo1_screen_tag_4d      , // 11
    amo1_screen_tag_5d      , // 12
    amo1_screen_tag_on      , // 13
};

int16_t amo1_screen_x, amo1_screen_y;
int16_t amo1_screen_current_dur;
int amo1_screen_last_dur = 0;
int16_t amo1_screen_current_tag;
bool amo1_screen_short_press_detected = 0;

int amo1_screen_current[AMO1_SCREEN_NUM_OF_DIGITS] = {0};
bool amo1_screen_pressed[AMO1_SCREEN_NUM_OF_DIGITS * 2] = {0};
bool amo1_screen_on = false;
bool amo1_screen_toggle_on = true;

//////////////////////////////////////////////////////////////////////////////////////
// Member Functions Declaration
//////////////////////////////////////////////////////////////////////////////////////

// Core Functions
void amo1_init();
void amo1_processFault();

// VDD1 DAC Functions
void amo1_initVDD1();
void amo1_adjVDD1();
void amo1_VDD1(bool state);
void amo1_setVDD1mV(uint32_t millivolts);
uint16_t amo1_milliVoltsToCounts(uint32_t millivolts);
void amo1_setVDD1cnts(uint16_t counts);

// OUT DAC Functions
void amo1_initOUT();
//void amo1_setOUT(bool state, uint32_t microamps);
void amo1_setOUT();
void amo1_OUT(bool state);
void amo1_setOUTuA(uint32_t microamps);
uint16_t amo1_microAmpsToCounts(uint32_t microamps);
void amo1_setOUTcnts(uint16_t counts);

// Read Functions
void amo1_initRead();
uint32_t amo1_readIOUTmA();
uint32_t amo1_readVOUTmV();

// Screen Functions
void amo1_screen_debug();
void amo1_screen_init();

void amo1_screen_refresh();
void amo1_screen_draw();

void amo1_screen_processButtons();
void amo1_screen_shortPress (bool *press_detected);
void amo1_screen_processShortPress();

void amo1_screen_increaseSetCurrent(int i);
void amo1_screen_decreaseSetCurrent(int i);

bool amo1_screen_isOn();
uint32_t amo1_screen_getCurrent();

//////////////////////////////////////////////////////////////////////////////////////
// Member Functions Implementation
//////////////////////////////////////////////////////////////////////////////////////

// Core Functions
void amo1_init()
{
  // AMO6 init
  AMO6_CLEO_PWR_DDR  |=  _BV(AMO6_CLEO_PWR);//output
  AMO6_CLEO_PWR_PORT |=  _BV(AMO6_CLEO_PWR); //1
  AMO6_EXT1_EN_DDR  |=  _BV(AMO6_EXT1_EN); //output
  AMO6_EXT1_EN_PORT &= ~_BV(AMO6_EXT1_EN); //0
  
  // AMO1 init
  amo1_initOUT();
  amo1_initVDD1();
  amo1_initRead();
  
  // screen init
  amo1_screen_init();
  
  // AMO1 setup
  amo1_setVDD1mV(amo1_vdd1_min_mv);
  amo1_VDD1(1);
  amo1_setOUTuA(0);
  _delay_ms(5000); //wait for iout to settle before ramping up VDD1
  amo1_setVDD1mV(amo1_vdd1_max_mv);
  amo1_setOUTuA(0); //program one more time to be safe
  
  // AMO1 unused pins
  AMO1_OUT_FET_DDR  |=  _BV(AMO1_OUT_FET); //output
  AMO1_OUT_FET_PORT &= ~_BV(AMO1_OUT_FET); //0
  AMO1_D1_4_DDR  |=  _BV(AMO1_D1_4); //output
  AMO1_D1_4_PORT |=  _BV(AMO1_D1_4); //1
  AMO1_D2_4_DDR  |=  _BV(AMO1_D2_4); //output
  AMO1_D2_4_PORT |=  _BV(AMO1_D2_4); //1
}

void amo1_processFault()
{
  if ((amo1_iout_ma*1000)>amo1_iout_max_ua) amo1_fault = 1;
  else if((amo1_vout_mv > 6990) && (amo1_iout_ma < 10)) amo1_fault = 2;
  else amo1_fault = 0;
  
  uint16_t i;
  if (amo1_fault==1) { //max current fault
    amo1_setOUTuA(0);
    _delay_ms(100);
    amo1_OUT(0);
    amo1_setVDD1mV(amo1_vdd1_max_mv);
    amo1_out_state = 0;
    amo1_screen_on = 0;
    amo1_screen_refresh();
    for(i=0;i<10;i++) _delay_ms(1000);
  }
  else if (amo1_fault==2) { //no diode fault
    amo1_setOUTuA(0);
    _delay_ms(100);
    amo1_OUT(0);
    amo1_setVDD1mV(amo1_vdd1_max_mv);
    amo1_out_state = 0;
    amo1_screen_on = 0;
    amo1_screen_refresh();
    for(i=0;i<5;i++) _delay_ms(1000);
  }
  amo1_fault = 0;
}

// VDD1 Write Functions
void amo1_initVDD1()
{
  AMO1_VDD1_EN_DDR  |=  _BV(AMO1_VDD1_EN); //output
  AMO1_VDD1_EN_PORT &= ~_BV(AMO1_VDD1_EN); //0
  //AMO1_VDD1_EN_PORT |=  _BV(AMO1_VDD1_EN); //1
  amo1_vdd1_dac.init();
  
}

void amo1_adjVDD1()
{
  uint32_t pfet_mw, pfet_mv;
  int32_t vdd1_mv, pfet_dv_mv;
  
  amo1_readIOUTmA();
  amo1_readVOUTmV();
  pfet_mv = amo1_prev_vdd1_mv-amo1_iout_ma*amo1_iout_res-amo1_vout_mv;
  pfet_mw = pfet_mv*amo1_iout_ma/1000;

  if (amo1_iout_ma > amo1_pfet_iout_trig_ma) {
    
    // Check pfet power
    if (pfet_mw > amo1_pfet_max_trig_mw) {
      if (amo1_pfet_pmax_trig_cnt>=amo1_pfet_pmax_trig_cnt_max) {
        pfet_dv_mv = ((pfet_mw-amo1_pfet_max_mw)*1000)/amo1_iout_ma;
        vdd1_mv = amo1_prev_vdd1_mv-pfet_dv_mv;
        if (vdd1_mv>0) {
          amo1_setVDD1mV(vdd1_mv);
          //SerialUSB.println("-- adjVDD1 > amo1_pfet_max_trig_mw > new vdd1 --");
          //SerialUSB.println(amo1_iout_ma);
          //SerialUSB.println(amo1_vout_mv);
          //SerialUSB.println(pfet_mv);
          //SerialUSB.println(pfet_mw);
          //SerialUSB.println(pfet_dv_mv);
          //SerialUSB.println(vdd1_mv);
        }
        amo1_pfet_pmax_trig_cnt=0;
      }
      else amo1_pfet_pmax_trig_cnt++;
    }
    else {
      if (amo1_pfet_pmax_trig_cnt>0) amo1_pfet_pmax_trig_cnt--;
    }
    
    // Check pfet vds voltage
    if (pfet_mv<amo1_pfet_vdsmin_trig_mv) {
      if (amo1_pfet_vdsmin_trig_cnt>=amo1_pfet_vdsmin_trig_cnt_max) {
        //SerialUSB.println("-- adjVDD1 > amo1_pfet_vdsmin_trig_mv > new vdd1 --");
        if (amo1_prev_vdd1_mv<amo1_vdd1_max_mv) amo1_setVDD1mV(amo1_vdd1_max_mv);
        amo1_pfet_vdsmin_trig_cnt=0;
      }
      else amo1_pfet_vdsmin_trig_cnt++;
    }
    else {
      if (amo1_pfet_vdsmin_trig_cnt>0) amo1_pfet_vdsmin_trig_cnt--;
    }
    
  }
  else {
    if (amo1_pfet_pmax_trig_cnt>0)    amo1_pfet_pmax_trig_cnt--;
    if (amo1_pfet_vdsmin_trig_cnt>0)  amo1_pfet_vdsmin_trig_cnt--;
  }
  //SerialUSB.println(amo1_vout_mv);
  //SerialUSB.println(amo1_pfet_pmax_trig_cnt);
  //SerialUSB.println(amo1_pfet_vdsmin_trig_cnt);
}

void amo1_VDD1(bool state)
{
  if (state) AMO1_VDD1_EN_PORT |=  _BV(AMO1_VDD1_EN); //1
  else       AMO1_VDD1_EN_PORT &= ~_BV(AMO1_VDD1_EN); //0
//  controller.setDO(1, state);
}

void amo1_setVDD1mV(uint32_t millivolts)
{
  uint16_t cnts = 0;
  if      (millivolts>amo1_vdd1_max_mv) millivolts=amo1_vdd1_max_mv;
  else if (millivolts<amo1_vdd1_min_mv) millivolts=amo1_vdd1_min_mv;
  cnts = amo1_milliVoltsToCounts(millivolts);
  amo1_setVDD1cnts(cnts);
  amo1_prev_vdd1_mv=millivolts;
}

uint16_t amo1_milliVoltsToCounts(uint32_t millivolts)
{
  float cnts = 0;
  cnts = amo1_vdd1_mv_to_cnts*millivolts;
  if (cnts > amo1_vdd1_cnts) {
    cnts = 0;
  }
  return cnts;
}

void amo1_setVDD1cnts(uint16_t counts)
{
  amo1_vdd1_dac.setCounts(counts);
  //SerialUSB.println(counts);
//  controller.writeDac2(counts);
}

// OUT Write Functions
void amo1_initOUT()
{
  AMO1_OUT_EN_DDR  |=  _BV(AMO1_OUT_EN); //output
  AMO1_OUT_EN_PORT &= ~_BV(AMO1_OUT_EN); //0
  //AMO1_OUT_EN_PORT |=  _BV(AMO1_OUT_EN); //1
  amo1_out_dac.init();
}

//void amo1_setOUT(bool state, uint32_t microamps)
void amo1_setOUT()
{
  uint32_t microamps = amo1_screen_getCurrent();
  if (amo1_out_state==0 && amo1_screen_on==1) { //off -> on
    amo1_OUT(1);
    amo1_setOUTuA(microamps);
    amo1_prev_iout_ua = microamps;
    amo1_out_state = 1;
    _delay_ms(100);
//    delay(100);
  }
  else if (amo1_out_state==1 && amo1_screen_on==0) { //on -> off
    amo1_setOUTuA(0);
    _delay_ms(100);
//    delay(100);
    amo1_OUT(0);
    amo1_setVDD1mV(amo1_vdd1_max_mv);
    amo1_out_state = 0;
  }
  else if (amo1_out_state==1 && amo1_screen_on==1) { //on -> on
    if (microamps!=amo1_prev_iout_ua) {
      amo1_setOUTuA(microamps);
      amo1_prev_iout_ua=microamps;
    }
  }
}

void amo1_OUT(bool state)
{
  if (state)
    AMO1_OUT_EN_PORT |=  _BV(AMO1_OUT_EN); //1
  else
    AMO1_OUT_EN_PORT &= ~_BV(AMO1_OUT_EN); //0
//  controller.setDO(0, state);
}

void amo1_setOUTuA(uint32_t microamps)
{
  uint16_t cnts = 0;
  if (microamps>amo1_iout_max_set_ua) microamps=amo1_iout_max_set_ua;
  cnts = amo1_microAmpsToCounts(microamps);
  
  amo1_setOUTcnts(cnts);
}

uint16_t amo1_microAmpsToCounts(uint32_t microamps)
{
  float cnts = 0;
  cnts = amo1_iout_ua_to_cnts*microamps;
  if (cnts > amo1_iout_cnts) cnts = 0;
  //SerialUSB.println(cnts);
  cnts = amo1_iout_cnts-cnts;
  return cnts;
}

void amo1_setOUTcnts(uint16_t counts)
{
  amo1_out_dac.setCounts(counts);
  //SerialUSB.println(counts);
//  controller.writeDac1(counts);
}

// Read Functions
void amo1_initRead()
{
  // IOUT
  AMO1_IOUT_DDR  &= ~_BV(AMO1_IOUT); //input
  AMO1_IOUT_PORT &= ~_BV(AMO1_IOUT); //disable pullup
  //AMO1_IOUT_PORT |=  _BV(AMO1_IOUT); //enable pullup
  
  // VOUT
  AMO1_VOUT_DDR  &= ~_BV(AMO1_VOUT); //input
  AMO1_VOUT_PORT &= ~_BV(AMO1_VOUT); //disable pullup
  //AMO1_VOUT_PORT |=  _BV(AMO1_VOUT); //enable pullup
  
  // ADC Settings
  ADMUX |= _BV(REFS1) | _BV(REFS0); //Ref=2.56V
  amo1_adc_vref = 2.56;
    // |-------+-------+-----------|
    // | REFS2 | REFS0 |  Ref Sel  |
    // |-------+-------+-----------|
    // |   0   |   0   |  Ext Ref  |
    // |-------+-------+-----------|
    // |   0   |   1   |   AVCC    |
    // |-------+-------+-----------|
    // |   1   |   0   |   1.10V   |
    // |-------+-------+-----------|
    // |   1   |   1   |   2.56V   |
    // |-------+-------+-----------|
  ADMUX |= _BV(ADLAR); //result is left adjusted to 16bits
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); //16MHz/125=125kHz
    // |-------+-------+-------+------------|
    // | ADPS2 | ADPS1 | ADPS0 | Div Factor |
    // |-------+-------+-------+------------|
    // |   0   |   0   |   0   |     2      |
    // |-------+-------+-------+------------|
    // |   0   |   0   |   1   |     2      |
    // |-------+-------+-------+------------|
    // |   0   |   1   |   0   |     4      |
    // |-------+-------+-------+------------|
    // |   0   |   1   |   1   |     8      |
    // |-------+-------+-------+------------|
    // |   1   |   0   |   0   |     16     |
    // |-------+-------+-------+------------|
    // |   1   |   0   |   1   |     32     |
    // |-------+-------+-------+------------|
    // |   1   |   1   |   0   |     64     |
    // |-------+-------+-------+------------|
    // |   1   |   1   |   1   |     128    |
    // |-------+-------+-------+------------|
  ADCSRA |= _BV(ADEN); //enable ADC
}

uint32_t amo1_readIOUTmA()
{
  float read_value = 0;
  unsigned char i = 0;
  
  ADCSRB &= 0xF7;               //clear ADC MUX[5]
  ADMUX  &= 0xE0;               //clear ADC MUX[4:0]
  ADCSRB |= AMO1_IOUT_ADMUX5_;  //select ADC MUX[5]
  ADMUX  |= AMO1_IOUT_ADMUX40;  //select ADC MUX[4:0]
  
  for (i=0;i<8;i++) {
    ADCSRA |= _BV(ADSC);          //start conversion
    while((ADCSRA & _BV(ADSC)));  //wait for conversion to complete
    //while(!(ADCSRA & _BV(ADIF))); //wait for ADC Interrupt Flag to complete
    //ADCSRA |= _BV(ADIF);          //clear ADC Interrupt Flag
    read_value = ADC | 0x003F;
  }
  //printf("iout read_value = 0x%x\n", read_value);
  
  read_value = amo1_iout_cnts_to_mv*read_value;
  amo1_iout_ma = read_value;
  return read_value;
}

uint32_t amo1_readVOUTmV()
{
  float read_value = 0;
  unsigned char i = 0;
  
  ADCSRB &= 0xF7;               //clear ADC MUX[5]
  ADMUX  &= 0xE0;               //clear ADC MUX[4:0]
  ADCSRB |= AMO1_VOUT_ADMUX5_;  //select ADC MUX[5]
  ADMUX  |= AMO1_VOUT_ADMUX40;  //select ADC MUX[4:0]
  
  for (i=0;i<8;i++) {
    ADCSRA |= _BV(ADSC);          //start conversion
    while((ADCSRA & _BV(ADSC)));  //wait for conversion to complete
    //while(!(ADCSRA & _BV(ADIF))); //wait for ADC Interrupt Flag to complete
    //ADCSRA |= _BV(ADIF);          //clear ADC Interrupt Flag
    read_value = ADC | 0x003F;
  }
  //printf("vout read_value = 0x%x\n", read_value);
  
  read_value = amo1_vout_cnts_to_mv*read_value;
  amo1_vout_mv = read_value;
  return read_value;
}

// Screen Functions
void amo1_screen_debug()
{
  printf("CleO Version = %d\n", CleO.Version());
  printf("CleO ID = %d\n", CleO.ModuleIdentifier());
  CleO.Noop();
  printf("CleO Noop() Echo = %d\n", CleO.Echo());
  //printf("spi_flex_read_byte = 0x%x\n", spi_flex_read_byte(0));
  //printf("spi_flex_read_write_byte = 0x%x\n", spi_flex_read_write_byte(0, 0x8e));
}

void amo1_screen_init()
{
  char buf_text[20];
  CleO.begin();
  CleO.Display(100);
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.SetBackgroundcolor(0xe9d3ebUL);
  sprintf(buf_text,"Diode Laser Current Controller");
  CleO.StringExt(FONT_SANS_4, AMO1_SCREEN_WIDTH/2, 30, amo1_screen_text_color, MM, 0, 0, buf_text);
  sprintf(buf_text,"Device ID : AMO1");
  CleO.StringExt(FONT_BIT_3, 10, 100, amo1_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Hardware ID : 0.0.0");
  CleO.StringExt(FONT_BIT_3 , 10 , 130 , amo1_screen_text_color , ML , 0 , 0, buf_text);
  sprintf(buf_text,"Firmware ID : 0.0.0");
  CleO.StringExt(FONT_BIT_3, 10, 160, amo1_screen_text_color, ML, 0, 0, buf_text);
  sprintf(buf_text,"Starting Up ... ");
  CleO.StringExt(FONT_BIT_4 , 10 , 200 , amo1_screen_text_color , ML , 0 , 0, buf_text);
  CleO.Show();
  CleO.DisplayRotate(2, 0);
  CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo1_screen_refresh()
{
    //------------------------------------------------------------------------------------------------------------------
    // Start Drawing Screen
    //------------------------------------------------------------------------------------------------------------------
    CleO.Start();

    //------------------------------------------------------------------------------------------------------------------
    // Build Keypads / Status Screens
    //------------------------------------------------------------------------------------------------------------------
    CleO.RectangleJustification(MM);
    CleO.LineColor(amo1_screen_line_color);
    amo1_screen_draw();

    //------------------------------------------------------------------------------------------------------------------
    // Collect Tags
    //------------------------------------------------------------------------------------------------------------------
    if (amo1_fault==0) {
      amo1_screen_processButtons();
      if (amo1_screen_short_press_detected) amo1_screen_processShortPress();
    }
    //------------------------------------------------------------------------------------------------------------------
    // Update Screen
    //------------------------------------------------------------------------------------------------------------------
    CleO.Show();
}

void amo1_screen_draw()
{
    int x_offset = AMO1_SCREEN_WIDTH/2 -60;

    CleO.LineWidth(1);
    char temp = 'a';
    char* output_digit = &temp;
    char digit[1];
    char buf_on_off[15] = "OFF";

    //------------------------------------------------------------------------------------------------------------------
    // Digits Box
    //------------------------------------------------------------------------------------------------------------------

    CleO.RectangleColor(MY_WHITE);
    CleO.RectangleXY(240, 40, AMO1_SCREEN_WIDTH, 80);
    for (int i = 0; i < 6; ++i)
    {
        //*output_digit = (char)(amo1_screen_current[5-i] + '0');
        //CleO.StringExt(FONT_SANS_3 , 35 + amo1_screen_locationX[2*i], 40  , amo1_screen_text_color , MM , 0 , 0 , output_digit); // digit
        sprintf(digit, "%d", amo1_screen_current[5-i]);
        CleO.StringExt(FONT_SANS_7 , 38 + amo1_screen_locationX[2*i], 40  , amo1_screen_text_color , MM , 0 , 0 , digit); // digit
    }
    output_digit = (char*) ",";
    CleO.StringExt(FONT_SANS_5 , 40 + amo1_screen_locationX[5], 45  , amo1_screen_text_color , MM , 0 , 0 , output_digit); // comma
    //CleO.StringExt(FONT_SANS_3 , 35 + amo1_screen_locationX[12]-20, 40  , amo1_screen_text_color , MM , 0 , 0 , "uA"); // uA

    //------------------------------------------------------------------------------------------------------------------
    // ON/OFF Box
    //------------------------------------------------------------------------------------------------------------------

    CleO.Tag(amo1_screen_tag_on);
    CleO.RectangleColor(amo1_screen_on ? MY_GREEN : MY_RED);
    CleO.RectangleXY(240, 280, AMO1_SCREEN_WIDTH, 80);
    if (amo1_screen_on) {
      //sprintf(buf_on_off, "%1lu.%02luV, %03lumA", amo1_vout_mv/1000, amo1_vout_mv%1000, amo1_iout_ma);
      sprintf(buf_on_off, "%0.2fV, %lumA", amo1_vout_mv/1000.0, amo1_iout_ma);
    }
    else if (amo1_fault == 1) sprintf(buf_on_off, "%s", "Max Current Fault");
    else if (amo1_fault == 2) sprintf(buf_on_off, "%s", "Diode Not Connected");
    CleO.StringExt(FONT_SANS_4 , 60 + x_offset , 280 , amo1_screen_text_color , MM , 0 , 0, buf_on_off);
    //CleO.Tag(0);

    //------------------------------------------------------------------------------------------------------------------
    // Arrow Boxes
    //------------------------------------------------------------------------------------------------------------------
    
    CleO.NeedleWidth(15);
    for (int i = 0; i < 2; ++i){ //top to bottom
        for (int j = 0; j < 6; ++j){ // left to right
            CleO.Tag(i*6 + 6 - j);
            if(i%2!=j%2) {
                CleO.RectangleColor(!amo1_screen_pressed[i*6+j] ? MY_BLUE : MY_ORANGE);
            }
            else {
                CleO.RectangleColor(!amo1_screen_pressed[i*6+j] ? MY_YELLOW : MY_ORANGE);
            }
            CleO.RectangleXY(amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i], 80, 80);
            //CleO.Tag(0);
            if(i == 0){ // top arrow
                if      (j==2) {
                  CleO.StringExt(FONT_SANS_2 , amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]-22, amo1_screen_text_color , MM , 0 , 0 , "mA");
                  CleO.NeedleExt(amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]+35, 30, MY_BLACK, 180, 15);
                }
                else if (j==5) {
                  CleO.StringExt(FONT_SANS_2 , amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]-22, amo1_screen_text_color , MM , 0 , 0 , "uA");
                  CleO.NeedleExt(amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]+35, 30, MY_BLACK, 180, 15);
                }
                else {
                  CleO.NeedleExt(amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]+25, 30, MY_BLACK, 180, 15);
                }
                
            }
            else // bottom arrow
            {
                CleO.NeedleExt(amo1_screen_locationX[1+2*j], amo1_screen_locationY[3+2*i]-25, 30, MY_BLACK, 0, 15);
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    // Draw Divider Lines
    //------------------------------------------------------------------------------------------------------------------

    // status lines
    for (int i = 1; i < 4; i+=2)
        CleO.Line(0, AMO1_SCREEN_HEIGHT*i/4, AMO1_SCREEN_WIDTH, AMO1_SCREEN_HEIGHT*i/4);
        CleO.Line(0, AMO1_SCREEN_HEIGHT/2, amo1_screen_locationX[12], AMO1_SCREEN_HEIGHT/2);
   // arrow lines
    for (int i = 1; i < 7; ++i)
        CleO.Line(amo1_screen_locationX[2*i], AMO1_SCREEN_HEIGHT/4, amo1_screen_locationX[2*i], 3*AMO1_SCREEN_HEIGHT/4);
}

void amo1_screen_processButtons()
{
    //NOTE: for more than 13 tags, you must manually tag!
    CleO.TouchCoordinates(amo1_screen_x, amo1_screen_y, amo1_screen_current_dur, amo1_screen_current_tag);
    amo1_screen_shortPress(&amo1_screen_short_press_detected);

    amo1_screen_last_dur = amo1_screen_current_dur;
    if (amo1_screen_current_tag == 13){
        if (amo1_screen_toggle_on){
            amo1_screen_on = !amo1_screen_on;
            amo1_screen_toggle_on = false;
        }
    }
    else if (!amo1_screen_toggle_on)
        amo1_screen_toggle_on = true;
}

void amo1_screen_shortPress (bool *press_detected)
{
    if (amo1_screen_current_dur==1 && amo1_screen_last_dur==0 && !*press_detected) {
        *press_detected = 1;
        //SerialUSB.println("Short press!");
    }
    else {
        *press_detected = 0;
    }
}

void amo1_screen_processShortPress() {
    switch (amo1_screen_current_tag) {
        case amo1_screen_tag_0i    :
            amo1_screen_increaseSetCurrent(0);
            break;
        case amo1_screen_tag_1i    :
            amo1_screen_increaseSetCurrent(1);
            break;
        case amo1_screen_tag_2i    :
            amo1_screen_increaseSetCurrent(2);
            break;
        case amo1_screen_tag_3i    :
            amo1_screen_increaseSetCurrent(3);
            break;
        case amo1_screen_tag_4i    :
            amo1_screen_increaseSetCurrent(4);
            break;
        case amo1_screen_tag_5i    :
            amo1_screen_increaseSetCurrent(5);
            break;
        case amo1_screen_tag_0d    :
            amo1_screen_decreaseSetCurrent(0);
            break;
        case amo1_screen_tag_1d    :
            amo1_screen_decreaseSetCurrent(1);
            break;
        case amo1_screen_tag_2d    :
            amo1_screen_decreaseSetCurrent(2);
            break;
        case amo1_screen_tag_3d    :
            amo1_screen_decreaseSetCurrent(3);
            break;
        case amo1_screen_tag_4d    :
            amo1_screen_decreaseSetCurrent(4);
            break;
        case amo1_screen_tag_5d    :
            amo1_screen_decreaseSetCurrent(5);
            break;
    }
}

void amo1_screen_increaseSetCurrent(int i)
{
    if (i < 0) {
      return;
    }
    else if (i >= AMO1_SCREEN_NUM_OF_DIGITS){
      amo1_screen_current[i-1] = 9;
      return;
    }
    /*
    else if (amo1_screen_current[AMO1_SCREEN_NUM_OF_DIGITS-1] >= 2) {
      return;
    }*/

    ++amo1_screen_current[i];
    if (amo1_screen_current[i] > 9)
    {
        amo1_screen_current[i] = 0;
        amo1_screen_increaseSetCurrent(i + 1);
    }
	
    if (amo1_screen_getCurrent() > amo1_iout_max_set_ua) {
      amo1_screen_current[0]=0;
      amo1_screen_current[1]=0;
      amo1_screen_current[2]=0;
      amo1_screen_current[3]=0;
      amo1_screen_current[4]=0;
      amo1_screen_current[5]=2;
      return;
    }
}

void amo1_screen_decreaseSetCurrent(int i)
{
    if (i >= AMO1_SCREEN_NUM_OF_DIGITS || i < 0) return;

    --amo1_screen_current[i];
    if (amo1_screen_current[i] < 0) {
      if (i < (AMO1_SCREEN_NUM_OF_DIGITS-1)) {
        if (amo1_screen_current[i+1]>0) {
          amo1_screen_current[i]=9;
          amo1_screen_decreaseSetCurrent(i+1);
          return;
        }
      }
      amo1_screen_current[i] = 0;
    }
}

bool amo1_screen_isOn()
{
    return amo1_screen_on;
}

uint32_t amo1_screen_getCurrent()
{
    uint32_t total = 0;
    uint32_t place = 1;
    for (int i = 0; i < AMO1_SCREEN_NUM_OF_DIGITS; ++i)
    {
        total += place * amo1_screen_current[i];
        place *= 10;
    }
    return total;
}

/*
void amo1_parseInput(String input)
{
  String cmd, data, len;
  input.trim();
  //input.toLowerCase();
  len = input.length();

  // Check length
  if (len.toInt()>3) {
    cmd = input.substring(0,4);
    cmd.trim();
    data = input.substring(4);
    data.trim();
  }
  else {
    SerialUSB.println("Invalid Input");
  }

  // Parse commands
  if (cmd == "read") {
    SerialUSB.println("read");
    SerialUSB.println(amo1_readIOUTmA());
    SerialUSB.println(amo1_readVOUTmV());
  }
  else if (cmd == "iout") {
    if (data == "off") {
      SerialUSB.println("iout>off");
      amo1_OUT(0);
    }
    else if (data == "on") {
      SerialUSB.println("iout>on");
      amo1_OUT(1);
    }
    else if (data == "read") {
      SerialUSB.println("iout>read");
      SerialUSB.println(amo1_readIOUTmA());
      SerialUSB.println(amo1_readVOUTmV());
    }
    else {
      SerialUSB.println("iout>data");
      amo1_setOUTuA(data.toInt());
    }
  }
  else if (cmd == "vdd1") {
    if (data == "off") {
      SerialUSB.println("vdd1>off");
      amo1_VDD1(0);
    }
    else if (data == "on") {
      SerialUSB.println("vdd1>on");
      amo1_VDD1(1);
    }
    else {
      SerialUSB.println("vdd1>data");
      amo1_setVDD1mV(data.toInt());
    }
  }
  else
  {
    SerialUSB.println("Invalid Command");
  }
}
*/
#endif // AMO1_H
