#ifndef AMOCORE_HPP
#define AMOCORE_HPP 1

#include "amo_core.h"

//////////////////////////////////////////////////////////////////////////////////////
// Interrupts
//////////////////////////////////////////////////////////////////////////////////////
ISR(INT3_vect) {}       //ENC_SW
ISR(INT2_vect, ISR_ALIASOF(INT5_vect)); //map ENC_A to unused INT5
ISR(INT1_vect, ISR_ALIASOF(INT5_vect)); //map ENC_B to unused INT5
ISR(INT5_vect) {        //ENC_TURN
    static uint8_t old_AB = 0;  //lookup table index
    static const int8_t enc_states[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };  //encoder lookup table

    old_AB <<= 2;  //store previous state
    old_AB |= (((((PIND>>PD2) & 0x01) << 1) | ((PIND>>PD1) & 0x01)) & 0x03); //add current state
    amo6_encoder_val += enc_states[(old_AB & 0x0f)];
}

ISR(PCINT0_vect) {      //SW1 SW2
    static bool sw1_old = true;
    static bool sw2_old = true;

    //check if sw1 is still pushed
    const bool sw1_now = (PINB>>PB6) & 0x01;
    if (sw1_old && !sw1_now) {
        amo6_sw1_pushed = true;
    }
    sw1_old = sw1_now;

    //check if sw2 is still pushed
    const bool sw2_now = (PINB>>PB5) & 0x01;
    if (sw2_old && !sw2_now) {
        amo6_sw2_pushed = true;
    }
    sw2_old = sw2_now;
}

//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - SCREEN
//////////////////////////////////////////////////////////////////////////////////////
void amo6_ext_init(){
    //SPI Intialization
    SPI_FLEX_02_RST_PORT |= _BV(SPI_FLEX_02_RST); //set reset HI
    //EXT1 Initialization
    AMO6_EXT1_nEN_DDR |= _BV(AMO6_EXT1_nEN); //output
    AMO6_EXT1_nEN_PORT &= ~_BV(AMO6_EXT1_nEN); //0
}

void amo6_screen_init() {
    //Display initialization
    AMO6_CLEO_nPWR_DDR |= _BV(AMO6_CLEO_nPWR);//output
    AMO6_CLEO_nPWR_PORT |= _BV(AMO6_CLEO_nPWR); //1
    AMO6_CLEO_nPWR_PORT &= ~_BV(AMO6_CLEO_nPWR); //0
    char buf_text[40];
    CleO.begin();
    CleO.Display(100);
    CleO.Start();
    CleO.RectangleJustification(MM);
    CleO.SetBackgroundcolor(0x121212UL);
    
    sprintf(buf_text, "%s", device_name);
    CleO.StringExt(FONT_SANS_3, AMO1_SCREEN_WIDTH / 2, 30, AMO7_TEXT_COLOR, MM, 0, 0, buf_text);
    sprintf(buf_text, "Device ID : %s", device_id);
    CleO.StringExt(FONT_BIT_3, 10, 100, AMO7_TEXT_COLOR, ML, 0, 0, buf_text);
    sprintf(buf_text, "Hardware ID : %s", hardware_id);
    CleO.StringExt(FONT_BIT_3, 10, 120, AMO7_TEXT_COLOR, ML, 0, 0, buf_text);
    sprintf(buf_text, "Firmware ID : %s", firmware_id);
    CleO.StringExt(FONT_BIT_3, 10, 140, AMO7_TEXT_COLOR, ML, 0, 0, buf_text);

    sprintf(buf_text, "Starting Up...");
    CleO.StringExt(FONT_BIT_5, AMO1_SCREEN_WIDTH / 2, AMO6_SCREEN_ROW3_Y, AMO7_TEXT_COLOR, MM, 0, 0, buf_text);
    CleO.Show();
    CleO.DisplayRotate(2, 0);
    CleO.LoadFont("@Fonts/DSEG7ClassicMini-BoldItalic.ftfont");
}

void amo6_screen_touch() {
    amo6_screen_processButtons();
    if (amo6_screen_short_press_detected) {
        amo6_screen_processShortPress();
    }
}

void amo6_screen_update() {
    amo6_screen_draw();
    amo6_screen_touch();
}

void amo6_screen_processButtons() {
    CleO.TouchCoordinates(amo6_screen_x, amo6_screen_y, amo6_screen_current_dur, amo6_screen_current_tag);
    amo6_screen_shortPress(&amo6_screen_short_press_detected);
    amo6_screen_last_dur = amo6_screen_current_dur;
}

void amo6_screen_shortPress(bool *press_detected) {
    if ((amo6_screen_current_dur == 1) && (amo6_screen_last_dur == 0) && (!*press_detected)) {
        *press_detected = 1;
    } else {
        *press_detected = 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - BUTTONS
//////////////////////////////////////////////////////////////////////////////////////
void amo6_buttons_init() {
    // ENC_A
    DDRD &= ~_BV(PD2);   //input
    PORTD |= _BV(PD2);   //enable pullup
    EICRA &= ~_BV(ISC21); //enable any edge interrupt
    EICRA |= _BV(ISC20); //enable any edge interrupt
    EIMSK |= _BV(INT2);  //enable interrupt

    // ENC_B
    DDRD &= ~_BV(PD1);   //input
    PORTD |= _BV(PD1);   //enable pullup
    EICRA &= ~_BV(ISC11); //enable any edge interrupt
    EICRA |= _BV(ISC10); //enable any edge interrupt
    EIMSK |= _BV(INT1);  //enable interrupt for the pin

    // ENC_SW
    DDRD &= ~_BV(PD3);   //input
    PORTD |= _BV(PD3);   //enable pullup
    EICRA |= _BV(ISC31); //enable falling edge interrupt
    EICRA &= ~_BV(ISC30); //enable falling edge interrupt
    EIMSK |= _BV(INT3);  //enable interrupt for the pin

    // SW1
    DDRB &= ~_BV(PB6);   //input
    PORTB |= _BV(PB6);   //enable pullup
    PCICR |= _BV(PCIE0); //enable pin change interrupt enable 0
    PCMSK0 |= _BV(PCINT6);//enable interrupt for the pin

    // SW2
    DDRB &= ~_BV(PB5);   //input
    PORTB |= _BV(PB5);   //enable pullup
    PCICR |= _BV(PCIE0); //enable pin change interrupt enable 0
    PCMSK0 |= _BV(PCINT5);//enable interrupt for the pin

    // Buzzer
    AMO6_BUZZER_nEN_DDR |= _BV(AMO6_BUZZER_nEN); //output
    AMO6_BUZZER_nEN_PORT |= _BV(AMO6_BUZZER_nEN); //1
}

//////////////////////////////////////////////////////////////////////////////////////
// AMO6 - SERIAL
//////////////////////////////////////////////////////////////////////////////////////
void amo6_serial_update() {
    char getchar;
    static int i = 0, j_prev = 0;
    //read in next char
    while (getchar = uart_trygetchar()) {
        //parse upon EOL
        if (getchar == '\r' || getchar == '\n') {
            if (i > 0) {
                int j = 0;
                while (j < i) {
                    amo6_serial_string[j] = amo6_serial_buffer[j];
                    amo6_serial_buffer[j] = 0;
                    ++j;
                }
                while (j < j_prev) {
                    amo6_serial_string[j] = 0;
                    ++j;
                }
                j_prev = i;
                i = 0;
                amo6_serial_parse();
            }
        //otherwise add input to buffer
        } else {
            //reset input buffer
            if (i >= amo6_serial_buffer_size) {
                while (i > 0) {
                    amo6_serial_buffer[i] = 0;
                    --i;
                }
                amo6_serial_buffer[i] = 0;
            }
            amo6_serial_buffer[i] = getchar;
            ++i;
        }
    }
}

#endif //AMOCORE_HPP
