#ifndef AMO7_H
#define AMO7_H 1
#include "amo7.h"

//////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////

// AMO7
void amo7_init ()
{
    // hardware i/o config
    AMO6_CLEO_nPWR_DDR  |=  _BV(AMO6_CLEO_nPWR);//output
    AMO6_CLEO_nPWR_PORT |=  _BV(AMO6_CLEO_nPWR); //1
    
    AMO6_EXT1_nEN_DDR  |=  _BV(AMO6_EXT1_nEN); //output
    AMO6_EXT1_nEN_PORT &= ~_BV(AMO6_EXT1_nEN); //0
    AMO6_EXT2_nEN_DDR  |=  _BV(AMO6_EXT2_nEN); //output
    AMO6_EXT2_nEN_PORT &= ~_BV(AMO6_EXT2_nEN); //0
    AMO6_BUZZER_nEN_DDR  |=  _BV(AMO6_BUZZER_nEN); //output
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
    
    AMO7_DRV_DAC_DDR    = 0xff; //AMO7_DRV_DAC_PORT is shift register & DAC
    AMO7_STEP_DDR       = 0xf0; //J0-J3 is motor 1 feedback, J4-J7 are motor step output
    AMO7_BOARD_DDR      = 0xff; //C0-C3 enable input dig. iso., C4-C7 enable feedback dig. iso.
    AMO7_FEEDBACK_DDR2  = 0x00; //PORTK is all feedback
    
    // hardware init
    TCCR1B |= _BV(WGM12);  //set CTC mode
    TIMSK1 |= _BV(OCIE1A); //enable OCR1A match interrupt        
    AMO7_DRV_DAC_PORT = (_BV(AMO7_DRV_CLEAR) | _BV(AMO7_DAC_LOAD) | _BV(AMO7_DAC_CLEAR));
    AMO7_BOARD_PORT   = 0x00;
    
    //sensor interrupt init
    //PCICR |= (_BV(PCIE2) | _BV(PCIE1));
    PCMSK1 |= _BV(PCINT9);
    PCMSK2 |= (_BV(PCINT19) | _BV(PCINT23));
    
    amo6_screen_init();
    amo6_buttons_init();
    amo7_dac_init();
    _delay_ms(10);
    amo7_board_config(0, true); //start at board 0, motor 0
}

// Buttons (AMO6)
void amo6_buttons_init () {
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
ISR(INT5_vect){ //ENC_TURN
    static uint8_t old_AB = 0;  //lookup table index  
    static const int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table
    old_AB <<= 2;  //store previous state
    old_AB |= (  ( (((PIND>>PD2)&0x01)<<1) | ((PIND>>PD1)&0x01) )  &  0x03  ); //add current state
    amo6_encoder_val += enc_states[( old_AB & 0x0f )];
}

ISR(INT3_vect){     //ENC_SW
}

ISR(PCINT0_vect){   //SW1 SW2
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

ISR(TIMER1_COMPA_vect){
    TCCR1B &= ~(_BV(CS11)); //turn off timer
    long current_tmp = labs(amo7_motors[amo7_step_queue[0][0]].move_holder) >> (3 - amo7_queued_microstep_counter);
    if (current_tmp != 0) {
        if (amo7_step_rising){                      //step high
            AMO7_STEP_PORT |= _BV(amo7_motor_shift); 
            int tmp = _BV(3 - amo7_queued_microstep_counter);
            amo7_motors[amo7_step_queue[0][0]].move_holder -= tmp;
        }
        else {                          //step low
            AMO7_STEP_PORT &= ~(_BV(amo7_motor_shift));
        }
        if (amo7_local_acceleration && amo7_step_rising){   //adjust acceleration
            uint16_t ocr1a_tmp = OCR1A;  //load OCR1A value
            if (amo7_accel_steps_tmp > 0){
                ocr1a_tmp -= amo7_accel_rate;
                OCR1A = ocr1a_tmp;
                amo7_accel_steps_tmp -= 1;
            }
            else if(current_tmp < amo7_steps_to_max_min){
                ocr1a_tmp += amo7_accel_rate;
                OCR1A = ocr1a_tmp;
            }
        }
        amo7_step_rising = !amo7_step_rising;
        TCCR1B |= _BV(CS11);  //turn on timer
    }
    else {
        AMO7_STEP_PORT &= ~(_BV(amo7_motor_shift));
        amo7_local_acceleration = false;
        amo7_motor_moving = false;      //tell amo7_background_stepping to stop
    }
}

ISR(PCINT1_vect, ISR_ALIASOF(PCINT2_vect)); //map PCINT1 to PCINT2
ISR(PCINT2_vect){
    printf("thkim\n");
    if (!amo7_sensor_feedback(amo7_step_queue[0][0]) && amo7_motors[amo7_step_queue[0][0]].sensor){
        printf("light: %d\n", amo7_sensor_feedback(amo7_step_queue[0][0]));
        printf("PINJ: %x\n", PINJ);
        amo7_motors[amo7_step_queue[0][0]].step_holder = 0;
        amo7_motors[amo7_step_queue[0][0]].move_holder = 0;
        printf("   calibrated motor %d\n", amo7_step_queue[0][0]+1);
        PCICR &= ~(_BV(PCIE2) | _BV(PCIE1));        //disable pcint interrupts
    }
}

void amo6_buttons_update () {
    static int tag_old = 0;
    int tag;
    double tmp;
    bool sw1_now = (PINB>>PB6) & 0x01;
    bool sw2_now = (PINB>>PB5) & 0x01;
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
            default :       //toggle alternate mode
                if (amo7_queue_index == 0){
                    amo7_alt_mode = !amo7_alt_mode;   //switch modes
                    printf("   alternate mode: %d\n", amo7_alt_mode);
                    if (amo7_alt_mode){  //reset motors if not moved
                        for (int i = 0; i <= amo7_max_stepper_motor_number; i++){
                            amo7_motors[i].step_holder = amo7_motors[i].move_holder;
                        }
                    }
                }
                AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                _delay_ms(100);
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
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
                        tmp = amo7_motors[amo7_stepper_motor_number].moving_voltage - 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_motors[amo7_stepper_motor_number].moving_voltage = tmp;
                        break;
                    case holding_voltage_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_motors[amo7_stepper_motor_number].holding_voltage - 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_motors[amo7_stepper_motor_number].holding_voltage = tmp;
                        amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                        break;
                    case coarse_display	:
                        break;
                    case step_counter	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_motors[amo7_stepper_motor_number].step_holder - _BV(3 - amo7_microstep_number);
                        if (tmp>amo7_max_holder_val) tmp=amo7_max_holder_val;
                        if (tmp<(amo7_max_holder_val*-1)) tmp=(amo7_max_holder_val*-1);
                        amo7_motors[amo7_stepper_motor_number].step_holder = tmp;
                        if (amo7_alt_mode) amo7_manual_stepping(amo7_stepper_motor_number, amo7_microstep_number, -1);
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
                        tmp = amo7_motors[amo7_stepper_motor_number].moving_voltage + 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_motors[amo7_stepper_motor_number].moving_voltage = tmp;
                        break;
                    case holding_voltage_output	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_motors[amo7_stepper_motor_number].holding_voltage + 1;
                        if (tmp>amo7_max_V) tmp=amo7_max_V;
                        if (tmp<0) tmp=0;
                        amo7_motors[amo7_stepper_motor_number].holding_voltage = tmp;
                        amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                        break;
                    case coarse_display	:
                        break;
                    case step_counter	:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(5);
                        tmp = amo7_motors[amo7_stepper_motor_number].step_holder + _BV(3 - amo7_microstep_number);
                        if (tmp>amo7_max_holder_val) tmp=amo7_max_holder_val;
                        if (tmp<(amo7_max_holder_val*-1)) tmp=(amo7_max_holder_val*-1);
                        amo7_motors[amo7_stepper_motor_number].step_holder = tmp;
                        if (amo7_alt_mode) amo7_manual_stepping(amo7_stepper_motor_number, amo7_microstep_number, 1);
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
                    tmp = amo7_motors[amo7_stepper_motor_number].moving_voltage + 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_motors[amo7_stepper_motor_number].moving_voltage = tmp;
                    break;
                case holding_voltage_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_motors[amo7_stepper_motor_number].holding_voltage + 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_motors[amo7_stepper_motor_number].holding_voltage = tmp;
                    amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                    break;
                case coarse_display	:
                    break;
                case step_counter               	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_motors[amo7_stepper_motor_number].step_holder + (_BV(3 - amo7_microstep_number))*10;
                    if (tmp>amo7_max_holder_val) tmp=amo7_max_holder_val;
                    if (tmp<(amo7_max_holder_val*-1)) tmp=(amo7_max_holder_val*-1);
                    amo7_motors[amo7_stepper_motor_number].step_holder = tmp;
                    if (amo7_alt_mode) amo7_manual_stepping(amo7_stepper_motor_number, amo7_microstep_number, 10);
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
                    tmp = amo7_motors[amo7_stepper_motor_number].moving_voltage - 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_motors[amo7_stepper_motor_number].moving_voltage = tmp;
                    break;
                case holding_voltage_output	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_motors[amo7_stepper_motor_number].holding_voltage - 20;
                    if (tmp>amo7_max_V) tmp=amo7_max_V;
                    if (tmp<0) tmp=0;
                    amo7_motors[amo7_stepper_motor_number].holding_voltage = tmp;
                    amo7_stepper_dac_update(amo7_stepper_motor_number, 0);
                    break;
                case coarse_display	:
                    break;
                case step_counter	:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(5);
                    tmp = amo7_motors[amo7_stepper_motor_number].step_holder - 10 * (_BV(3 - amo7_microstep_number));
                    if (tmp>amo7_max_holder_val) tmp=amo7_max_holder_val;
                    if (tmp<(amo7_max_holder_val*-1)) tmp=(amo7_max_holder_val*-1);
                    amo7_motors[amo7_stepper_motor_number].step_holder = tmp;
                    if (amo7_alt_mode) amo7_manual_stepping(amo7_stepper_motor_number, amo7_microstep_number, -10);
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
        amo6_encoder_val_prev = 0;
        amo6_encoder_val = 0;
    }
    else {
        int8_t val = amo6_encoder_val - amo6_encoder_val_prev;
        switch (tag) {
            case moving_voltge_output	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_motors[amo7_stepper_motor_number].moving_voltage + val;
                if (tmp>amo7_max_V) tmp=amo7_max_V;
                if (tmp<0) tmp=0;
                amo7_motors[amo7_stepper_motor_number].moving_voltage = tmp;
                break;
            case holding_voltage_output	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_motors[amo7_stepper_motor_number].holding_voltage + val;
                if (tmp>amo7_max_V) tmp=amo7_max_V;
                if (tmp<0) tmp=0;
                amo7_motors[amo7_stepper_motor_number].holding_voltage = tmp;
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
                tmp = amo7_motors[amo7_stepper_motor_number].step_holder + val * (_BV(3 - amo7_microstep_number));
                if (tmp>amo7_max_holder_val) {
                    tmp=amo7_max_holder_val;
                }
                if (tmp<(amo7_max_holder_val*-1)) {
                    tmp=(amo7_max_holder_val*-1);
                }
                amo7_motors[amo7_stepper_motor_number].step_holder = tmp;
                if (amo7_alt_mode && labs(tmp) < amo7_max_holder_val) amo7_manual_stepping(amo7_stepper_motor_number, amo7_microstep_number, val);
                break;
            case stepper_motor_counter    	:
                val = val/10;
                if (val!=0) {
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                }
                tmp = amo7_stepper_motor_number + val;
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
                tmp = amo7_microstep_number + val;
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

void amo6_serial_parse () {
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
            if (strcmp(token[2], "m") == 0||strcmp(token[2], "M") == 0){
                amo7_motors[channel-1].moving_voltage = (int) tmp;
                double voltage_output = amo7_motors[channel-1].moving_voltage*4.096/256;
                printf("vout.w : set motor #%d to moving at %1.3fV\n", channel,voltage_output);
            }
            else if (strcmp(token[2], "h") == 0||strcmp(token[2], "H") == 0){
                amo7_motors[channel-1].holding_voltage = (int) tmp;
                double voltage_output = amo7_motors[channel-1].holding_voltage*4.096/256;
                printf("vout.w : set motor #%d to holding at %1.3fV\n", channel, voltage_output);
                amo7_stepper_dac_update(channel-1, 0);
            }
            else if (strcmp(token[2], "p") == 0||strcmp(token[2], "P") ==0){
                amo7_motors[channel-1].pfd_voltage = (int) tmp;
                double voltage_output = amo7_motors[channel-1].pfd_voltage*4.096/256;
                printf("vout.w : set motor #%d pfd to %1.3fV\n", channel,voltage_output);
                amo7_stepper_dac_update(amo7_stepper_motor_number, 2);
            }
        }
    }
    else if(strcmp(token[0],"vout.r")==0 && i==3) { //read moving voltage
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            double tmp = 0;
            if (strcmp(token[2], "m") == 0 || strcmp(token[2], "M") == 0){
                tmp = amo7_motors[channel-1].moving_voltage*4.096/256;
            }
            else if (strcmp(token[2], "h") == 0 ||strcmp(token[2], "H") == 0){
                tmp = amo7_motors[channel-1].holding_voltage*4.096/256;
            }
            else if (strcmp(token[2], "p") == 0 ||strcmp(token[2], "P") == 0){
                tmp = amo7_motors[channel-1].pfd_voltage*4.096/256;
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
                amo7_motors[channel-1].power =false;
                printf("out.w : motor %d disabled\n", channel);
            }
            else if (tmp == 1){
                amo7_motors[channel-1].power =true;
                printf("out.w : motor %d enabled\n", channel);
            }
            amo7_motor_config(channel-1, 1, 0);
        }
    }
    else if(strcmp(token[0],"out.r")==0 && i == 2) {  //read on/off
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            printf("%d\n", amo7_motors[channel-1].power);
        }
    }
    else if(strcmp(token[0],"move.w")==0 && i == 3) { //write move
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);     
        if (channel <= 12 && channel >=1){
            bool queuedup = false;
            for(int j=0; j < amo7_queue_index; j++){  //make sure motor isn't queued up
                if (channel-1 == amo7_step_queue[j][0]) queuedup = true;
            }
            if (queuedup == false && amo7_queue_index <= 11){
                char *move_tmp[2];                    //split input into steps
                move_tmp[0] = strtok(token[2], ", ");
                move_tmp[1] = strtok(NULL, ", ");
                long tmp2[2] = {atol(move_tmp[0]), atol(move_tmp[1])};
                long step_holder_tmp = (labs(tmp2[0]) << 3) * (signbit(tmp2[0])?-1:1) + labs(tmp2[1]) * (signbit(tmp2[1])?-1:1);
                if (labs(step_holder_tmp) >= amo7_max_holder_val){
                    step_holder_tmp = (amo7_max_holder_val) * (signbit(step_holder_tmp)?-1:1);
                    tmp2[0] = (labs(step_holder_tmp) >> 3) * (signbit(step_holder_tmp)?-1:1);
                    tmp2[1] = 0;
                }
                amo7_motors[channel-1].step_holder = step_holder_tmp;
                amo7_move_config(channel-1, false);
                printf("move.w: motor #%d set to: %ld (full), %ld (eighths)\n", channel, tmp2[0], tmp2[1]);
            }
            else {
                printf("move.w invalid: motor currently queued up to move\n");
            }
        }
    }
    else if(strcmp(token[0],"move.r")==0 && i == 2) { //read step array
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            int tmp2[2];
            tmp2[0] = (labs(amo7_motors[channel-1].step_holder) >> 3) * (signbit(amo7_motors[channel-1].step_holder)?-1:1);
            tmp2[1] = labs(amo7_motors[amo7_stepper_motor_number].step_holder) & 0x7;
            printf("full steps: %d, eighth steps: %d\n", tmp2[0], tmp2[1]);
        }
    }
    else if(strcmp(token[0],"calib.w") == 0 && i == 2) {  //calibrate array
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(5);
        int channel = atoi(token[1]);
        if (channel<=12 && channel >=1){
            bool queuedup = false;
            for(int j=0; j< amo7_queue_index; j++){  //make sure motor isn't queued up
                if (channel-1 == amo7_step_queue[j][0]) queuedup = true;
            }
            if (queuedup == false){
                if (!amo7_alt_mode){
                    amo7_motors[channel-1].move_holder = 0;
                    amo7_motors[channel-1].step_holder = 0;
                }
                else if (amo7_motors[channel-1].sensor) {
                    amo7_move_config(channel-1, true);
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
            tmp = 1000000/tmp;
            if (tmp > amo7_max_delay_us) tmp = amo7_max_delay_us;
            if (tmp < amo7_min_delay_us) tmp = amo7_min_delay_us;
            amo7_motors[channel-1].speed_delay_us = (long) tmp;
            double speed = 1000000/amo7_motors[channel-1].speed_delay_us;
            printf("speed.w : set motor #%d speed to %.2lf steps/s\n", channel, speed);
        }
    }
    else if(strcmp(token[0],"speed.r")==0 && i==2) { //read speed
        int channel = atoi(token[1]);
        if (channel <= 12 && channel >=1){
            double tmp = 1000000/amo7_motors[channel-1].speed_delay_us;
            printf("%.2lf steps/s\n", tmp);
        }
    }
    else if(strcmp(token[0],"accel.toggle")==0 && i == 1) {
        amo7_global_acceleration = !amo7_global_acceleration;
        printf("acceleration: set to %d\n", amo7_global_acceleration);
    }
    else if(strcmp(token[0],"round.toggle")==0 && i == 1) {
        amo7_rounding_mode = !amo7_rounding_mode;
        printf("rounding steps: set to %d\n", amo7_rounding_mode);
    }
    else if(strcmp(token[0],"alt.toggle")==0 && i == 1) {
        amo7_alt_mode = !amo7_alt_mode;
        printf("alt mode: set to %d\n", amo7_alt_mode);
    }
    else if(strcmp(token[0],"back.toggle")==0 && i == 1) {
        amo7_back_account = !amo7_back_account;
        printf("alt mode: set to %d\n", amo7_back_account);
    }
    else if(strcmp(token[0],"id?")==0 && i == 1) {
        printf("%s\n", device_name);
        printf("Device ID : %s\n", device_id);
        printf("Hardware ID : %s\n", hardware_id);
        printf("Firmware ID : %s\n", firmware_id);
    }
    else if(strcmp(token[0],"help")==0) {
        printf("Commands:\nvout.w [motor number] [mode] [voltage]\nvout.r [motor number] [mode]\nout.w [motor number] [enable]\nout.r [motor number]\nmove.w [motor number] [full steps, eighth steps]\nmove.r [motor number]\ncalib.w [motor number]\nspeed.w [motor number] [speed]\nspeed.r [motor number]\naccel.toggle\nround.toggle\nalt.toggle\nback.toggle\nid?\n");
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
    double output_volts = amo7_motors[amo7_stepper_motor_number].moving_voltage*4.096/256;
    sprintf(text_buf, "%1.3f", output_volts);
    CleO.StringExt(FONT_SANS_0, 160+3, 160+2, amo6_screen_text_color, TL, 0, 0, "Moving");
    CleO.StringExt(FONT_SANS_4, 280, 200, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_3, 290, 200+2, amo6_screen_text_color, MM, 0, 0, "V");
    
    //Holding Voltage
    CleO.Tag(holding_voltage_output);
    CleO.RectangleColor(amo6_screen_select[holding_voltage_output] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 280-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    double holding_volts = amo7_motors[amo7_stepper_motor_number].holding_voltage*4.096/256;
    sprintf(text_buf, "%1.3f", holding_volts);
    CleO.StringExt(FONT_SANS_0, 160+3, 240+2, amo6_screen_text_color, TL, 0, 0, "Holding");
    CleO.StringExt(FONT_SANS_4, 280, 280, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_3, 290, 280+2, amo6_screen_text_color, MM, 0, 0, "V");
    
    //Move Button
    CleO.Tag(move_button);
    CleO.RectangleColor(amo7_motors[amo7_stepper_motor_number].enable ? MY_GREEN : MY_RED);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    if (amo7_motors[amo7_stepper_motor_number].enable){
        CleO.StringExt(FONT_SANS_5, 400, 240, amo6_screen_text_color, MM, 0, 0, "MOVE");
    }
    else if (amo7_step_queue[0][0] == amo7_stepper_motor_number) {
        CleO.StringExt(FONT_SANS_4, 400, 240, amo6_screen_text_color, MM, 0, 0, "MOVING");
    }
    else {
        CleO.StringExt(FONT_SANS_4, 400, 240, amo6_screen_text_color, MM, 0, 0, "QUEUED");
    }
    if (amo7_alt_mode){
        CleO.RectangleColor(MY_RED);
        CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
        CleO.StringExt(FONT_SANS_4, 400, 240, amo6_screen_text_color, MM, 0, 0, "MANUAL");
    }
    
    //Coarse Steps
    CleO.Tag(coarse_display);
    CleO.RectangleColor(amo6_screen_select[coarse_display] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 40-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_0, 320+3, 0+2, amo6_screen_text_color, TL, 0, 0, "Coarse Display");
    double total_angle = amo7_motors[amo7_stepper_motor_number].step_holder * amo7_motors[amo7_stepper_motor_number].step_size / 8;
    sprintf(text_buf, "%.2f", total_angle);
    if (labs(total_angle) >= 1000 || total_angle <= -100){
        CleO.StringExt(FONT_SANS_4, 459, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    else {
        CleO.StringExt(FONT_SANS_5, 459, 40, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    CleO.StringExt(FONT_SANS_2, 465, 20, amo6_screen_text_color, MM, 0, 0, "o");
    
    //Calibrate Button
    CleO.Tag(calibrate_button);
    CleO.RectangleColor(amo7_motors[amo7_stepper_motor_number].enable ? MY_GREEN : MY_RED);
    CleO.RectangleXY(400-2*AMO6_SCREEN_OFFSET, 120-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    if (amo7_alt_mode){
        CleO.StringExt(FONT_SANS_2, 400, 110, amo6_screen_text_color, MM, 0, 0, "CALIBRATE");
        CleO.StringExt(FONT_SANS_2, 400, 130, amo6_screen_text_color, MM, 0, 0, "WAVEPLATE");
    }
    else {
        CleO.StringExt(FONT_SANS_3, 400, 120, amo6_screen_text_color, MM, 0, 0, "CALIBRATE");
    }
    
    //Fine Steps
    CleO.Tag(step_counter);
    CleO.RectangleColor(amo6_screen_select[step_counter] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 40-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_0, 160+3, 0+2, amo6_screen_text_color, TL, 0, 0, "Step Display");
    long tmp2[2] = {(labs(amo7_motors[amo7_stepper_motor_number].step_holder) >> 3) * (signbit(amo7_motors[amo7_stepper_motor_number].step_holder)?-1:1), labs(amo7_motors[amo7_stepper_motor_number].step_holder) & 0x7};
    sprintf(text_buf, "%ld", tmp2[0]);
    if (labs(tmp2[0]) >= 1000 && labs(tmp2[0]) < 10000){
        CleO.StringExt(FONT_SANS_4, 248, 43, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    else if (labs(tmp2[0]) >= 10000){
        CleO.StringExt(FONT_SANS_3, 248, 45, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    else {
        CleO.StringExt(FONT_SANS_5, 248, 39, amo6_screen_text_color, MR, 0, 0, text_buf);
    }
    sprintf(text_buf, "%ld/8", tmp2[1]);
    CleO.StringExt(FONT_SANS_3, 290, 40+5, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_2, 305, 40+6, amo6_screen_text_color, MR, 0, 0, "s");
    
    //Fine Step Adjustment
    CleO.Tag(fine_step_adjustment);
    CleO.RectangleColor(amo6_screen_select[fine_step_adjustment] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 120-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_0, 160+3, 80+2, amo6_screen_text_color, TL, 0, 0, "Microsteps");
    sprintf(text_buf, "1/%d ", (1 << amo7_microstep_number));
    CleO.StringExt(FONT_SANS_6, 240, 120, amo6_screen_text_color, MM, 0, 0, text_buf);
    sprintf(text_buf, "%.3f", (double) amo7_motors[amo7_stepper_motor_number].step_size/(1 << amo7_microstep_number));
    CleO.StringExt(FONT_SANS_1, 305, 150, amo6_screen_text_color, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_TINY, 305, 142, amo6_screen_text_color, ML, 0, 0, " o");
    
    //Stepper Motor Counter
    CleO.Tag(stepper_motor_counter);
    CleO.RectangleColor(amo6_screen_select[stepper_motor_counter] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(80-2*AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    CleO.StringExt(FONT_SANS_0, 0+3, 0+2, amo6_screen_text_color, TL, 0, 0, "Motor Number");
    sprintf(text_buf, "#%d", amo7_stepper_motor_number+1);
    CleO.StringExt(FONT_SANS_6, 80, 80, amo6_screen_text_color, MM, 0, 0, text_buf);

    //ON/OFF Switch
    CleO.Tag(on_off_switch);
    CleO.RectangleColor(amo7_motors[amo7_stepper_motor_number].power ? MY_GREEN : MY_RED);
    CleO.RectangleXY(80-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    strcpy(text_buf, amo7_motors[amo7_stepper_motor_number].power? "ON" : "OFF");
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
            amo7_motors[amo7_stepper_motor_number].power = !amo7_motors[amo7_stepper_motor_number].power;
            amo7_motor_config(amo7_stepper_motor_number, 0, 0);
            sel = !amo6_screen_select[on_off_switch];
            for(i=0;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            break;
        case move_button	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            for(i=0;i<move_button;i++) amo6_screen_select[i]=0;
            for(i=move_button+1;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            if (amo7_motors[amo7_stepper_motor_number].enable && !amo7_alt_mode) amo7_move_config(amo7_stepper_motor_number, false);
            break;
        case calibrate_button	:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            amo7_motor_config(amo7_stepper_motor_number, 1, 0);
            for(i=0;i<calibrate_button;i++) amo6_screen_select[i]=0;
            for(i=calibrate_button+1;i<AMO6_SCREEN_TAGS;i++) amo6_screen_select[i]=0;
            if (amo7_motors[amo7_stepper_motor_number].enable){
                if (!amo7_alt_mode) {
                    amo7_motors[amo7_stepper_motor_number].move_holder = 0;
                    amo7_motors[amo7_stepper_motor_number].step_holder = 0;
                }
                else if (amo7_motors[amo7_stepper_motor_number].sensor){
                    amo7_move_config(amo7_stepper_motor_number, true);
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
void amo7_dac_init() {
    uint32_t init_input = 8;                    //command code 0001 in reverse
    init_input |= (15 << 4);                    //all dac address code
    AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_LOAD));             //CS/LD low to begin serial input
    for (int i=0; i<=23; i++){
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_CLOCK));        //dac clocks sdi in on rising edge
        if (init_input & _BV(0)){
            AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_INPUT);
        }
        else {
            AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_INPUT));
        }
        AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_CLOCK);
        init_input >>= 1;
    }
    AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_LOAD);                //CS/LD high to finish serial input 
    _delay_ms(10);
}

void amo7_stepper_dac_update (int motor_num, int mode) {
    uint16_t dac_input = 0x3000;        //command code 0011
    uint8_t address_code = 2*(motor_num % 3);
    uint8_t portc_tmp = AMO7_BOARD_PORT_R;  //store current board port settings
    amo7_board_config(motor_num, true);
    switch (mode){                      //mode: 0 = holding, 1 = moving, 2 = pfd
        case 0:
            dac_input |= amo7_motors[motor_num].holding_voltage;   
            break;
        case 1:
            dac_input |= amo7_motors[motor_num].moving_voltage;
            break;
        case 2:
            address_code += 1;
            dac_input |= amo7_motors[motor_num].pfd_voltage;
            break;
    }
    dac_input |= (address_code << 8);
    AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_LOAD));     //CS/LD low to begin serial input
    for (int i=0; i<=15; i++){
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_CLOCK));//dac clocks sdi in on rising edge
        if (dac_input & _BV(15)){
            AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_INPUT);        
        }
        else {
            AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_INPUT));
        }
        AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_CLOCK);
        dac_input <<= 1;
    }
    AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_INPUT));    //+8 don't-care bits since message must be 24b
    for (int i=0; i<=7; i++){           
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_CLOCK));
        AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_CLOCK);
    }
    AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_LOAD);        //CS/LD high to finish serial input
    AMO7_BOARD_PORT = portc_tmp;                    //restore board port
}

void amo7_background_stepping (){
    if (amo7_queue_index != 0 && !amo7_motor_moving){
        if (amo7_new_motor){                 
            printf("   new motor\n");
            amo7_board_config(amo7_step_queue[0][0], true);        //set board
            amo7_stepper_dac_update(amo7_step_queue[0][0], 1);     //change to moving voltage
            amo7_new_motor = false;
            if (amo7_rounding_mode) {           //move rounding steps
                printf("   rounding: %d\n", amo7_step_queue[0][1]);
                amo7_manual_stepping(amo7_step_queue[0][0], 3, -amo7_step_queue[0][1]);
                amo7_motors[amo7_step_queue[0][0]].move_holder += 2*amo7_step_queue[0][2];
            }
            amo7_motor_config(amo7_step_queue[0][0], amo7_step_queue[0][2], 0);//config after
        }
        long current_steps = (labs(amo7_motors[amo7_step_queue[0][0]].move_holder) >> (3 - amo7_queued_microstep_counter)) * (signbit(amo7_motors[amo7_step_queue[0][0]].move_holder)?-1:1);
        printf("        steps to move: %ld\n", current_steps);
        if (current_steps == 0 && (amo7_queued_microstep_counter < amo7_max_microstep_number)) {                                        //set new microstep
            amo7_queued_microstep_counter += 1;
            amo7_motor_config(amo7_step_queue[0][0], amo7_step_queue[0][2], amo7_queued_microstep_counter);
            printf("   new microstep: %d\n", amo7_queued_microstep_counter);
        }
        else if (current_steps == 0 && amo7_queued_microstep_counter >= amo7_max_microstep_number){              //end of current motor, reset
            TCCR1B &= 0xf8;
            printf("   end of motor\n");
            amo7_motors[amo7_step_queue[0][0]].move_holder = amo7_motors[amo7_step_queue[0][0]].step_holder;
            //update queue
            amo7_motors[amo7_step_queue[0][0]].enable = true;
            amo7_queued_microstep_counter = 0;
            amo7_new_motor = true;
            amo7_stepper_dac_update(amo7_step_queue[0][0], 0);
            for (int i = 0; i < amo7_queue_index; i++){
                amo7_step_queue[i][0] = amo7_step_queue[i+1][0];    //update motor num
                amo7_step_queue[i][1] = amo7_step_queue[i+1][1];    //update rounding steps
                amo7_step_queue[i][2] = amo7_step_queue[i+1][2];    //update direction
            }
            amo7_queue_index -= 1;
        }
        else if (current_steps != 0){   //step
            uint16_t ocr_tmp = round(amo7_motors[amo7_step_queue[0][0]].speed_delay_us/amo7_timer_val_to_us);
            //config accel
            if (amo7_global_acceleration && amo7_queued_microstep_counter == 0){
                amo7_steps_to_max_min = round((amo7_starting_delay_us - amo7_motors[amo7_step_queue[0][0]].speed_delay_us)/amo7_timer_val_to_us/amo7_accel_rate);
                if (current_steps > (2 * amo7_steps_to_max_min)){
                    amo7_accel_steps_tmp = amo7_steps_to_max_min;
                    amo7_local_acceleration = true;
                }
                else {
                    amo7_local_acceleration = false;
                }
                ocr_tmp = round(amo7_starting_delay_us/amo7_timer_val_to_us);
            }
            OCR1A = ocr_tmp;
            amo7_motor_moving = true;
            TCCR1B |= _BV(CS11);    //enable timer and set prescaler to 8
        }
    }
}

void amo7_board_config(int motor_num, bool out) {
    uint8_t board_num = 0;
    uint8_t board_tmp = AMO7_BOARD_PORT;
    switch ((motor_num-(motor_num % 3))/3) {
        case 0:
            board_num = AMO7_BOARD_PIN_0;
            break;
        case 1:
            board_num = AMO7_BOARD_PIN_1;
            break;
        case 2:
            board_num = AMO7_BOARD_PIN_2;
            break;
        case 3:
            board_num = AMO7_BOARD_PIN_3;
            break;
    }
    if (out){
        board_tmp |= 0x0f;
        board_tmp &= ~(_BV(board_num));
    }
    else {
        board_tmp &= 0x0f;
        board_tmp |= _BV(board_num + 4);  //C0-C3 = out boards, C4-C7 = in boards 
    }        
    AMO7_BOARD_PORT = board_tmp;
}

void amo7_motor_config(int motor_num, bool dir, int msn) {
    uint16_t reg_input = 0x18C7;        //0(slp),1(r3),2(e3),6(r2),7(e2),11(r1),12(e1)
    int motor_on_board = motor_num % 3;
    int ms_shift = 14 - 5*(motor_on_board);  //Shifts microstepping to appropriate pin output
    int board_num_min = motor_num-(motor_on_board);
    uint8_t portc_tmp = AMO7_BOARD_PORT_R;
    amo7_board_config(motor_num, true);
    reg_input |= msn<<ms_shift;
    reg_input |= dir<<(ms_shift-1);
    switch (motor_on_board){            //assign step port
        case 0:
            amo7_motor_shift = AMO7_STEP_PIN_0;
            break;
        case 1:
            amo7_motor_shift = AMO7_STEP_PIN_1;
            break;
        case 2:
            amo7_motor_shift = AMO7_STEP_PIN_2;
            break;
    }
    for (int i = board_num_min; i <= board_num_min+2; i++){ //enable ON motors within board
        if (amo7_motors[i].power){             
            reg_input &= ~(_BV(12-5*(i%3))); 
        }
    }
    for (int i=0; i<=15; i++){
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DRV_CLOCK));    //drv clocks in on rising edge
        if (reg_input & _BV(0)){
            AMO7_DRV_DAC_PORT |= _BV(AMO7_DRV_INPUT);
        }
        else {
            AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DRV_INPUT));
        }
        AMO7_DRV_DAC_PORT |= _BV(AMO7_DRV_CLOCK);
        reg_input >>= 1;
    }
    AMO7_DRV_DAC_PORT |= _BV(AMO7_DRV_LOAD);
    AMO7_DRV_DAC_PORT &= 0xf1;                          //Set A1-A3 low
    AMO7_BOARD_PORT = portc_tmp;
}

void amo7_move_config (int motor_num, bool calib){
    int rounding_steps = 0;
    if (calib && amo7_sensor_feedback(motor_num)){
        amo7_motors[motor_num].move_holder = amo7_max_holder_val;
        PCICR |= (_BV(PCIE2) | _BV(PCIE1));
    }
    else {
        rounding_steps = amo7_motors[motor_num].move_holder % 8;
        amo7_motors[motor_num].move_holder = amo7_motors[motor_num].step_holder - amo7_motors[motor_num].move_holder;
        if (amo7_motors[motor_num].move_holder == 0){   //reset move_holder and exit
            amo7_motors[motor_num].move_holder = amo7_motors[motor_num].step_holder;
            return;
        }
    }
    amo7_motors[motor_num].enable = false;          //stops further instructions to motor
    //update queue
    amo7_step_queue[amo7_queue_index][0] = motor_num;
    amo7_step_queue[amo7_queue_index][1] = rounding_steps;
    amo7_step_queue[amo7_queue_index][2] = amo7_motors[motor_num].move_holder>0 ? true:false;
    if (amo7_step_queue[amo7_queue_index][2] && amo7_back_account){
        
    }
    amo7_motors[motor_num].move_holder = labs(amo7_motors[motor_num].move_holder);
    amo7_queue_index += 1;
}

void amo7_manual_stepping (int motor_num, int ms, int steps) {
    int tmp_motor_shift = 0;
    switch (motor_num % 3){         //assign step port
        case 0:
            tmp_motor_shift = AMO7_STEP_PIN_0;
            break;
        case 1:
            tmp_motor_shift = AMO7_STEP_PIN_1;
            break;
        case 2:
            tmp_motor_shift = AMO7_STEP_PIN_2;
            break;
    }
    amo7_motors[motor_num].move_holder += steps;
    if (steps > 0) {
        amo7_motor_config(motor_num, 1, ms);
    }
    else if (steps < 0) {
        amo7_motor_config(motor_num, 0, ms);
        steps = abs(steps);
    }
    while (steps > 0){
        AMO7_STEP_PORT |= _BV(tmp_motor_shift);
        _delay_ms(2);
        AMO7_STEP_PORT &= ~(_BV(tmp_motor_shift));
        _delay_ms(1);
        steps -= 1;
    }
}

bool amo7_sensor_feedback (int motor_num) {
    amo7_board_config(motor_num, false);
    volatile uint8_t *pin = 0;
    int sensor_pin = 0;
    switch (motor_num % 3){
        case 0:
            pin = &AMO7_FEEDBACK_PORT1_R;
            sensor_pin = 0;
            break;
        case 1:
            pin = &AMO7_FEEDBACK_PORT2_R;
            sensor_pin = 7;
            break;
        case 2:
            pin = &AMO7_FEEDBACK_PORT2_R;
            sensor_pin = 3;
            break;
    }
    return *pin & _BV(sensor_pin);
}
#endif // AMO7_H
