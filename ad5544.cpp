#include <assert.h>
#include "ad5544.hpp"

AD5544::AD5544(const unsigned char spi)
{
  spi_n = spi;
}

//counts denotes value (16bit)
//output_line denotes DAC (2bit)
void AD5544::setCounts(uint32_t counts, uint32_t output_line)
{
  spi_flex_sel(spi_n);
  spi_flex_write_byte(spi_n, output_line & 0x03);
  spi_flex_write_byte(spi_n, (counts>>8) & 0xFF);
  spi_flex_write_byte(spi_n, counts & 0xFF);
  spi_flex_usel(spi_n);
}

void AD5544::init()
{
  spi_flex_init(spi_n);
}
