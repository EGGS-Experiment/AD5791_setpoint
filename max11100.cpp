#include <assert.h>
#include "max11100.hpp"

MAX11100::MAX11100(const unsigned char spi)
{
  spi_n = spi;
}

uint16_t MAX11100::readCounts()
{
  spi_flex_sel(spi_n);
  spi_flex_read_byte(spi_n);
  uint8_t b1 = spi_flex_read_byte(spi_n);
  uint8_t b2 = spi_flex_read_byte(spi_n);
  spi_flex_usel(spi_n);
  
  uint16_t counts = ((b1<<8) | (b2<<0));
  return counts;
}

void MAX11100::init()
{
  spi_flex_init(spi_n);
}