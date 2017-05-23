#ifndef CLEO_H
#define CLEO_H 1
// CleO_1.0.0

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "spi_flex.h"
#include "serial_console.h"
#include "CleO_common.hpp"
//#define REPORT(VAR) (Serial.print(#VAR "="), Serial.println(VAR, HEX))

//static int16_t __lnum;

extern uint8_t *addstr(uint8_t *pc, const char *s);

class CleOClass
{
public:
    CleOClass()
    {
    }

  int begin(void) {
    spi_flex_init(SPI_FLEX_CLEO);

    uint16_t init = RX2();
    if (init != 0x3412) {
      return -1;
    }
    uint16_t r0, r1;
    do {
        r0 = Noop();
        r1 = Echo();
	printf("CleO r0=0x%x\n", r0);
	printf("CleO r1=0x%x\n", r1);
    } while ((r0 != 0x0000) || (r1 != 0x1d7f));
    printf("CleO Synced\n");
    return 0;
  }

#include "CleO_encoder.hpp"

private:

  void sel(void) {
    spi_flex_chip_sel(SPI_FLEX_CLEO);
  }

  void unsel(void) {
    spi_flex_chip_usel(SPI_FLEX_CLEO);
  }

  union {
    uint8_t c2nbuf[256];
    uint16_t c2nbuf_w[128];
  };

  void TX(uint8_t *a, size_t b) {
    sel();
    
    // write size of byte array
    spi_flex_write_byte(SPI_FLEX_CLEO, b);
    spi_flex_write_byte(SPI_FLEX_CLEO, b >> 8);
    
    // write bytes
    size_t i;
    for (i = 0; i < b; i++) {
      if ((i & 63) == 0) {
	while (spi_flex_read_irq(SPI_FLEX_CLEO) == 0); //wait for cleo ready
      }
      spi_flex_write_byte(SPI_FLEX_CLEO, a[i]);
    }
    
    unsel();
  }

  uint8_t collect(void) {
    uint8_t r = spi_flex_read_write_byte(SPI_FLEX_CLEO, 0xff);
    return r;
  }

  void RX(int n) {   
    sel();
    
    //read
    for (int i = 0; i < n; i++) {
      if ((i & 63) == 0) {
	while (spi_flex_read_irq(SPI_FLEX_CLEO) == 0); //wait for cleo to be ready
      }
      c2nbuf[i] = collect();
    }
    
    unsel();

    while (spi_flex_read_irq(SPI_FLEX_CLEO) == 1); // wait for cleo to complete MISO transaction before moving on
  }

  int RX2() {
    RX(2);
    return c2nbuf_w[0];
  }
};

extern CleOClass CleO;

#endif  // CLEO_H
