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

#ifndef SERIAL_CONSOLE_H
#define SERIAL_CONSOLE_H 1

#ifdef __cplusplus
extern "C" {
#endif

// initializes primary serial port (8 bits, no parity, 1 stop bit (8N1))
// and maps stdin and stdout to serial port
void serial_console_init();

// turns on (== 1) or off (== 0) the echo of the serial console, i.e.,
// sending back the received character
void serial_console_echo(const int b);
void serial_console_echo_reset();

#ifdef __cplusplus
}
#endif

#endif  // SERIAL_CONSOLE_H
