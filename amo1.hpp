#ifndef AMO1_H
#define AMO1_H 1

//////////////////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////////////////

// screen constants
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

//////////////////////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////////////////////
const uint32_t amo1_iout_max_ua = 80000;

// screen variables
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

//////////////////////////////////////////////////////////////////////////////////////
// Member Variables
//////////////////////////////////////////////////////////////////////////////////////

// screen variables
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
// Member Functions: Declaration
//////////////////////////////////////////////////////////////////////////////////////
void amo1_init();

// screen functions
void amo1_screen_debug();

void amo1_screen_refresh();
void amo1_screen_draw(uint8_t fault);

void amo1_screen_processButtons();
void amo1_screen_shortPress (bool *press_detected);
void amo1_screen_processShortPress();

void amo1_screen_increaseSetCurrent(int i);
void amo1_screen_decreaseSetCurrent(int i);

bool amo1_screen_isOn();
uint32_t amo1_screen_getCurrent();

void amo1_screen_processFault(uint8_t fault);

//////////////////////////////////////////////////////////////////////////////////////
// Member Functions: Implementation
//////////////////////////////////////////////////////////////////////////////////////
void amo1_init()
{
  // screen init
  CleO.begin();
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.SetBackgroundcolor(0xe9d3ebUL);
  CleO.Show();
  CleO.DisplayRotate(2, 0);
  CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo1_screen_debug()
{
  printf("CleO Version = %d\n", CleO.Version());
  printf("CleO ID = %d\n", CleO.ModuleIdentifier());
  CleO.Noop();
  printf("CleO Noop() Echo = %d\n", CleO.Echo());
  //printf("spi_flex_read_byte = 0x%x\n", spi_flex_read_byte(0));
  //printf("spi_flex_read_write_byte = 0x%x\n", spi_flex_read_write_byte(0, 0x8e));
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
    amo1_screen_draw(0);

    //------------------------------------------------------------------------------------------------------------------
    // Collect Tags
    //------------------------------------------------------------------------------------------------------------------
    amo1_screen_processButtons();
    if (amo1_screen_short_press_detected) amo1_screen_processShortPress();

    //------------------------------------------------------------------------------------------------------------------
    // Update Screen
    //------------------------------------------------------------------------------------------------------------------
    CleO.Show();
}

void amo1_screen_draw(uint8_t fault)
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
//      sprintf(buf_on_off, "%1lu.%03luV, %03lumA", amo1_vout_mv/1000, amo1_vout_mv%1000, amo1_iout_ma);
    }
    else if (fault == 1) {
      sprintf(buf_on_off, "%s", "Current Fault!");
    }
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
	
    if (amo1_screen_getCurrent() > amo1_iout_max_ua) {
      amo1_screen_current[0]=0;
      amo1_screen_current[1]=0;
      amo1_screen_current[2]=0;
      amo1_screen_current[3]=0;
      amo1_screen_current[4]=8;
      amo1_screen_current[5]=0;
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

void amo1_screen_processFault(uint8_t fault)
{
  if (fault==1) {
    amo1_screen_on = 0;
  }
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.LineColor(amo1_screen_line_color);
  amo1_screen_draw(fault);
  CleO.Show();
}

#endif // AMO1_H
