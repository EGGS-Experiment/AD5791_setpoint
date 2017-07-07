/*
 * master configuration file
 *
 * Copyright 2013--2017 Christian Schneider <software(at)chschneider(dot)eu>
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

#ifndef CONFIG_H
#define CONFIG_H 1

// ////////////////////////////////////////////////////////////////////
// Version Number
// ////////////////////////////////////////////////////////////////////

#define VERSION "xxx"

// ////////////////////////////////////////////////////////////////////
// serial console defaults
// ////////////////////////////////////////////////////////////////////

// default baud rate (unless overwritten in Makefile!)
#ifndef BAUD
#define BAUD               38400
#endif  // BAUD

// default serial console echo on (1)/off (0) on init
#define SERIAL_ECHO_ON     0

// use interrupt-based RX (enabled, if macro is defined)
//#define SERIAL_RX_INTERRUPT 1

// default size of serial buffer; only for interrupt based RX
// (maximum allowed size: 255)
#define SERIAL_BUFFER_SIZE 255

#endif  // CONFIG_H
