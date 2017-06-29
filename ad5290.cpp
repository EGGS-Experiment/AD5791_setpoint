#include <assert.h>
#include "ad5290.hpp"

AD5290::AD5290(const unsigned char spi)
{
  spi_n = spi;
}

void AD5290::setCounts(uint16_t counts)
{
/*spi_flex_sel(spi_n);
  spi_flex_write_byte(spi_n, (counts >>  8) & 0xFF);
  spi_flex_write_byte(spi_n, (counts >>  0) & 0xFF);
  spi_flex_usel(spi_n);*/
}

void AD5290::init()
{
  spi_flex_init(spi_n);
}