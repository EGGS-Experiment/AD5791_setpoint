#ifndef AMO7_HPP
#define AMO7_HPP 1
#include "amo7.h"


//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - BUTTONS
//////////////////////////////////////////////////////////////////////////////////////
void amo6_buttons_update(){
    bool sw1_now = (PINB >> PB6) & 0x01;
    bool sw2_now = (PINB >> PB5) & 0x01;

    //find active screen tag
    uint8_t tag;
    for (tag=0; tag<AMO6_SCREEN_TAGS-1; ++tag) {
        if (amo6_screen_select[tag]==1) break;
    };

    // (-) sw1 pressed (red)
    if (amo6_sw1_pushed) {
        // (+) only update if other button is not pressed
        if (!amo6_count_latch[1]){
            amo6_count_latch[0] = true; // start counting hold time
            if (!sw1_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
                switch (tag) {
                    case voltage_output:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(1);
                        long tmp = amo7_DAC_cnts - 1;
                        if (tmp > AMO7_CNTS_MAX) tmp = AMO7_CNTS_MAX;
                        if (tmp < AMO7_CNTS_MIN) tmp = AMO7_CNTS_MIN;
                        amo7_DAC_cnts = tmp;
                        break;
                }
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            }
        } else {
            // (+) reset long-press variables
            amo6_count_latch[1] = false;
            amo6_hold_count[1] = 0;
        }
        amo6_sw1_pushed = false;
    }
    
    // (+) sw2 pressed (black)
    if (amo6_sw2_pushed) {
        // (+) only update if other button is not pressed
        if (!amo6_count_latch[0]){
            amo6_count_latch[1] = true; // start counting hold time
            if (!sw2_now) { //ensure sw is pressed to workaround a bug in the mechanical switch
                switch (tag) {
                    case voltage_output:
                        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                        _delay_ms(1);
                        long tmp = amo7_DAC_cnts + 1;
                        if (tmp > AMO7_CNTS_MAX) tmp = AMO7_CNTS_MAX;
                        if (tmp < AMO7_CNTS_MIN) tmp = AMO7_CNTS_MIN;
                        amo7_DAC_cnts = tmp;
                        break;
                }
                AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
            }
        } else {
            // (+) reset long-press variables
            amo6_count_latch[0] = false;
            amo6_hold_count[0] = 0;
        }
        amo6_sw2_pushed = false;
    }
    // (-) sw1 held (red)
    if (amo6_count_latch[0]){
        // increment hold_counter
        if (amo6_hold_count[0] < AMO6_HOLD_THRESHOLD) ++(amo6_hold_count[0]);
        // update values
        if (amo6_hold_count[0] >= AMO6_HOLD_THRESHOLD){
            switch (tag) {
                case voltage_output:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                    long tmp = amo7_DAC_cnts - 20;
                    if (tmp > AMO7_CNTS_MAX) tmp = AMO7_CNTS_MAX;
                    if (tmp < AMO7_CNTS_MIN) tmp = AMO7_CNTS_MIN;
                    amo7_DAC_cnts = tmp;
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

    // (+) sw2 held (black)
    if (amo6_count_latch[1]){
        // increment hold_counter
        if (amo6_hold_count[1] < AMO6_HOLD_THRESHOLD) ++(amo6_hold_count[1]);
        // update values
        if (amo6_hold_count[1] >= AMO6_HOLD_THRESHOLD){
            switch (tag) {
                case voltage_output:
                    AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
                    _delay_ms(1);
                    long tmp = amo7_DAC_cnts + 20;
                    if (tmp > AMO7_CNTS_MAX) tmp = AMO7_CNTS_MAX;
                    if (tmp < AMO7_CNTS_MIN) tmp = AMO7_CNTS_MIN;
                    amo7_DAC_cnts = tmp;
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
    
    // encoder turn
    static int8_t amo6_encoder_val_prev;
    if ((amo6_encoder_val_prev == amo6_encoder_val) || (tag != tag_old)) {
        amo6_encoder_val_prev = 0;
        amo6_encoder_val = 0;
    } else {
        // scale encoder value
        const int32_t val = (amo6_encoder_val - amo6_encoder_val_prev) / 10;
        if (val != 0) {
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);  //0
            _delay_ms(1);
            AMO6_BUZZER_nEN_PORT |= _BV(AMO6_BUZZER_nEN);   //1
            switch (tag) {
                case voltage_output:
                    long tmp = amo7_DAC_cnts + val;
                    if (tmp > AMO7_CNTS_MAX) tmp = AMO7_CNTS_MAX;
                    if (tmp < AMO7_CNTS_MIN) tmp = AMO7_CNTS_MIN;
                    amo7_DAC_cnts = tmp;
                    break;
            }
            // reset encoder values
            amo6_encoder_val_prev = 0;
            amo6_encoder_val = 0;
        }
    }
    tag_old = tag;
}


//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - SERIAL
//////////////////////////////////////////////////////////////////////////////////////
void amo6_serial_parse(){
    char delimiters[] = " ";
    char *token[8];
    uint8_t i = 0;
    token[0] = strtok(amo6_serial_string, delimiters);
    ++i;

    //split the serial string by the delimiter
    while (i < 8) {
        token[i] = strtok(NULL, delimiters);
        if (token[i] == NULL) break;
        ++i;
    }
    /////////////////////////////////////// W R I T E S ////////////////////////////////
    if ((strcmp(token[0],"vout.w") == 0) && (i == 2)) {      //write voltage
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(3);
        const double vout_tmp = atof(token[1]);
        if ((vout_tmp > AMO7_VOUT_MAX) || (vout_tmp < AMO7_VOUT_MIN)) {
            printf("Invalid voltage entry.\n");
        } else {
            amo7_DAC_cnts = vout_tmp * AMO7_VOUT_TO_CNTS;
            printf("%.2fV\n", amo7_DAC_cnts * AMO7_CNTS_TO_VOUT);
        }
    } else if((strcmp(token[0],"out.w") == 0) && (i == 2)) {
        AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN);
        _delay_ms(3);
        const int state = atoi(token[1]);
        if ((state != 0) && (state != 1)) printf("Invalid state entry.\n");
        else {
            amo7_DAC_state = state;
            if (state == 0) printf("OFF\n");
            else printf("ON\n");
        }
    /////////////////////////////////////////////////// R E A D S //////////////////////////
    } else if((strcmp(token[0],"vout.r") == 0) && (i == 1)) {
        const double tmp = amo7_DAC_cnts * AMO7_CNTS_TO_VOUT;
        printf("%.2fV\n", tmp);
    } else if((strcmp(token[0],"out.r") == 0) && (i == 1)) {
        if (amo7_DAC_state == 1) printf("ON\n");
        else printf("OFF\n");
    } else if((strcmp(token[0],"id?")==0) && (i == 1)) {
        printf("%s\n", device_name);
        printf("Device ID: %s\n", device_id);
        printf("Hardware ID: %s\n", hardware_id);
        printf("Firmware ID: %s\n", firmware_id);
    } else if(strcmp(token[0],"help") == 0) {
        printf("Commands:\n");
        printf("\tvout.w [voltage]\n");
        printf("\tvout.r\n");
        printf("\tout.w [enable]\n");
        printf("\tout.r\n");
        printf("\tid?\n");
    } else {
        printf("Command not recognized.\nType 'help' for list of commands.\n");
    }
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}

//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - SCREEN
//////////////////////////////////////////////////////////////////////////////////////
void amo6_screen_draw(){
    // Start Drawing Screen
    CleO.Start();
    CleO.RectangleJustification(MM);
    CleO.SetBackgroundcolor(MY_BLACK);
    char text_buf[50];
    
    //Voltage Output
    CleO.Tag(voltage_output);
    CleO.RectangleColor(amo6_screen_select[voltage_output] ? CLEO_SELECT : MY_WHITE);
    CleO.RectangleXY(240-2*AMO6_SCREEN_OFFSET, 200-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 80-AMO6_SCREEN_OFFSET);
    sprintf(text_buf, "%1.3f", amo7_DAC_cnts * AMO7_CNTS_TO_VOUT);
    CleO.StringExt(FONT_SANS_4, 280, 200, AMO7_SCREEN_TEXT_COLOR, MR, 0, 0, text_buf);
    CleO.StringExt(FONT_SANS_3, 290, 200+2, AMO7_SCREEN_TEXT_COLOR, MM, 0, 0, "V");

    //ON/OFF Switch
    CleO.Tag(on_off_switch);
    CleO.RectangleColor(amo7_DAC_state? MY_GREEN : MY_RED);
    CleO.RectangleXY(80-2*AMO6_SCREEN_OFFSET, 240-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET, 160-AMO6_SCREEN_OFFSET);
    strcpy(text_buf, amo7_DAC_state? "ON" : "OFF");
    CleO.StringExt(FONT_SANS_5, 80, 240, AMO7_SCREEN_TEXT_COLOR, MM, 0, 0, text_buf);

    // Update Screen
    CleO.Show();
}

void amo6_screen_processShortPress () {
    uint8_t i;
    bool sel;
    switch (amo6_screen_current_tag) {
        case voltage_output:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            sel = !amo6_screen_select[voltage_output];
            for(i=0; i<AMO6_SCREEN_TAGS; ++i) amo6_screen_select[i]=0;
            amo6_screen_select[voltage_output] = sel;
            break;
        case on_off_switch:
            AMO6_BUZZER_nEN_PORT &= ~_BV(AMO6_BUZZER_nEN); //0
            _delay_ms(2);
            amo7_DAC_state = !amo7_DAC_state;
            sel = !amo6_screen_select[on_off_switch];
            for(i=0; i<AMO6_SCREEN_TAGS; ++i) amo6_screen_select[i]=0;
            break;
    }
    AMO6_BUZZER_nEN_PORT |=  _BV(AMO6_BUZZER_nEN); //1
}


//////////////////////////////////////////////////////////////////////////////////////
// AMO7 Hardware
//////////////////////////////////////////////////////////////////////////////////////
void amo7_init () {
    //hardware init
    AMO7_DRV_DAC_DDR = 0xFF;
    AMO7_DRV_DAC_PORT = (_BV(AMO7_DAC_LOAD) | _BV(AMO7_DAC_SYNC));

    //start up DAC
    uint32_t init_input = 0x00000004;                       //set OPGND=0, DACTRI=0, BIN=0, LINCOMP=0
    AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_LOAD));             //bring CS/LD low to begin serial input

    for (uint8_t i=0; i<=23; ++i){                          //enter in all letters of DAC input
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_CLOCK));        //bring clock low since DAC clocks in on rising edge
        if (init_input & _BV(0)){                           //send leftmost digit to input pin
            AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_INPUT);
        } else {
            AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_INPUT));
        }
        AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_CLOCK);           //bring clock high to input bit
        init_input >>= 1;                                   //move to next bit for input
    }
    AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_LOAD);                //CS/LD high to finish serial input
}

void amo7_set_dac(const uint32_t cnts) {
    uint32_t dac_input = 0x00100000 | cnts;             //dac_input holds input for dac as sequential 24-bit word

    AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_LOAD));         //bring CS/LD low to begin serial input

    for (uint8_t i=0; i<=23; ++i){                      //enter in all letters data of dac_input
        AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_CLOCK));    //bring clock low since DAC clocks in on rising edge
        if (dac_input & _BV(23)){                       //send leftmost digit to input pin
            AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_INPUT);        
        } else {
            AMO7_DRV_DAC_PORT &= ~(_BV(AMO7_DAC_INPUT));
        }

        AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_CLOCK);       //bring clock high to input bit
        dac_input <<= 1;                                //move to next bit for input
    }
    AMO7_DRV_DAC_PORT |= _BV(AMO7_DAC_LOAD);            //CS/LD high to finish serial input
}

void amo7_hardware_update(){
    // voltage changed
    if (amo7_DAC_cnts != amo7_DAC_cnts_old) {
        // on to on
        if ((amo7_DAC_state_old) && (amo7_DAC_state_old == amo7_DAC_state)) {
            amo7_set_dac(amo7_DAC_cnts);
        }
        amo7_DAC_cnts = amo7_DAC_cnts_old;
    }

    // power changed
    if (amo7_DAC_state != amo7_DAC_state_old) {
        // off to on
        if (amo7_DAC_state) {
            amo7_set_dac(amo7_DAC_cnts);
        // on to off
        } else {
            amo7_set_dac(0);
        }
        amo7_DAC_state = amo7_DAC_state_old;
    }
}

#endif // AMO7_HPP
