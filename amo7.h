#ifndef AMO7_HH
#define AMO7_HH 1

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////
// Tracking
//////////////////////////////////////////////////////////////////////////////////////
const char device_name[] = "Stepper Motor Controller";
const char device_id[]   = "AMO7";
const char hardware_id[] = "1.0.0";
const char firmware_id[] = "1.2.0";

//////////////////////////////////////////////////////////////////////////////////////
// Declaration
//////////////////////////////////////////////////////////////////////////////////////

//Ports

    //Extension (?)
#define AMO6_EXT1_nEN		PG1
#define AMO6_EXT1_nEN_DDR   	DDRG
#define AMO6_EXT1_nEN_PORT  	PORTG

#define AMO6_EXT2_nEN		PG3
#define AMO6_EXT2_nEN_DDR   	DDRG
#define AMO6_EXT2_nEN_PORT  	PORTG

    //Buzzer
#define AMO6_BUZZER_nEN		PD7
#define AMO6_BUZZER_nEN_DDR   	DDRD
#define AMO6_BUZZER_nEN_PORT  	PORTD

    //Shift Register
#define AMO7_DRV_CLEAR      PA0
#define AMO7_DRV_CLOCK      PA1
#define AMO7_DRV_LOAD       PA2
#define AMO7_DRV_INPUT      PA3

    //DAC
#define AMO7_DAC_LOAD       PA4
#define AMO7_DAC_CLOCK      PA5
#define AMO7_DAC_INPUT      PA6
#define AMO7_DAC_CLEAR      PA7

#define AMO7_DRV_DAC_PORT   PORTA
#define AMO7_DRV_DAC_DDR    DDRA

    //Stepping
#define AMO7_STEP_PIN_0     PJ4
#define AMO7_STEP_PIN_1     PJ5
#define AMO7_STEP_PIN_2     PJ6
#define AMO7_STEP_PORT      PORTJ
#define AMO7_STEP_DDR       DDRJ

    //Board Selection
#define AMO7_BOARD_PIN_0    PC0
#define AMO7_BOARD_PIN_1    PC1
#define AMO7_BOARD_PIN_2    PC2
#define AMO7_BOARD_PIN_3    PC3
#define AMO7_BOARD_PORT     PORTC
#define AMO7_BOARD_DDR      DDRC
#define AMO7_BOARD_PORT_R   PORTC

    //Calibration & HOME Interrupt
#define AMO7_FEEDBACK_PORT1_R   PINJ
#define AMO7_FEEDBACK_PORT2_R   PINK
#define AMO7_FEEDBACK_DDR2  DDRK

// Buttons (AMO6)
static int8_t  amo6_encoder_val       = 0;
static bool    amo6_sw1_pushed        = false;
static bool    amo6_sw2_pushed        = false;
static bool    amo6_count_latch [2]   = {false, false};
uint8_t        amo6_hold_count  [2]   = {0, 0};
const uint8_t  amo6_hold_threshold    = 7;  //decrease hold_threshold for faster incrementing

void  amo6_buttons_init    ();
void  amo6_buttons_update  ();

// Serial (AMO6)
const int  amo6_serial_buffer_size  = 100;
char       amo6_serial_buffer  [amo6_serial_buffer_size+1];
char       amo6_serial_string  [amo6_serial_buffer_size+1];

void  amo6_serial_update  ();
void  amo6_serial_parse   ();

//Screen (AMO6)

#define AMO6_SCREEN_H		320
#define AMO6_SCREEN_W		480
#define AMO6_SCREEN_OFFSET  1

    //CLEO
#define AMO6_CLEO_nPWR		PG0
#define AMO6_CLEO_nPWR_DDR	DDRG
#define AMO6_CLEO_nPWR_PORT	PORTG

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
#define CLEO_SELECT		0xADD8E6UL
#define CLEO_TEC_ON		0x98FB98UL
#define CLEO_TEC_OFF	0xFF7256UL
#define amo6_screen_text_color  0x000000UL  //MY_BLACK
#define amo6_screen_line_color  0x004166UL  //MY_DARKBLUE

enum{       //Labels for screen tags
    amo6_screen_null_tag         , // 0
    moving_voltge_output         , // 1
    coarse_display               , // 2
    step_counter                 , // 3
    on_off_switch                , // 4
    calibrate_button             , // 5
    zero_button                  , // 6
    move_button                  , // 7
    holding_voltage_output       , // 8
    fine_step_adjustment         , // 9
    stepper_motor_counter        , // 10
    screen_bug                   , // 11
};
#define AMO6_SCREEN_TAGS 12	
bool amo6_screen_select[AMO6_SCREEN_TAGS];

int16_t  amo6_screen_x  , amo6_screen_y    ;
int16_t  amo6_screen_current_dur           ;
int      amo6_screen_last_dur              = 0;
int16_t  amo6_screen_current_tag           ;
bool     amo6_screen_short_press_detected  = 0;

    //Screen functions
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
#define      amo7_max_stepper_motor_number  11      //starts from 0
#define      amo7_max_microstep_number      3
#define      amo7_max_holder_val            358400  //200*64*3.5 << 3, too high = overflow
#define      amo7_max_V                     255
#define      amo7_min_delay_us              100     //-> max speed = 10k steps/s
#define      amo7_max_delay_us              65000   //det. by timer register size (16b)
#define      amo7_starting_delay_us         1000    //starting speed is 1000 steps/s
#define      amo7_retreat_delay             781     //delay between hitting home and retreating, in steps of 64us, starts at 50ms
#define      amo7_timer_val_to_us           1       //Convert timer value to us, = 1e6(1s in us) * 8(prescaler) * 2(1:1 high:low) / 1.6e7 (clock)
#define      amo7_accel_rate                5       //shorten delay by 5us/s
#define      amo7_backlash_constant         10      //backlash from backlash device
#define      amo7_calib_offset              1000    //offset steps before/after calibration

#define      amo7_calib_dir                 1       //direction of calibration

    //Motor Object
struct Individual_Motor {
    Individual_Motor (float angle, bool feedback) {
        step_size = angle;
        sensor = feedback;
    }
    float           step_size       ;
    bool            sensor          ;
    long            step_holder     = 0;
    long            move_holder     = 0;
    int             moving_voltage  = 0;
    int             holding_voltage = 0;
    int             pfd_voltage     = 0;
    bool            power           = false;
    bool            enable          = true;
    long            speed_delay_us  = amo7_starting_delay_us;
};

    //Motors for Box
Individual_Motor amo7_motors[12] {
    Individual_Motor(1.8, true),  //1
    Individual_Motor(1.8, true),  //2
    Individual_Motor(1.8, true),  //3
    Individual_Motor(1.8, true),  //4
    Individual_Motor(1.8, true),  //5
    Individual_Motor(1.8, true),  //6
    Individual_Motor(1.8, true),  //7
    Individual_Motor(1.8, true),  //8
    Individual_Motor(1.8, true),  //9
    Individual_Motor(1.8, true),  //10
    Individual_Motor(1.8, true),  //11
    Individual_Motor(1.8, true),  //12
};

    //Screen variables
int          amo7_microstep_number           = 0;    //Tracks microstepping display & config
int          amo7_stepper_motor_number       = 0;    //Tracks active stepper motor

    //Background queue
volatile int  amo7_step_queue[12][4]          ;       //0=motor#,1=rounding_steps,2=dir,3=calib?
int           amo7_queue_index                = 0;    //Tracks how many motors are queued up
bool          amo7_new_motor                  = true;
volatile int  amo7_queued_microstep_counter   = false;//Tracks background microstepping

    //Interrupt stepping
volatile bool amo7_motor_moving               = false;
volatile int  amo7_motor_shift                ;
volatile long amo7_steps_to_max_min           ;
volatile long amo7_accel_steps_tmp            ;

    //Mode options
volatile bool amo7_alt_mode                   = false;  //alt mode: manual stepping & no HOME interrupts
bool          amo7_global_acceleration        = true;   //accelerates from starting speed
bool          amo7_local_acceleration         = false;  //shifts calculation to main loop
bool          amo7_rounding_mode              = true;   //move to nearest full step
bool          amo7_back_account               = false;  //backlash accounting (not yet implemented)

    //Motor Functions

//initializes all the relevant ports, registers, pins, and hardware
void amo7_init                   ();

//initializes the dac
void amo7_dac_init               ();

//updates the voltage to each motor via the dac
    //@motor_num: the motor to be updated, @mode: the type of voltage to update (0 = holding, 1 = moving, 2 = pdf)
void amo7_stepper_dac_update     (int motor_num, int mode);

//runs in the background to queue and prepare motors for stepping
void amo7_background_stepping    ();

//chooses the board to communicate with and the direction of data transfer
    //@motor_num: the motor to be updated, @out: whether data is going to or from the board
void amo7_board_config           (int motor_num, bool out);

//configures the voltage, power, microstep, and direction of each motor
    //@motor_num: the motor to be updated, @dir: the direction to move, @msn: the microstep number in powers of -2
void amo7_motor_config           (int motor_num, bool dir, int msn);

//gets the motor data and puts it into step_queue
    //@motor_num: the motor to be updated, @out: 
void amo7_move_config            (int motor_num, bool calib);

//steps the motor immediately in response to user input
    //@motor_num: the motor to be updated, @ms: the microstep number in powers of -2, @steps: the steps to move
void amo7_manual_stepping        (int motor_num, int ms, int steps);

//return whether the pin is over the home sensor or not (0 = yes, 1 = no)
    //@motor_num: the motor to be updated
bool amo7_sensor_feedback        (int motor_num);

#endif // AMO7_HH