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
  
// debugging
void spi_flex_debug(const int enabled);

// setup
void spi_flex_init(const unsigned char spi_n);
void spi_flex_reset(const unsigned char spi_n);

// chip select
void spi_flex_chip_sel(const unsigned char spi_n);
void spi_flex_chip_usel(const unsigned char spi_n);

// write byte starting with MSB
void spi_flex_write_byte(const unsigned char spi_n, const unsigned char val);

// read byte starting with MSB
unsigned char spi_flex_read_byte(const unsigned char spi_n);

// read & write byte starting with MSB
unsigned char spi_flex_read_write_byte(const unsigned char spi_n, const unsigned char val);

// check irq
unsigned char spi_flex_irq(const unsigned char spi_n);

#ifdef __cplusplus
}
#endif

#endif  // SPI_FLEX_H
