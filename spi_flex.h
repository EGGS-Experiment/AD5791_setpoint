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
#define SPI_FLEX_AMO8_DAC1      0x02

#define SPI_FLEX_02_CLK		PC4
#define SPI_FLEX_02_CLK_PIN   	PINC
#define SPI_FLEX_02_CLK_DDR   	DDRC
#define SPI_FLEX_02_CLK_PORT  	PORTC

#define SPI_FLEX_02_SDI		PC0	//DAC's "SDO"
#define SPI_FLEX_02_SDI_PIN   	PINC
#define SPI_FLEX_02_SDI_DDR   	DDRC
#define SPI_FLEX_02_SDI_PORT  	PORTC

#define SPI_FLEX_02_SDO		PC2	//DAC's "SDI"
#define SPI_FLEX_02_SDO_PIN   	PINC
#define SPI_FLEX_02_SDO_DDR   	DDRC
#define SPI_FLEX_02_SDO_PORT  	PORTC

#define SPI_FLEX_02_nCS		PC6
#define SPI_FLEX_02_nCS_PIN   	PINC
#define SPI_FLEX_02_nCS_DDR   	DDRC
#define SPI_FLEX_02_nCS_PORT  	PORTC

#define SPI_FLEX_02_DIS		PJ0
#define SPI_FLEX_02_DIS_PIN   	PINJ
#define SPI_FLEX_02_DIS_DDR   	DDRJ
#define SPI_FLEX_02_DIS_PORT  	PORTJ

#define SPI_FLEX_02_nCLR	PA7
#define SPI_FLEX_02_nCLR_PIN   	PINA
#define SPI_FLEX_02_nCLR_DDR   	DDRA
#define SPI_FLEX_02_nCLR_PORT  	PORTA

#define SPI_FLEX_02_RST		PA5
#define SPI_FLEX_02_RST_PIN   	PINA
#define SPI_FLEX_02_RST_DDR   	DDRA
#define SPI_FLEX_02_RST_PORT  	PORTA

// SPI_FLEX_04
#define SPI_FLEX_AMO8_DAC2      0x04

#define SPI_FLEX_04_CLK		PC5
#define SPI_FLEX_04_CLK_PIN   	PINC
#define SPI_FLEX_04_CLK_DDR   	DDRC
#define SPI_FLEX_04_CLK_PORT  	PORTC

#define SPI_FLEX_04_SDI		PC1	//DAC's "SDO"
#define SPI_FLEX_04_SDI_PIN   	PINC
#define SPI_FLEX_04_SDI_DDR   	DDRC
#define SPI_FLEX_04_SDI_PORT  	PORTC

#define SPI_FLEX_04_SDO		PC3	//DAC's "SDI"
#define SPI_FLEX_04_SDO_PIN   	PINC
#define SPI_FLEX_04_SDO_DDR   	DDRC
#define SPI_FLEX_04_SDO_PORT  	PORTC

#define SPI_FLEX_04_nCS		PC7
#define SPI_FLEX_04_nCS_PIN   	PINC
#define SPI_FLEX_04_nCS_DDR   	DDRC
#define SPI_FLEX_04_nCS_PORT  	PORTC

#define SPI_FLEX_04_DIS		PJ1
#define SPI_FLEX_04_DIS_PIN   	PINJ
#define SPI_FLEX_04_DIS_DDR   	DDRJ
#define SPI_FLEX_04_DIS_PORT  	PORTJ

#define SPI_FLEX_04_nCLR	PA6
#define SPI_FLEX_04_nCLR_PIN   	PINA
#define SPI_FLEX_04_nCLR_DDR   	DDRA
#define SPI_FLEX_04_nCLR_PORT  	PORTA

#define SPI_FLEX_04_RST		PA4
#define SPI_FLEX_04_RST_PIN   	PINA
#define SPI_FLEX_04_RST_DDR   	DDRA
#define SPI_FLEX_04_RST_PORT  	PORTA

// SPI_FLEX_03
#define SPI_FLEX_AMO8_ADC1	0x03

#define SPI_FLEX_03_CLK		PJ6
#define SPI_FLEX_03_CLK_PIN   	PINJ
#define SPI_FLEX_03_CLK_DDR   	DDRJ
#define SPI_FLEX_03_CLK_PORT  	PORTJ

#define SPI_FLEX_03_SDO		PJ4	//ADC's "SDI"
#define SPI_FLEX_03_SDO_PIN   	PINJ
#define SPI_FLEX_03_SDO_DDR   	DDRJ
#define SPI_FLEX_03_SDO_PORT  	PORTJ

#define SPI_FLEX_03_nCS		PA3
#define SPI_FLEX_03_nCS_PIN   	PINA
#define SPI_FLEX_03_nCS_DDR   	DDRA
#define SPI_FLEX_03_nCS_PORT  	PORTA

#define SPI_FLEX_03_SDI		PJ2	//ADC's "SDO"
#define SPI_FLEX_03_SDI_PIN   	PINJ
#define SPI_FLEX_03_SDI_DDR   	DDRJ
#define SPI_FLEX_03_SDI_PORT  	PORTJ

// SPI_FLEX_05
#define SPI_FLEX_AMO8_ADC2	0x05

#define SPI_FLEX_05_CLK		PJ7
#define SPI_FLEX_05_CLK_PIN   	PINJ
#define SPI_FLEX_05_CLK_DDR   	DDRJ
#define SPI_FLEX_05_CLK_PORT  	PORTJ

#define SPI_FLEX_05_SDO		PJ5	//ADC's "SDI"
#define SPI_FLEX_05_SDO_PIN   	PINJ
#define SPI_FLEX_05_SDO_DDR   	DDRJ
#define SPI_FLEX_05_SDO_PORT  	PORTJ

#define SPI_FLEX_05_nCS		PA2
#define SPI_FLEX_05_nCS_PIN   	PINA
#define SPI_FLEX_05_nCS_DDR   	DDRA
#define SPI_FLEX_05_nCS_PORT  	PORTA

#define SPI_FLEX_05_SDI		PJ3	//ADC's "SDO"
#define SPI_FLEX_05_SDI_PIN   	PINJ
#define SPI_FLEX_05_SDI_DDR   	DDRJ
#define SPI_FLEX_05_SDI_PORT  	PORTJ

// setup
void spi_flex_init(const unsigned char spi_n);
void spi_flex_reset(const unsigned char spi_n);

// chip select
void spi_flex_sel(const unsigned char spi_n);
void spi_flex_usel(const unsigned char spi_n);

// write byte starting with MSB
void spi_flex_write_byte(const unsigned char spi_n, const unsigned char val);

//
void spi_flex_write_two_bits(const unsigned char spi_n,
                             const unsigned char val);
//
// read byte starting with MSB
unsigned char spi_flex_read_byte(const unsigned char spi_n);
//unsigned char spi_flex_read_18(const unsigned char spi_n);
uint32_t spi_flex_read_18(const unsigned char spi_n);
unsigned char spi_flex_read_2bits(const unsigned char spi_n);

// read & write byte starting with MSB
unsigned char spi_flex_read_write_byte(const unsigned char spi_n, const unsigned char val);

// irq
unsigned char spi_flex_read_irq(const unsigned char spi_n);

#ifdef __cplusplus
}
#endif

#endif  // SPI_FLEX_H
