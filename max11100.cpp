#include <assert.h>
#include "max11100.hpp"

MAX11100::MAX11100(const unsigned char spi)
{
  spi_n = spi;
}

void MAX11100::setCounts(uint16_t counts)
{
/*spi_flex_sel(spi_n);
  spi_flex_write_byte(spi_n, (counts >>  8) & 0xFF);
  spi_flex_write_byte(spi_n, (counts >>  0) & 0xFF);
  spi_flex_usel(spi_n);*/
}

void MAX11100::init()
{
  spi_flex_init(spi_n);
}