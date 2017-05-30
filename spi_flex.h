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
  
// SPI_FLEX_01 = CLEO
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
#define SPI_FLEX_AMO1_VDD1      0x02

#define SPI_FLEX_02_CLK		PK2
#define SPI_FLEX_02_CLK_PIN   	PINK
#define SPI_FLEX_02_CLK_DDR   	DDRK
#define SPI_FLEX_02_CLK_PORT  	PORTK

#define SPI_FLEX_02_SDO		PK1
#define SPI_FLEX_02_SDO_PIN   	PINK
#define SPI_FLEX_02_SDO_DDR   	DDRK
#define SPI_FLEX_02_SDO_PORT  	PORTK

#define SPI_FLEX_02_nCS		PK0
#define SPI_FLEX_02_nCS_PIN   	PINK
#define SPI_FLEX_02_nCS_DDR   	DDRK
#define SPI_FLEX_02_nCS_PORT  	PORTK

#define SPI_FLEX_02_DIS		PA1
#define SPI_FLEX_02_DIS_PIN   	PINA
#define SPI_FLEX_02_DIS_DDR   	DDRA
#define SPI_FLEX_02_DIS_PORT  	PORTA

// SPI_FLEX_03
#define SPI_FLEX_AMO1_OUT	0x03

#define SPI_FLEX_03_CLK		PK2
#define SPI_FLEX_03_CLK_PIN   	PINK
#define SPI_FLEX_03_CLK_DDR   	DDRK
#define SPI_FLEX_03_CLK_PORT  	PORTK

#define SPI_FLEX_03_SDO		PK1
#define SPI_FLEX_03_SDO_PIN   	PINK
#define SPI_FLEX_03_SDO_DDR   	DDRK
#define SPI_FLEX_03_SDO_PORT  	PORTK

#define SPI_FLEX_03_nCS		PK4
#define SPI_FLEX_03_nCS_PIN   	PINK
#define SPI_FLEX_03_nCS_DDR   	DDRK
#define SPI_FLEX_03_nCS_PORT  	PORTK

#define SPI_FLEX_03_DIS		PA5
#define SPI_FLEX_03_DIS_PIN   	PINA
#define SPI_FLEX_03_DIS_DDR   	DDRA
#define SPI_FLEX_03_DIS_PORT  	PORTA

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
