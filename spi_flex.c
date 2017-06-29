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

void spi_flex_init(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //SPI_MODE0
/*    SPI_FLEX_01_PWR_DDR  |=  _BV(SPI_FLEX_01_PWR); //output
    SPI_FLEX_01_PWR_PORT |=  _BV(SPI_FLEX_01_PWR); //1
    _delay_ms(1000);
    SPI_FLEX_01_PWR_PORT &= ~_BV(SPI_FLEX_01_PWR); //0
    _delay_ms(1000);*/
    
    SPI_FLEX_01_nCS_DDR  |=  _BV(SPI_FLEX_01_nCS); //output
    SPI_FLEX_01_nCS_PORT |=  _BV(SPI_FLEX_01_nCS); //1
    //SPI_FLEX_01_nCS_PORT &= ~_BV(SPI_FLEX_01_nCS); //0
	
    SPI_FLEX_01_nRS_DDR  |=  _BV(SPI_FLEX_01_nRS); //output
    SPI_FLEX_01_nRS_PORT |=  _BV(SPI_FLEX_01_nRS); //1
    //SPI_FLEX_01_nRS_PORT &= ~_BV(SPI_FLEX_01_nRS); //0
	
    SPI_FLEX_01_CLK_DDR  |=  _BV(SPI_FLEX_01_CLK); //output
    SPI_FLEX_01_CLK_PORT |=  _BV(SPI_FLEX_01_CLK); //1
    //SPI_FLEX_01_CLK_PORT &= ~_BV(SPI_FLEX_01_CLK); //0
  
    SPI_FLEX_01_SDO_DDR  |=  _BV(SPI_FLEX_01_SDO); //output
    SPI_FLEX_01_SDO_PORT |=  _BV(SPI_FLEX_01_SDO); //1
    //SPI_FLEX_01_SDO_PORT &= ~_BV(SPI_FLEX_01_SDO); //0
   
    SPI_FLEX_01_SDI_DDR  &= ~_BV(SPI_FLEX_01_SDI); //input
    SPI_FLEX_01_SDI_PORT &= ~_BV(SPI_FLEX_01_SDI); //disable pullup
  
    SPI_FLEX_01_IRQ_DDR  &= ~_BV(SPI_FLEX_01_IRQ); //input
    SPI_FLEX_01_IRQ_PORT &= ~_BV(SPI_FLEX_01_IRQ); //disable pullup
  }
  else if (spi_n == SPI_FLEX_AMO2_VT) { //SPI_MODE0
    SPI_FLEX_02_DIS_DDR  |=  _BV(SPI_FLEX_02_DIS); //output
    //SPI_FLEX_02_DIS_PORT |=  _BV(SPI_FLEX_02_DIS); //1
    SPI_FLEX_02_DIS_PORT &= ~_BV(SPI_FLEX_02_DIS); //0
    _delay_ms(100);
	
    SPI_FLEX_02_nCS_DDR  |=  _BV(SPI_FLEX_02_nCS); //output
    SPI_FLEX_02_nCS_PORT |=  _BV(SPI_FLEX_02_nCS); //1
    //SPI_FLEX_02_nCS_PORT &= ~_BV(SPI_FLEX_02_nCS); //0
	
    SPI_FLEX_02_CLK_DDR  |=  _BV(SPI_FLEX_02_CLK); //output
    SPI_FLEX_02_CLK_PORT |=  _BV(SPI_FLEX_02_CLK); //1
    //SPI_FLEX_02_CLK_PORT &= ~_BV(SPI_FLEX_02_CLK); //0
  
    SPI_FLEX_02_SDO_DDR  |=  _BV(SPI_FLEX_02_SDO); //output
    SPI_FLEX_02_SDO_PORT |=  _BV(SPI_FLEX_02_SDO); //1
    //SPI_FLEX_02_SDO_PORT &= ~_BV(SPI_FLEX_02_SDO); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VILM) { //SPI_MODE0
    SPI_FLEX_03_DIS_DDR  |=  _BV(SPI_FLEX_03_DIS); //output
    //SPI_FLEX_03_DIS_PORT |=  _BV(SPI_FLEX_03_DIS); //1
    SPI_FLEX_03_DIS_PORT &= ~_BV(SPI_FLEX_03_DIS); //0
    _delay_ms(100);
   
    SPI_FLEX_03_nCS_DDR  |=  _BV(SPI_FLEX_03_nCS); //output
    SPI_FLEX_03_nCS_PORT |=  _BV(SPI_FLEX_03_nCS); //1
    //SPI_FLEX_03_nCS_PORT &= ~_BV(SPI_FLEX_03_nCS); //0
	
    SPI_FLEX_03_CLK_DDR  |=  _BV(SPI_FLEX_03_CLK); //output
    SPI_FLEX_03_CLK_PORT |=  _BV(SPI_FLEX_03_CLK); //1
    //SPI_FLEX_03_CLK_PORT &= ~_BV(SPI_FLEX_03_CLK); //0

    SPI_FLEX_03_SDO_DDR  |=  _BV(SPI_FLEX_03_SDO); //output
    SPI_FLEX_03_SDO_PORT |=  _BV(SPI_FLEX_03_SDO); //1
    //SPI_FLEX_03_SDO_PORT &= ~_BV(SPI_FLEX_03_SDO); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_PID) { //SPI_MODE0
    SPI_FLEX_04_DIS_DDR  |=  _BV(SPI_FLEX_04_DIS); //output
    //SPI_FLEX_04_DIS_PORT |=  _BV(SPI_FLEX_04_DIS); //1
    SPI_FLEX_04_DIS_PORT &= ~_BV(SPI_FLEX_04_DIS); //0
    _delay_ms(100);
   
    SPI_FLEX_04_nCS_DDR  |=  _BV(SPI_FLEX_04_nCS); //output
    SPI_FLEX_04_nCS_PORT |=  _BV(SPI_FLEX_04_nCS); //1
    //SPI_FLEX_04_nCS_PORT &= ~_BV(SPI_FLEX_04_nCS); //0
	
    SPI_FLEX_04_CLK_DDR  |=  _BV(SPI_FLEX_04_CLK); //output
    SPI_FLEX_04_CLK_PORT |=  _BV(SPI_FLEX_04_CLK); //1
    //SPI_FLEX_04_CLK_PORT &= ~_BV(SPI_FLEX_04_CLK); //0

    SPI_FLEX_04_SDO_DDR  |=  _BV(SPI_FLEX_04_SDO); //output
    SPI_FLEX_04_SDO_PORT |=  _BV(SPI_FLEX_04_SDO); //1
    //SPI_FLEX_04_SDO_PORT &= ~_BV(SPI_FLEX_04_SDO); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VPP) { //SPI_MODE0
    SPI_FLEX_05_DIS_DDR  |=  _BV(SPI_FLEX_05_DIS); //output
    //SPI_FLEX_05_DIS_PORT |=  _BV(SPI_FLEX_05_DIS); //1
    SPI_FLEX_05_DIS_PORT &= ~_BV(SPI_FLEX_05_DIS); //0
    _delay_ms(100);
   
    SPI_FLEX_05_nCS_DDR  |=  _BV(SPI_FLEX_05_nCS); //output
    SPI_FLEX_05_nCS_PORT |=  _BV(SPI_FLEX_05_nCS); //1
    //SPI_FLEX_05_nCS_PORT &= ~_BV(SPI_FLEX_05_nCS); //0
	
    SPI_FLEX_05_CLK_DDR  |=  _BV(SPI_FLEX_05_CLK); //output
    SPI_FLEX_05_CLK_PORT |=  _BV(SPI_FLEX_05_CLK); //1
    //SPI_FLEX_05_CLK_PORT &= ~_BV(SPI_FLEX_05_CLK); //0

    SPI_FLEX_05_SDO_DDR  |=  _BV(SPI_FLEX_05_SDO); //output
    SPI_FLEX_05_SDO_PORT |=  _BV(SPI_FLEX_05_SDO); //1
    //SPI_FLEX_05_SDO_PORT &= ~_BV(SPI_FLEX_05_SDO); //0
    
    SPI_FLEX_05_SDI_DDR  &= ~_BV(SPI_FLEX_05_SDI); //input
    SPI_FLEX_05_SDI_PORT &= ~_BV(SPI_FLEX_05_SDI); //disable pullup
  }
}

void spi_flex_reset(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    //_delay_loop_1(1);
    SPI_FLEX_01_nRS_PORT &= ~_BV(SPI_FLEX_01_nRS); //0
    _delay_loop_1(10);
    SPI_FLEX_01_nRS_PORT |=  _BV(SPI_FLEX_01_nRS); //1
    _delay_loop_1(1);
  }
}

void spi_flex_sel(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    SPI_FLEX_01_CLK_PORT &= ~_BV(SPI_FLEX_01_CLK); //0
    SPI_FLEX_01_nCS_PORT &= ~_BV(SPI_FLEX_01_nCS); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VT) { //0x02, SPI_MODE0
    //SPI_FLEX_02_DIS_PORT &= ~_BV(SPI_FLEX_02_DIS); //0
    //_delay_loop_1(1);
    SPI_FLEX_02_CLK_PORT &= ~_BV(SPI_FLEX_02_CLK); //0
    SPI_FLEX_02_nCS_PORT &= ~_BV(SPI_FLEX_02_nCS); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VILM) { //0x03, SPI_MODE0
    //SPI_FLEX_03_DIS_PORT &= ~_BV(SPI_FLEX_03_DIS); //0
    //_delay_loop_1(1);
    SPI_FLEX_03_CLK_PORT &= ~_BV(SPI_FLEX_03_CLK); //0
    SPI_FLEX_03_nCS_PORT &= ~_BV(SPI_FLEX_03_nCS); //0
  }
}

void spi_flex_usel(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    SPI_FLEX_01_nCS_PORT |=  _BV(SPI_FLEX_01_nCS); //1
    SPI_FLEX_01_CLK_PORT |=  _BV(SPI_FLEX_01_CLK); //1
    SPI_FLEX_01_SDO_PORT |=  _BV(SPI_FLEX_01_SDO); //1
  }
  else if (spi_n == SPI_FLEX_AMO2_VT) { //0x02, SPI_MODE0
    SPI_FLEX_02_nCS_PORT |=  _BV(SPI_FLEX_02_nCS); //1
    SPI_FLEX_02_CLK_PORT |=  _BV(SPI_FLEX_02_CLK); //1
    SPI_FLEX_02_SDO_PORT |=  _BV(SPI_FLEX_02_SDO); //1
    //_delay_loop_1(1);
    //SPI_FLEX_02_DIS_PORT |=  _BV(SPI_FLEX_02_DIS); //1
  }
  else if (spi_n == SPI_FLEX_AMO2_VILM) { //0x03, SPI_MODE0
    SPI_FLEX_03_nCS_PORT |=  _BV(SPI_FLEX_03_nCS); //1
    SPI_FLEX_03_CLK_PORT |=  _BV(SPI_FLEX_03_CLK); //1
    SPI_FLEX_03_SDO_PORT |=  _BV(SPI_FLEX_03_SDO); //1
    //_delay_loop_1(1);
    //SPI_FLEX_03_DIS_PORT |=  _BV(SPI_FLEX_03_DIS); //1
  }
}

static inline void __spi_flex_write_bit(const unsigned char spi_n, 
                                        const unsigned char bit) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    if (bit)
      SPI_FLEX_01_SDO_PORT |=  _BV(SPI_FLEX_01_SDO); //1
    else
      SPI_FLEX_01_SDO_PORT &= ~_BV(SPI_FLEX_01_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT |=  _BV(SPI_FLEX_01_CLK); //1
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT &= ~_BV(SPI_FLEX_01_CLK); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VT) { //0x02, SPI_MODE0
    if (bit)
      SPI_FLEX_02_SDO_PORT |=  _BV(SPI_FLEX_02_SDO); //1
    else
      SPI_FLEX_02_SDO_PORT &= ~_BV(SPI_FLEX_02_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_02_CLK_PORT |=  _BV(SPI_FLEX_02_CLK); //1
    _delay_loop_1(1);
    SPI_FLEX_02_CLK_PORT &= ~_BV(SPI_FLEX_02_CLK); //0
  }
  else if (spi_n == SPI_FLEX_AMO2_VILM) { //0x03, SPI_MODE0
    if (bit)
      SPI_FLEX_03_SDO_PORT |=  _BV(SPI_FLEX_03_SDO); //1
    else
      SPI_FLEX_03_SDO_PORT &= ~_BV(SPI_FLEX_03_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_03_CLK_PORT |=  _BV(SPI_FLEX_03_CLK); //1
    _delay_loop_1(1);
    SPI_FLEX_03_CLK_PORT &= ~_BV(SPI_FLEX_03_CLK); //0
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
}

static inline unsigned char __spi_flex_read_bit(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT |=  _BV(SPI_FLEX_01_CLK); //1
    unsigned char rbit = (SPI_FLEX_01_SDI_PIN >> SPI_FLEX_01_SDI) & 0x01;
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT &= ~_BV(SPI_FLEX_01_CLK); //0
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
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    if (bit)
      SPI_FLEX_01_SDO_PORT |=  _BV(SPI_FLEX_01_SDO); //1
    else
      SPI_FLEX_01_SDO_PORT &= ~_BV(SPI_FLEX_01_SDO); //0
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT |=  _BV(SPI_FLEX_01_CLK); //1
    unsigned char rbit = (SPI_FLEX_01_SDI_PIN >> SPI_FLEX_01_SDI) & 0x01;
    _delay_loop_1(1);
    SPI_FLEX_01_CLK_PORT &= ~_BV(SPI_FLEX_01_CLK); //0
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

unsigned char spi_flex_read_irq(const unsigned char spi_n) {
  if (spi_n == SPI_FLEX_CLEO) { //0x01, SPI_MODE0
    return ((SPI_FLEX_01_IRQ_PIN >> SPI_FLEX_01_IRQ) & 0x01);
  }
  return 0;
}
