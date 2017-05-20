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

#ifndef SPI_X8_DRIVER_H
#define SPI_X8_DRIVER_H 1

#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// initialize SPI interfaces
void spi_x8_init();

// set chip select of SPI 0/1
// * port \in { 0, 1 }:  selects the SPI port 0 or 1
// * bits:               chip select bits (2 LSB)
void spi_x8_chip_select(const unsigned char port, const unsigned char bits);

// write byte to SPI 0/1
// * port \in { 0, 1 }:  selects the SPI port 0 or 1
// * val:                byte value to be written (starting with MSB)
void spi_x8_write_byte(const unsigned char port, const unsigned char val);

// read byte from SPI 0/1
// * port \in { 0, 1 }:  selects the SPI port 0 or 1
// * <return value>:     read byte (starting with MSB)
unsigned char spi_x8_read_byte(const unsigned char port);

#endif  // SPI_X8_DRIVER_H
