#ifndef _FT_COMMON_H_
#define _FT_COMMON_H_

#include "CleO_colornames.hpp"
#include "CleO_icons.hpp"

#define DEGREES               0
#define FURMANS               1

#define FONT_VGA_8            0
#define FONT_VGA_16           2
#define FONT_BIT_0            4
#define FONT_BIT_1            5
#define FONT_BIT_2            6
#define FONT_BIT_3            7
#define FONT_BIT_4            8
#define FONT_BIT_5            9
#define FONT_SANS_0           10
#define FONT_SANS_1           11
#define FONT_SANS_2           12
#define FONT_SANS_3           13
#define FONT_SANS_4           14
#define FONT_SANS_5           15
#define FONT_SANS_6           16
#define FONT_SANS_7           17
#define FONT_SANS_8           18

#define FONT_TINY             FONT_SANS_0
#define FONT_MEDIUM           FONT_SANS_4
#define FONT_HUGE             FONT_SANS_8

typedef enum {TL, TM, TR, ML, MM, MR, BL, BM, BB} just_t;

#define OPT_CENTER            1536UL
#define OPT_CENTERX           512UL
#define OPT_CENTERY           1024UL
#define OPT_FLAT              256UL
#define OPT_FULLSCREEN        8UL
#define OPT_MEDIAFIFO         16UL
#define OPT_MONO              1UL
#define OPT_NOBACK            4096UL
#define OPT_NODL              2UL
#define OPT_NOHANDS           49152UL
#define OPT_NOHM              16384UL
#define OPT_NOPOINTER         16384UL
#define OPT_NOSECS            32768UL
#define OPT_NOTEAR            4UL
#define OPT_NOTICKS           8192UL
#define OPT_RIGHTX            2048UL
#define OPT_SIGNED            256UL
#define OPT_SOUND             32UL

// Built-in sounds

#define SILENCE              0x00

#define SQUAREWAVE           0x01
#define SINEWAVE             0x02
#define SAWTOOTH             0x03
#define TRIANGLE             0x04

#define BEEPING              0x05
#define ALARM                0x06
#define WARBLE               0x07
#define CAROUSEL             0x08

#define PIPS(n)              (0x0f + (n))

#define HARP                 0x40
#define XYLOPHONE            0x41
#define TUBA                 0x42
#define GLOCKENSPIEL         0x43
#define ORGAN                0x44
#define TRUMPET              0x45
#define PIANO                0x46
#define CHIMES               0x47
#define MUSICBOX             0x48
#define BELL                 0x49

#define CLICK                0x50
#define SWITCH               0x51
#define COWBELL              0x52
#define NOTCH                0x53
#define HIHAT                0x54
#define KICKDRUM             0x55
#define POP                  0x56
#define CLACK                0x57
#define CHACK                0x58

#define MUTE                 0x60
#define UNMUTE               0x61

// FOpen 'mode' values
#define FILE_READ             0x01
#define FILE_OPEN_EXISTING    0x00
#define FILE_WRITE            0x02
#define FILE_CREATE_NEW       0x04
#define FILE_CREATE_ALWAYS    0x08
#define FILE_OPEN_ALWAYS      0x10

// Modes for SetBackgroundImage
#define CENTERED              0
#define ZOOMED                1
#define TILED                 2

// Modes for AudioPlay
#define PLAY_WAIT             0
#define PLAY_ONCE             1
#define PLAY_LOOP             2

// Error return codes

#define ERROR_GENERAL             -1
#define ERROR_INTERNAL            -2
#define ERROR_NOFILE              -3
#define ERROR_NOPATH              -4
#define ERROR_INVALIDFILE         -5
#define ERROR_INVALIDOBJECT       -6
#define ERROR_NOFILESYSTEM        -7
#define ERROR_FILESYSTEMFULL      -8
#define ERROR_NOTENOUGHCORE       -9
#define ERROR_TOOMANYOPENFILES    -10
#define ERROR_INVALIDPARAMETERS   -11
#define ERROR_NOSDCARD            -12

typedef struct {
  uint8_t size;
  char text[31];
} textfield;

#endif
