#ifndef SCREEN_H
#define SCREEN_H 1

static const int long_press_threshold = 3;

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

#define screenWidth  480
#define screenHeight 320
#define windowWidth  240
#define windowHeight 320

const int NUM_OF_DIGITS = 6;

int16_t x, y, dur, current_tag;

//////////////////////////////////////////////////////////////////////////////////////
// Useful variables - sets up screen
//////////////////////////////////////////////////////////////////////////////////////

// over buttons
int locationY[9] = {0, 40, 80, 120, 160 ,200 , 240, 280 , 320};
int locationX[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 480, 480};

int bounding_margin = 20;
uint32_t keypad_taglist=0;

bool keypad_enabled [2] = {0,0};

uint32_t keypad_color       = MY_PURPLE;
uint32_t keypad_text_color  = MY_BLACK;

uint32_t display_text_color = MY_BLACK;

uint32_t background_color   = MY_PINK;

uint32_t line_color         = MY_DARKBLUE;

uint32_t color_good         = MY_GREEN;
uint32_t color_bad          = MY_RED;

uint32_t color_on           = MY_GREEN;
uint32_t color_off          = MY_RED;

uint32_t set_color          = keypad_color;
uint32_t touch_color        = MY_BLUE;

uint32_t color_tripped      = 0xff0000;

int16_t font;

enum {
    tag_null    , // 0
    tag_0i      , // 1
    tag_1i      , // 2
    tag_2i      , // 3
    tag_3i      , // 4
    tag_4i      , // 5
    tag_5i      , // 6
    tag_0d      , // 7
    tag_1d      , // 8
    tag_2d      , // 9
    tag_3d      , // 10
    tag_4d      , // 11
    tag_5d      , // 12
    tag_set     ,//  13
};

//////////////////////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////////////////////

//writes where the buttons are on the screen
void processButtons    ();
//makes UI for each panel
void buildStatus       ();

//draws the screen and the line separating the 2 panels and scans for clicks
void updateScreen      ();

//for debugging in testing
void setDecimalPoint   ();

//new functions
void increaseSetCurrent(int i);
void decreaseSetCurrent(int i);

//////////////////////////////////////////////////////////////////////////////////////
// Member Variables
//////////////////////////////////////////////////////////////////////////////////////

enum {stat_trip=0, stat_idle, stat_setting, stat_good, stat_stable, stat_supply, NUM_STATS};

uint8_t status[2] = {stat_idle, stat_idle}; // default

/*
//status of device
char* statString (uint8_t stat)
{
    switch (stat) {
        case (stat_trip):              return ( (char*)"TRIP" );
        case (stat_idle):              return ( (char*)"IDLE");
        case (stat_setting):           return ( (char*)"SET"  );
        case (stat_good):              return ( (char*)"GOOD");
        case (stat_stable):            return ( (char*)"READY");
        case (stat_supply):            return ( (char*)"VCC BAD");
    }
}

uint32_t statColor (uint8_t stat)
{
    switch (stat) {
        case (stat_trip):              return (  MY_REDRED            );
        case (stat_idle):              return (  MY_GREEN             );
        case (stat_setting):           return (  MY_ORANGE            );
        case (stat_good):              return (  MY_GREEN             );
        case (stat_stable):            return (  MY_GREEN             );
        case (stat_supply):            return (  MY_REDRED            );
    }
}
*/

bool short_press_detected = 0;
int last_dur = 0;

//values specified on screen
extern uint16_t set_dac_counts [2]    ;  // Set Voltage IN deci-Volts
extern uint32_t set_microamps  [2]    ;  // Set Current IN micro-Amps

//new variables
int setCurrent[NUM_OF_DIGITS] = {0};
bool pressed[NUM_OF_DIGITS * 2] = {0};
bool screen_on = false;
bool toggleOn = true;

//////////////////////////////////////////////////////////////////////////////////////
// Member Functions: Implementation
//////////////////////////////////////////////////////////////////////////////////////

void shortPress (bool *press_detected)
{
    if (dur==1 && last_dur==0 && !*press_detected) {
        *press_detected = 1;
        //SerialUSB.println("Short press!");
    }
    else {
        *press_detected = 0;
    }
}

void processShortPress() {
    switch (current_tag) {
        case tag_0i    :
            increaseSetCurrent(0);
            break;
        case tag_1i    :
            increaseSetCurrent(1);
            break;
        case tag_2i    :
            increaseSetCurrent(2);
            break;
        case tag_3i    :
            increaseSetCurrent(3);
            break;
        case tag_4i    :
            increaseSetCurrent(4);
            break;
        case tag_5i    :
            increaseSetCurrent(5);
            break;
        case tag_0d    :
            decreaseSetCurrent(0);
            break;
        case tag_1d    :
            decreaseSetCurrent(1);
            break;
        case tag_2d    :
            decreaseSetCurrent(2);
            break;
        case tag_3d    :
            decreaseSetCurrent(3);
            break;
        case tag_4d    :
            decreaseSetCurrent(4);
            break;
        case tag_5d    :
            decreaseSetCurrent(5);
            break;
    }
}

void setDecimalPoint()
{
}

void buildStatus (uint8_t fault)
{
    int x_offset = screenWidth/2 -60;

    CleO.LineWidth(1);
    char temp = 'a';
    char* output_digit = &temp;
    char digit[1];
    char buf_on_off[15] = "OFF";

    //------------------------------------------------------------------------------------------------------------------
    // Digits Box
    //------------------------------------------------------------------------------------------------------------------

    CleO.RectangleColor(MY_WHITE);
    CleO.RectangleXY(240, 40, screenWidth, 80);
    for (int i = 0; i < 6; ++i)
    {
        //*output_digit = (char)(setCurrent[5-i] + '0');
        //CleO.StringExt(FONT_SANS_3 , 35 + locationX[2*i], 40  , display_text_color , MM , 0 , 0 , output_digit); // digit
        sprintf(digit, "%d", setCurrent[5-i]);
        CleO.StringExt(FONT_SANS_7 , 38 + locationX[2*i], 40  , display_text_color , MM , 0 , 0 , digit); // digit
    }
    output_digit = (char*) ",";
    CleO.StringExt(FONT_SANS_5 , 40 + locationX[5], 45  , display_text_color , MM , 0 , 0 , output_digit); // comma
    //CleO.StringExt(FONT_SANS_3 , 35 + locationX[12]-20, 40  , display_text_color , MM , 0 , 0 , "uA"); // uA

    //------------------------------------------------------------------------------------------------------------------
    // ON/OFF Box
    //------------------------------------------------------------------------------------------------------------------

    CleO.Tag(13);
    CleO.RectangleColor(screen_on ? MY_GREEN : MY_RED);
    CleO.RectangleXY(240, 280, screenWidth, 80);
    if (screen_on) {
//      sprintf(buf_on_off, "%1lu.%03luV, %03lumA", amo1_vout_mv/1000, amo1_vout_mv%1000, amo1_iout_ma);
    }
    else if (fault == 1) {
      sprintf(buf_on_off, "%s", "Current Fault!");
    }
    CleO.StringExt(FONT_SANS_4 , 60 + x_offset , 280 , display_text_color , MM , 0 , 0, buf_on_off);
    //CleO.Tag(0);

    //------------------------------------------------------------------------------------------------------------------
    // Arrow Boxes
    //------------------------------------------------------------------------------------------------------------------
    
    CleO.NeedleWidth(15);
    for (int i = 0; i < 2; ++i){ //top to bottom
        for (int j = 0; j < 6; ++j){ // left to right
            CleO.Tag(i*6 + 6 - j);
            if(i%2!=j%2) {
                CleO.RectangleColor(!pressed[i*6+j] ? MY_BLUE : MY_ORANGE);
            }
            else {
                CleO.RectangleColor(!pressed[i*6+j] ? MY_YELLOW : MY_ORANGE);
            }
            CleO.RectangleXY(locationX[1+2*j], locationY[3+2*i], 80, 80);
            //CleO.Tag(0);
            if(i == 0){ // top arrow
                if      (j==2) {
                  CleO.StringExt(FONT_SANS_2 , locationX[1+2*j], locationY[3+2*i]-22, display_text_color , MM , 0 , 0 , "mA");
                  CleO.NeedleExt(locationX[1+2*j], locationY[3+2*i]+35, 30, MY_BLACK, 180, 15);
                }
                else if (j==5) {
                  CleO.StringExt(FONT_SANS_2 , locationX[1+2*j], locationY[3+2*i]-22, display_text_color , MM , 0 , 0 , "uA");
                  CleO.NeedleExt(locationX[1+2*j], locationY[3+2*i]+35, 30, MY_BLACK, 180, 15);
                }
                else {
                  CleO.NeedleExt(locationX[1+2*j], locationY[3+2*i]+25, 30, MY_BLACK, 180, 15);
                }
                
            }
            else // bottom arrow
            {
                CleO.NeedleExt(locationX[1+2*j], locationY[3+2*i]-25, 30, MY_BLACK, 0, 15);
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    // Draw Divider Lines
    //------------------------------------------------------------------------------------------------------------------

    // status lines
    for (int i = 1; i < 4; i+=2)
        CleO.Line(0, screenHeight*i/4, screenWidth, screenHeight*i/4);
        CleO.Line(0, screenHeight/2, locationX[12], screenHeight/2);
   // arrow lines
    for (int i = 1; i < 7; ++i)
        CleO.Line(locationX[2*i], screenHeight/4, locationX[2*i], 3*screenHeight/4);
}

int getCurrent()
{
    int total = 0;
    int place = 1;
    for (int i = 0; i < NUM_OF_DIGITS; ++i)
    {
        total += place * setCurrent[i];
        place *= 10;
    }
    return total;
}

void increaseSetCurrent(int i)
{
    if (i < 0) {
      return;
    }
    else if (i >= NUM_OF_DIGITS){
      setCurrent[i-1] = 9;
      return;
    }
    /*
    else if (setCurrent[NUM_OF_DIGITS-1] >= 2) {
      return;
    }*/

    ++setCurrent[i];
    if (setCurrent[i] > 9)
    {
        setCurrent[i] = 0;
        increaseSetCurrent(i + 1);
    }
    
    if (getCurrent() > 80000) {
      setCurrent[0]=0;
      setCurrent[1]=0;
      setCurrent[2]=0;
      setCurrent[3]=0;
      setCurrent[4]=8;
      setCurrent[5]=0;
      return;
    }
}

void decreaseSetCurrent(int i)
{
    if (i >= NUM_OF_DIGITS || i < 0) return;

    --setCurrent[i];
    if (setCurrent[i] < 0) {
      if (i < (NUM_OF_DIGITS-1)) {
        if (setCurrent[i+1]>0) {
          setCurrent[i]=9;
          decreaseSetCurrent(i+1);
          return;
        }
      }
      setCurrent[i] = 0;
    }
}

void processButtons ()
{
    //NOTE: for more than 13 tags, you must manually tag!
    CleO.TouchCoordinates(x, y, dur, current_tag);
    shortPress(&short_press_detected);

    last_dur = dur;
    if (current_tag == 13){
        if (toggleOn){
            screen_on = !screen_on;
            toggleOn = false;
        }
    }
    else if (!toggleOn)
        toggleOn = true;
}

bool isOn()
{
    return screen_on;
}

void screen_processFault(uint8_t fault)
{
  if (fault==1) {
    screen_on = 0;
  }
  CleO.Start();
  CleO.RectangleJustification(MM);
  CleO.LineColor(line_color);
  buildStatus(fault);
  CleO.Show();
}

void updateScreen()
{
    //------------------------------------------------------------------------------------------------------------------
    // Start Drawing Screen
    //------------------------------------------------------------------------------------------------------------------

    CleO.Start();

    //------------------------------------------------------------------------------------------------------------------
    // Build Keypads / Status Screens
    //------------------------------------------------------------------------------------------------------------------

    CleO.RectangleJustification(MM);
    CleO.LineColor(line_color);

    buildStatus(0);

    //------------------------------------------------------------------------------------------------------------------
    // Collect Tags
    //------------------------------------------------------------------------------------------------------------------
    processButtons();

    if (short_press_detected) processShortPress();
    

    //------------------------------------------------------------------------------------------------------------------
    // Update Screen
    //------------------------------------------------------------------------------------------------------------------
    CleO.Show();
}
#endif // SCREEN_H
