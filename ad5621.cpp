#include <assert.h>
#include "ad5621.hpp"

AD5621::AD5621(const unsigned char spi)
{
  spi_n = spi;
}

void AD5621::setCounts(uint16_t counts)
{
  spi_flex_sel(spi_n);
  spi_flex_write_byte(spi_n, (counts >>  8) & 0xFF);
  spi_flex_write_byte(spi_n, (counts >>  0) & 0xFF);
  spi_flex_usel(spi_n);
}

void AD5621::init()
{
  spi_flex_init(spi_n);
}