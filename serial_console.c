/*
 * serial console
 *
 * Copyright 2013--2015 Christian Schneider <software(at)chschneider(dot)eu>
 *
 * This file is part of the MOTion trap control unit firmware
 * (called "program" in the following).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation, *not* any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include "serial_console.h"

#if SERIAL_BUFFER_SIZE > 255
#error "SERIAL_BUFFER_SIZE must be smaller or equal to 255!"
#endif

#ifdef SERIAL_RX_INTERRUPT
#include <avr/interrupt.h>
//#include <util/atomic.h>

volatile static char serial_buffer[SERIAL_BUFFER_SIZE];
volatile static unsigned int pos_w;  // write position
volatile static unsigned int pos_r;  // read position
volatile static unsigned char num_bytes;  // number of bytes in buffer
#endif  // SERIAL_RX_INTERRUPT

static int echo_on = SERIAL_ECHO_ON;

void uart_init() {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  UCSR0A &= ~(_BV(U2X0));             // single speed
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // enable RX and TX
}

void uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);

  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}

#ifdef SERIAL_RX_INTERRUPT

ISR(USART0_RX_vect) {
  char c = UDR0;

  // test for buffer overflow
  if (num_bytes == SERIAL_BUFFER_SIZE) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = '@';
  }
  else {
    serial_buffer[pos_w] = c;

    num_bytes++;
    pos_w++;
    if (pos_w == SERIAL_BUFFER_SIZE)
      pos_w = 0;

    if (echo_on) {
      loop_until_bit_is_set(UCSR0A, UDRE0);
      UDR0 = c;
    }
  }
}

char uart_getchar(FILE *stream) {
  // wait until buffer contains data (no need for atomic because of char)
  while (num_bytes == 0);

  char c = serial_buffer[pos_r];
  num_bytes--;
  pos_r++;
  if (pos_r == SERIAL_BUFFER_SIZE)
    pos_r = 0;

  return c;
}

char uart_trygetchar() {
  // wait until buffer contains data (no need for atomic because of char)
  //while (num_bytes == 0);
  if (num_bytes == 0) {
    return 0;
  }
  
  char c = serial_buffer[pos_r];
  num_bytes--;
  pos_r++;
  if (pos_r == SERIAL_BUFFER_SIZE)
    pos_r = 0;

  return c;
}

#else  // SERIAL_RX_INTERRUPT

char uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  char c = UDR0;
  if (echo_on)
    uart_putchar(c, stdout);
  return c;
}

#endif  // SERIAL_RX_INTERRUPT

//FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE uart_input  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
FILE uart_io = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void serial_console_init() {
  #ifdef SERIAL_RX_INTERRUPT
  UCSR0B &= ~(_BV(RXCIE0));  // disable RX complete interrupt
                             // (neccessary for initialization of pos_w etc.
                             // below without making it atomic)
  #endif  // SERIAL_RX_INTERRUPT

  uart_init();
  serial_console_echo_reset();

  //stdout = &uart_output;
  //stdin  = &uart_input;
  stdout = stdin = &uart_io;

  #ifdef SERIAL_RX_INTERRUPT
  pos_w = 0;
  pos_r = 0;
  num_bytes = 0;

  UCSR0B |= _BV(RXCIE0);  // enable RX complete interrupt
  #endif  // SERIAL_RX_INTERRUPT
}

void serial_console_echo(const int b) {
  echo_on = b;
}

void serial_console_echo_reset() {
  echo_on = SERIAL_ECHO_ON;
}