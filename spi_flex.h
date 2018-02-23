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

#ifndef SPI_FLEX_H
#define SPI_FLEX_H 1

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif
  
// SPI_FLEX_01
#define SPI_FLEX_CLEO		0x01

#define SPI_FLEX_01_CLK		PF3
#define SPI_FLEX_01_CLK_PIN   	PINF
#define SPI_FLEX_01_CLK_DDR   	DDRF
#define SPI_FLEX_01_CLK_PORT  	PORTF

#define SPI_FLEX_01_SDO		PF1
#define SPI_FLEX_01_SDO_PIN   	PINF
#define SPI_FLEX_01_SDO_DDR   	DDRF
#define SPI_FLEX_01_SDO_PORT  	PORTF

#define SPI_FLEX_01_nCS		PF0
#define SPI_FLEX_01_nCS_PIN   	PINF
#define SPI_FLEX_01_nCS_DDR   	DDRF
#define SPI_FLEX_01_nCS_PORT  	PORTF

#define SPI_FLEX_01_SDI		PF2
#define SPI_FLEX_01_SDI_PIN   	PINF
#define SPI_FLEX_01_SDI_DDR   	DDRF
#define SPI_FLEX_01_SDI_PORT  	PORTF

#define SPI_FLEX_01_nRS		PE7
#define SPI_FLEX_01_nRS_PIN   	PINE
#define SPI_FLEX_01_nRS_DDR   	DDRE
#define SPI_FLEX_01_nRS_PORT  	PORTE

#define SPI_FLEX_01_IRQ		PE6
#define SPI_FLEX_01_IRQ_PIN   	PINE
#define SPI_FLEX_01_IRQ_DDR   	DDRE
#define SPI_FLEX_01_IRQ_PORT  	PORTE

#define SPI_FLEX_01_PWR		PG0
#define SPI_FLEX_01_PWR_PIN   	PING
#define SPI_FLEX_01_PWR_DDR   	DDRG
#define SPI_FLEX_01_PWR_PORT  	PORTG

// SPI_FLEX_02
#define SPI_FLEX_AMO3_VOUT      0x02

#define SPI_FLEX_02_CLK		PH4
#define SPI_FLEX_02_CLK_PIN   	PINH
#define SPI_FLEX_02_CLK_DDR   	DDRH
#define SPI_FLEX_02_CLK_PORT  	PORTH

#define SPI_FLEX_02_SDO		PH5
#define SPI_FLEX_02_SDO_PIN   	PINH
#define SPI_FLEX_02_SDO_DDR   	DDRH
#define SPI_FLEX_02_SDO_PORT  	PORTH

#define SPI_FLEX_02_nCS		PH3
#define SPI_FLEX_02_nCS_PIN   	PINH
#define SPI_FLEX_02_nCS_DDR   	DDRH
#define SPI_FLEX_02_nCS_PORT  	PORTH

#define SPI_FLEX_02_DIS		PH7
#define SPI_FLEX_02_DIS_PIN   	PINH
#define SPI_FLEX_02_DIS_DDR   	DDRH
#define SPI_FLEX_02_DIS_PORT  	PORTH

#define SPI_FLEX_02_nLDAC	PH6
#define SPI_FLEX_02_nLDAC_PIN  	PINH
#define SPI_FLEX_02_nLDAC_DDR  	DDRH
#define SPI_FLEX_02_nLDAC_PORT 	PORTH

// SPI_FLEX_03
#define SPI_FLEX_AMO2_VILM	0x03

#define SPI_FLEX_03_CLK		PK1
#define SPI_FLEX_03_CLK_PIN   	PINK
#define SPI_FLEX_03_CLK_DDR   	DDRK
#define SPI_FLEX_03_CLK_PORT  	PORTK

#define SPI_FLEX_03_SDO		PK3
#define SPI_FLEX_03_SDO_PIN   	PINK
#define SPI_FLEX_03_SDO_DDR   	DDRK
#define SPI_FLEX_03_SDO_PORT  	PORTK

#define SPI_FLEX_03_nCS		PA1
#define SPI_FLEX_03_nCS_PIN   	PINA
#define SPI_FLEX_03_nCS_DDR   	DDRA
#define SPI_FLEX_03_nCS_PORT  	PORTA

#define SPI_FLEX_03_DIS		PA3
#define SPI_FLEX_03_DIS_PIN   	PINA
#define SPI_FLEX_03_DIS_DDR   	DDRA
#define SPI_FLEX_03_DIS_PORT  	PORTA
  
// SPI_FLEX_04
#define SPI_FLEX_AMO2_PID	0x04

#define SPI_FLEX_04_CLK		PK1
#define SPI_FLEX_04_CLK_PIN   	PINK
#define SPI_FLEX_04_CLK_DDR   	DDRK
#define SPI_FLEX_04_CLK_PORT  	PORTK

#define SPI_FLEX_04_SDO		PK3
#define SPI_FLEX_04_SDO_PIN   	PINK
#define SPI_FLEX_04_SDO_DDR   	DDRK
#define SPI_FLEX_04_SDO_PORT  	PORTK

#define SPI_FLEX_04_nCS		PJ6
#define SPI_FLEX_04_nCS_PIN   	PINJ
#define SPI_FLEX_04_nCS_DDR   	DDRJ
#define SPI_FLEX_04_nCS_PORT  	PORTJ

#define SPI_FLEX_04_DIS		PJ4
#define SPI_FLEX_04_DIS_PIN   	PINJ
#define SPI_FLEX_04_DIS_DDR   	DDRJ
#define SPI_FLEX_04_DIS_PORT  	PORTJ
  
// SPI_FLEX_05
#define SPI_FLEX_AMO2_VPP	0x05

#define SPI_FLEX_05_CLK		PK1
#define SPI_FLEX_05_CLK_PIN   	PINK
#define SPI_FLEX_05_CLK_DDR   	DDRK
#define SPI_FLEX_05_CLK_PORT  	PORTK

#define SPI_FLEX_05_SDO		PK3
#define SPI_FLEX_05_SDO_PIN   	PINK
#define SPI_FLEX_05_SDO_DDR   	DDRK
#define SPI_FLEX_05_SDO_PORT  	PORTK
  
#define SPI_FLEX_05_SDI		PK5
#define SPI_FLEX_05_SDI_PIN   	PINK
#define SPI_FLEX_05_SDI_DDR   	DDRK
#define SPI_FLEX_05_SDI_PORT  	PORTK

#define SPI_FLEX_05_nCS		PA5
#define SPI_FLEX_05_nCS_PIN   	PINA
#define SPI_FLEX_05_nCS_DDR   	DDRA
#define SPI_FLEX_05_nCS_PORT  	PORTA

#define SPI_FLEX_05_DIS		PA7
#define SPI_FLEX_05_DIS_PIN   	PINA
#define SPI_FLEX_05_DIS_DDR   	DDRA
#define SPI_FLEX_05_DIS_PORT  	PORTA
  
/* USES SAME PINS AS AMO3 VOUT
// SPI_FLEX_06
#define SPI_FLEX_AMO2_FET	0x06

#define SPI_FLEX_06_CLK		PH1
#define SPI_FLEX_06_CLK_PIN   	PINH
#define SPI_FLEX_06_CLK_DDR   	DDRH
#define SPI_FLEX_06_CLK_PORT  	PORTH

#define SPI_FLEX_06_SDO		PH0
#define SPI_FLEX_06_SDO_PIN   	PINH
#define SPI_FLEX_06_SDO_DDR   	DDRH
#define SPI_FLEX_06_SDO_PORT  	PORTH

#define SPI_FLEX_06_SDI		PH3
#define SPI_FLEX_06_SDI_PIN   	PINH
#define SPI_FLEX_06_SDI_DDR   	DDRH
#define SPI_FLEX_06_SDI_PORT  	PORTH

#define SPI_FLEX_06_nCS		PH2
#define SPI_FLEX_06_nCS_PIN   	PINH
#define SPI_FLEX_06_nCS_DDR   	DDRH
#define SPI_FLEX_06_nCS_PORT  	PORTH
*/
  
// setup
void spi_flex_init(const unsigned char spi_n);
void spi_flex_reset(const unsigned char spi_n);

// chip select
void spi_flex_sel(const unsigned char spi_n);
void spi_flex_usel(const unsigned char spi_n);

// write byte starting with MSB
void spi_flex_write_byte(const unsigned char spi_n, const unsigned char val);

// read byte starting with MSB
unsigned char spi_flex_read_byte(const unsigned char spi_n);

// read & write byte starting with MSB
unsigned char spi_flex_read_write_byte(const unsigned char spi_n, const unsigned char val);

// irq
unsigned char spi_flex_read_irq(const unsigned char spi_n);

#ifdef __cplusplus
}
#endif

#endif  // SPI_FLEX_H
