/*
 * SPI low-level driver for DACs on connector X8
 *
 * Copyright 2013--2016 Christian Schneider <software(at)chschneider(dot)eu>
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
#include "spi_x8_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>

// NOTE: In principle, the PA0-PA7 macros should only be used for mappings on
// PORTA, while PINA0-PINA7 are used for PINA, and DDA0-DDA7 for DDRA.
// However, PA0 == PINA0 == DDA0 etc., so that I am lazy this time.

#define SPI_X8I_PIN  PINC
#define SPI_X8I_DDR  DDRC
#define SPI_X8I_PORT PORTC

#define SPI_X8O_PIN  PINJ
#define SPI_X8O_DDR  DDRJ
#define SPI_X8O_PORT PORTJ

#define SPI_X8_NCS1A  PJ7
#define SPI_X8_SCLK1  PJ6
#define SPI_X8_SDO1   PJ5
#define SPI_X8_NCS0A  PJ4
#define SPI_X8_SCLK0  PJ3
#define SPI_X8_SDO0   PJ2
#define SPI_X8_NCS0B  PJ1
#define SPI_X8_NCS1B  PJ0
#define SPI_X8_SDI1A  PC7
#define SPI_X8_SDI0A  PC6
#define SPI_X8_SDI0B  PC5
#define SPI_X8_SDI1B  PC4
#define SPI_X8_IN2    PC3
#define SPI_X8_IN3    PC2
#define SPI_X8_IN4    PC1
#define SPI_X8_IN5    PC0

void spi_x8_init() {
  // define pins as outputs
  SPI_X8O_DDR |=   _BV(SPI_X8_NCS1A)
                 | _BV(SPI_X8_SCLK1)
                 | _BV(SPI_X8_SDO1)
                 | _BV(SPI_X8_NCS0A)
                 | _BV(SPI_X8_SCLK0)
                 | _BV(SPI_X8_SDO0)
                 | _BV(SPI_X8_NCS0B)
                 | _BV(SPI_X8_NCS1B);

  // define pins as inputs
  SPI_X8I_DDR &= ~(  _BV(SPI_X8_SDI1A)
                   | _BV(SPI_X8_SDI0A)
                   | _BV(SPI_X8_SDI0B)
                   | _BV(SPI_X8_SDI1B)
                   | _BV(SPI_X8_IN2)
                   | _BV(SPI_X8_IN3)
                   | _BV(SPI_X8_IN4)
                   | _BV(SPI_X8_IN5));

  // disable pull-ups
  SPI_X8I_PORT &= ~(  _BV(SPI_X8_SDI1A)
                    | _BV(SPI_X8_SDI0A)
                    | _BV(SPI_X8_SDI0B)
                    | _BV(SPI_X8_SDI1B)
                    | _BV(SPI_X8_IN2)
                    | _BV(SPI_X8_IN3)
                    | _BV(SPI_X8_IN4)
                    | _BV(SPI_X8_IN5));

  // set pins to one
  SPI_X8O_PORT |=   _BV(SPI_X8_NCS0A) | _BV(SPI_X8_NCS1A)
                  | _BV(SPI_X8_NCS0B) | _BV(SPI_X8_NCS1B);

  // set pins to zero
  SPI_X8O_PORT &= ~(  _BV(SPI_X8_SDO0)  | _BV(SPI_X8_SDI1A)
                    | _BV(SPI_X8_SCLK0) | _BV(SPI_X8_SCLK1));
}

static inline void __spi_x8_1_write_bit(const unsigned char bit) {
  // clock high
  SPI_X8O_PORT |= _BV(SPI_X8_SCLK1);

  // set bit
  if (bit)
    SPI_X8O_PORT |= _BV(SPI_X8_SDO1);
  else
    SPI_X8O_PORT &= ~(_BV(SPI_X8_SDO1));

  // delay
  _delay_loop_1(1);

  // clock low
  SPI_X8O_PORT &= ~_BV(SPI_X8_SCLK1);

  // delay
  _delay_loop_1(1);
}

static inline void __spi_x8_0_write_bit(const unsigned char bit) {
  // clock high
  SPI_X8O_PORT |= _BV(SPI_X8_SCLK0);

  // set bit
  if (bit)
    SPI_X8O_PORT |= _BV(SPI_X8_SDO0);
  else
    SPI_X8O_PORT &= ~(_BV(SPI_X8_SDO0));

  // delay
  _delay_loop_1(1);

  // clock low
  SPI_X8O_PORT &= ~_BV(SPI_X8_SCLK0);

  // delay
  _delay_loop_1(1);
}

static inline void __spi_x8_write_bit(const unsigned char port,
                                      const unsigned char bit) {
  if (port == 0)
    __spi_x8_0_write_bit(bit);
  else
    __spi_x8_1_write_bit(bit);
}

void spi_x8_write_byte(const unsigned char port,
                       const unsigned char val) {
  __spi_x8_write_bit(port, val & (0x01 << 7));
  __spi_x8_write_bit(port, val & (0x01 << 6));
  __spi_x8_write_bit(port, val & (0x01 << 5));
  __spi_x8_write_bit(port, val & (0x01 << 4));
  __spi_x8_write_bit(port, val & (0x01 << 3));
  __spi_x8_write_bit(port, val & (0x01 << 2));
  __spi_x8_write_bit(port, val & (0x01 << 1));
  __spi_x8_write_bit(port, val & (0x01 << 0));
}

static inline unsigned char __spi_x8_1_read_bit() {
  // clock high
  SPI_X8O_PORT |= _BV(SPI_X8_SCLK1);

  // read bit
  unsigned char bit = (SPI_X8I_PIN >> SPI_X8_SDI1A) & 0x01;

  // delay
  _delay_loop_1(1);

  // clock low
  SPI_X8O_PORT &= ~_BV(SPI_X8_SCLK1);

  // delay
  _delay_loop_1(1);

  return bit;
}

static inline unsigned char __spi_x8_0_read_bit() {
  // clock high
  SPI_X8O_PORT |= _BV(SPI_X8_SCLK0);

  // read bit
  unsigned char bit = (SPI_X8I_PIN >> SPI_X8_SDI0A) & 0x01;

  // delay
  _delay_loop_1(1);

  // clock low
  SPI_X8O_PORT &= ~_BV(SPI_X8_SCLK0);

  // delay
  _delay_loop_1(1);

  return bit;
}

static inline unsigned char __spi_x8_read_bit(const unsigned char port) {
  if (port == 0)
    return __spi_x8_0_read_bit();
  else
    return __spi_x8_1_read_bit();
}

unsigned char spi_x8_read_byte(const unsigned char port) {
  unsigned char byte = 0x00;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  byte <<= 1;
  byte |= __spi_x8_read_bit(port);
  return byte;
}

static inline void __spi_x8_1_chip_select(const unsigned char bits) {
  const unsigned char cs_mask =   _BV(SPI_X8_NCS1B)
                                | _BV(SPI_X8_NCS1A);

  SPI_X8O_PORT =   (SPI_X8O_PIN & (~cs_mask))
                 | ((bits & 0x02) ? 0x00 : _BV(SPI_X8_NCS1B))
                 | ((bits & 0x01) ? 0x00 : _BV(SPI_X8_NCS1A));

  // delay
  _delay_loop_1(1);
}

static inline void __spi_x8_0_chip_select(const unsigned char bits) {
  const unsigned char cs_mask =   _BV(SPI_X8_NCS0B)
                                | _BV(SPI_X8_NCS0A);

  SPI_X8O_PORT =   (SPI_X8O_PIN & (~cs_mask))
                 | ((bits & 0x02) ? 0x00 : _BV(SPI_X8_NCS0B))
                 | ((bits & 0x01) ? 0x00 : _BV(SPI_X8_NCS0A));

  // delay
  _delay_loop_1(1);
}

void spi_x8_chip_select(const unsigned char port,
                        const unsigned char bits) {
  if (port == 0)
    __spi_x8_0_chip_select(bits);
  else
    __spi_x8_1_chip_select(bits);
}
