/*
 * SPI low-level driver
 *
 * Copyright 2013--2017 
 *  Christian Schneider <software(at)chschneider(dot)eu>
 *  Peter Yu <ucla(dot)eshop(at)gmail(dot)com>
 *
 * This file is part of the AMO control unit firmware
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
#include "spi_flex.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// SPI_FLEX_0 = CLEO
#define SPI_FLEX_0_CLK		PF3
#define SPI_FLEX_0_CLK_PIN   	PINF
#define SPI_FLEX_0_CLK_DDR   	DDRF
#define SPI_FLEX_0_CLK_PORT  	PORTF

#define SPI_FLEX_0_SDO		PF1
#define SPI_FLEX_0_SDO_PIN   	PINF
#define SPI_FLEX_0_SDO_DDR   	DDRF
#define SPI_FLEX_0_SDO_PORT  	PORTF

#define SPI_FLEX_0_nCS		PF0
#define SPI_FLEX_0_nCS_PIN   	PINF
#define SPI_FLEX_0_nCS_DDR   	DDRF
#define SPI_FLEX_0_nCS_PORT  	PORTF

#define SPI_FLEX_0_SDI		PF2
#define SPI_FLEX_0_SDI_PIN   	PINF
#define SPI_FLEX_0_SDI_DDR   	DDRF
#define SPI_FLEX_0_SDI_PORT  	PORTF

#define SPI_FLEX_0_nRS		PE7
#define SPI_FLEX_0_nRS_PIN   	PINE
#define SPI_FLEX_0_nRS_DDR   	DDRE
#define SPI_FLEX_0_nRS_PORT  	PORTE

#define SPI_FLEX_0_IRQ		PE6
#define SPI_FLEX_0_IRQ_PIN   	PINE
#define SPI_FLEX_0_IRQ_DDR   	DDRE
#define SPI_FLEX_0_IRQ_PORT  	PORTE

#define SPI_FLEX_0_PWR		PG0
#define SPI_FLEX_0_PWR_PIN   	PING
#define SPI_FLEX_0_PWR_DDR   	DDRG
#define SPI_FLEX_0_PWR_PORT  	PORTG

static int __spi_flex_debug = 0;

void spi_flex_debug(const int enabled) {
  __spi_flex_debug = enabled;
}

void spi_flex_init(const unsigned char spi_n) {
  if (spi_n == 0x00) { //SPI_MODE0
    SPI_FLEX_0_CLK_DDR  |=  _BV(SPI_FLEX_0_CLK); //output
    SPI_FLEX_0_CLK_PORT |=  _BV(SPI_FLEX_0_CLK); //1
    //SPI_FLEX_0_CLK_PORT &= ~_BV(SPI_FLEX_0_CLK); //0
  
    SPI_FLEX_0_SDO_DDR  |=  _BV(SPI_FLEX_0_SDO); //output
    SPI_FLEX_0_SDO_PORT |=  _BV(SPI_FLEX_0_SDO); //1
    //SPI_FLEX_0_SDO_PORT &= ~_BV(SPI_FLEX_0_SDO); //0
   
    SPI_FLEX_0_nCS_DDR  |=  _BV(SPI_FLEX_0_nCS); //output
    SPI_FLEX_0_nCS_PORT |=  _BV(SPI_FLEX_0_nCS); //1
    //SPI_FLEX_0_nCS_PORT &= ~_BV(SPI_FLEX_0_nCS); //0
   
    SPI_FLEX_0_SDI_DDR  &= ~_BV(SPI_FLEX_0_SDI); //input
    SPI_FLEX_0_SDI_PORT &= ~_BV(SPI_FLEX_0_SDI); //disable pullup
  
    SPI_FLEX_0_nRS_DDR  |=  _BV(SPI_FLEX_0_nRS); //output
    SPI_FLEX_0_nRS_PORT |=  _BV(SPI_FLEX_0_nRS); //1
    //SPI_FLEX_0_nRS_PORT &= ~_BV(SPI_FLEX_0_nRS); //0

    SPI_FLEX_0_IRQ_DDR  &= ~_BV(SPI_FLEX_0_IRQ); //input
    SPI_FLEX_0_IRQ_PORT &= ~_BV(SPI_FLEX_0_IRQ); //disable pullup
    
    SPI_FLEX_0_PWR_DDR  |=  _BV(SPI_FLEX_0_PWR); //output
    //SPI_FLEX_0_PWR_PORT |=  _BV(SPI_FLEX_0_PWR); //1
    SPI_FLEX_0_PWR_PORT &= ~_BV(SPI_FLEX_0_PWR); //0
  }
  
  if (__spi_flex_debug)
    printf("spi init 0x%x", spi_n);
}

void spi_flex_reset(const unsigned char spi_n) {
  if (spi_n == 0x00) { //SPI_MODE0
    //_delay_loop_1(1);
    SPI_FLEX_0_nRS_PORT &= ~_BV(SPI_FLEX_0_nRS); //1->0
    _delay_loop_1(10);
    SPI_FLEX_0_nRS_PORT |=  _BV(SPI_FLEX_0_nRS); //0->1
    _delay_loop_1(1);
  }
  
  if (__spi_flex_debug)
    printf("spi reset 0x%x", spi_n);
}

void spi_flex_chip_sel(const unsigned char spi_n) {
  if (spi_n == 0x00) { //SPI_MODE0
    SPI_FLEX_0_CLK_PORT &= ~_BV(SPI_FLEX_0_CLK); //0
    SPI_FLEX_0_nCS_PORT &= ~_BV(SPI_FLEX_0_nCS); //1->0
  }

  if (__spi_flex_debug)
    printf("spi chip sel 0x%x", spi_n);
}

void spi_flex_chip_usel(const unsigned char spi_n) {
  if (spi_n == 0x00) { //SPI_MODE0
    SPI_FLEX_0_nCS_PORT |=  _BV(SPI_FLEX_0_nCS); //0->1
    SPI_FLEX_0_CLK_PORT |=  _BV(SPI_FLEX_0_CLK); //1
    SPI_FLEX_0_SDO_PORT |=  _BV(SPI_FLEX_0_SDO); //1
  }
  
  if (__spi_flex_debug)
    printf("spi chip usel 0x%x", spi_n);
}

static inline void __spi_flex_write_bit(const unsigned char spi_n, 
                                        const unsigned char bit) {
  if (spi_n == 0x00) { //SPI_MODE0
    if (bit)
      SPI_FLEX_0_SDO_PORT |=  _BV(SPI_FLEX_0_SDO); //1
    else
      SPI_FLEX_0_SDO_PORT &= ~_BV(SPI_FLEX_0_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT |=  _BV(SPI_FLEX_0_CLK); //0->1
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT &= ~_BV(SPI_FLEX_0_CLK); //1->0
  }
}

void spi_flex_write_byte(const unsigned char spi_n,
                         const unsigned char val) {
  __spi_flex_write_bit(spi_n, val & (0x01 << 7));
  __spi_flex_write_bit(spi_n, val & (0x01 << 6));
  __spi_flex_write_bit(spi_n, val & (0x01 << 5));
  __spi_flex_write_bit(spi_n, val & (0x01 << 4));
  __spi_flex_write_bit(spi_n, val & (0x01 << 3));
  __spi_flex_write_bit(spi_n, val & (0x01 << 2));
  __spi_flex_write_bit(spi_n, val & (0x01 << 1));
  __spi_flex_write_bit(spi_n, val & (0x01 << 0));

  if (__spi_flex_debug)
    printf("spi write 0x%x%x ", (val & 0xf0) >> 4, val & 0x0f);
}

static inline unsigned char __spi_flex_read_bit(const unsigned char spi_n) {
  if (spi_n == 0x00) { //SPI_MODE0
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT |=  _BV(SPI_FLEX_0_CLK); //0->1
    unsigned char rbit = (SPI_FLEX_0_SDI_PIN >> SPI_FLEX_0_SDI) & 0x01;
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT &= ~_BV(SPI_FLEX_0_CLK); //1->0
    return rbit;
  }
  return 0;
}

unsigned char spi_flex_read_byte(const unsigned char spi_n) {
  unsigned char byte = 0x00;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n);
  byte <<= 1;
  byte |= __spi_flex_read_bit(spi_n); 
  return byte;
}

static inline unsigned char __spi_flex_read_write_bit(const unsigned char spi_n, 
						      const unsigned char bit) {
  if (spi_n == 0x00) { //SPI_MODE0
    if (bit)
      SPI_FLEX_0_SDO_PORT |=  _BV(SPI_FLEX_0_SDO); //1
    else
      SPI_FLEX_0_SDO_PORT &= ~_BV(SPI_FLEX_0_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT |=  _BV(SPI_FLEX_0_CLK); //0->1
    unsigned char rbit = (SPI_FLEX_0_SDI_PIN >> SPI_FLEX_0_SDI) & 0x01;
    _delay_loop_1(1);
    SPI_FLEX_0_CLK_PORT &= ~_BV(SPI_FLEX_0_CLK); //1->0
    return rbit;
  }
  return 0;
}

unsigned char spi_flex_read_write_byte(const unsigned char spi_n, 
				       const unsigned char val) {
  unsigned char byte = 0x00;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 7));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 6));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 5));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 4));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 3));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 2));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 1));
  byte <<= 1;
  byte |= __spi_flex_read_write_bit(spi_n, val & (0x01 << 0));
  return byte;
}

unsigned char spi_flex_irq(const unsigned char spi_n) {
  if (spi_n == 0x00) {
    return ((SPI_FLEX_0_IRQ_PIN >> SPI_FLEX_0_IRQ) & 0x01);
  }
  return 0;
}
