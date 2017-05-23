//#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "spi_flex.h"
#include "serial_console.h"
#include "CleO_common.hpp"
//#define REPORT(VAR) (Serial.print(#VAR "="), Serial.println(VAR, HEX))

/* Default IO configurations */
#define _CLEO_CHIPSELECTPIN_ (10)
#define _CLEO_INTSELECTPIN_ (3)
#define SPI_FLEX_CLEO 0

//#if !defined(__AVR_ATmega328P__)
//#define MOSI  11
//#define MISO  12
//#define SCK   13    // B.27

/*
class ASPI_t {
public:
  void begin(void) {
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT_PULLUP);
    pinMode(SCK, OUTPUT);
    
    digitalWrite(SCK, 0);
    digitalWrite(MOSI, 0);
  }
  uint8_t transfer(uint8_t x ) {
    uint8_t r = 0;  

    for (uint8_t i = 0; i< 8; i++) {
       digitalWrite(MOSI, (x >> 7) & 1);
      r <<= 1;
      r |= digitalRead(MISO);
      
       digitalWrite(SCK, 1);
      //r |= digitalRead(MISO);   
       digitalWrite(SCK, 0);      
  
      x <<= 1;
    }
    
    return r;
  }
};
static class ASPI_t ASPI;
#define SPI ASPI

#endif
*/

//static int16_t __lnum;

extern uint8_t *addstr(uint8_t *pc, const char *s);

class CleOClass
{
public:
    CleOClass(uint8_t CSPin = _CLEO_CHIPSELECTPIN_ , uint8_t IntPin = _CLEO_INTSELECTPIN_)
    {
      _Cleo_chipSelectPin = CSPin;
      _Cleo_intSelectPin = IntPin;
    }

  int begin(void) {
    spi_flex_init(SPI_FLEX_CLEO);
//    pinMode(_Cleo_chipSelectPin, OUTPUT);
//    pinMode(_Cleo_intSelectPin, INPUT);
//    digitalWrite(_Cleo_chipSelectPin, 1);
/*
#if !defined(__AVR_ATmega328P__)
    Serial.println("SPI Bitbang enabled");
    ASPI.begin();
#else   
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
#endif  
*/    
    // initalize the  data ready and chip select pins:
//    pinMode(_Cleo_chipSelectPin, OUTPUT);
//    pinMode(_Cleo_intSelectPin, INPUT);
//    unsel();
//    delay(1);

    uint16_t init = RX2();
    if (init != 0x3412) {
      return -1;
    }
    uint16_t r0, r1;
    do {
        r0 = Noop();
        r1 = Echo();
//      Serial.print("r0=");
	printf("r0=");
//      Serial.println(r0, HEX);
	printf("0x%x", r0);
//      Serial.print("r1=");
	printf("r1=");
//      Serial.println(r1, HEX);
	printf("0x%x", r0);
//      Serial.println();
    } while ((r0 != 0x0000) || (r1 != 0x1d7f));
//    Serial.println("synced");
    printf("synced");
    return 0;
  }

#include "CleO_encoder.hpp"

private:
  uint8_t _Cleo_chipSelectPin;
  uint8_t _Cleo_intSelectPin;

  void sel(void) {
//    digitalWrite(_Cleo_chipSelectPin, 0);
    spi_flex_chip_sel(SPI_FLEX_CLEO);
  }

  void unsel(void) {
//    digitalWrite(_Cleo_chipSelectPin, 1);
    spi_flex_chip_usel(SPI_FLEX_CLEO);
  }

  union {
    uint8_t c2nbuf[256];
    uint16_t c2nbuf_w[128];
  };

  void TX(uint8_t *a, size_t b) {
    size_t i;   
    sel();
//    SPI.transfer(b);
    spi_flex_write_byte(SPI_FLEX_CLEO, b);

//    SPI.transfer(b >> 8);
    spi_flex_write_byte(SPI_FLEX_CLEO, b >> 8);
    for (i = 0; i < b; i++) {
      if ((i & 63) == 0) {
        // wait for a high signal - slave ready
//        while (digitalRead(_Cleo_intSelectPin) == 0)
	while (spi_flex_irq(SPI_FLEX_CLEO) == 0)
          ;
      }
//      SPI.transfer(a[i]);
      spi_flex_write_byte(SPI_FLEX_CLEO, a[i]);
    }
    unsel();
  }

  uint8_t collect(void) {
//    uint8_t r = SPI.transfer(0xff);
    uint8_t r = spi_flex_read_write_byte(SPI_FLEX_CLEO, 0xff);
    return r;
  }

  void RX(int n) {   
    sel();
    for (int i = 0; i < n; i++) {
      if ((i & 63) == 0) {
//        while (digitalRead(_Cleo_intSelectPin) == 0) // wait for a high signal - slave ready
	while (spi_flex_irq(SPI_FLEX_CLEO) == 0) // wait for a high signal - slave ready
          ;
      }
      c2nbuf[i] = collect();
    }
    unsel();

//    while (digitalRead(_Cleo_intSelectPin) == 1) // Wait for slave to complete MISO transaction before we move on
    while (spi_flex_irq(SPI_FLEX_CLEO) == 1) // Wait for slave to complete MISO transaction before we move on
      ;
  }

  int RX2() {
    RX(2);
    return c2nbuf_w[0];
  }
};

extern CleOClass CleO;
