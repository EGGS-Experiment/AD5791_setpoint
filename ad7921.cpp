#include <assert.h>
#include "ad7921.hpp"

AD7921::AD7921(const unsigned char spi)
{
  spi_n = spi;
}

uint32_t  AD7921::readCounts()
{ 
  int i = 0;

  for (i=0;i<3;i++) {
    spi_flex_sel(spi_n); //conversion for channel 0
    spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //set next conversion to channel 0
    spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //read channel 0
    spi_flex_usel(spi_n);
  }
  spi_flex_sel(spi_n); //conversion for channel 0
  uint32_t b0 = spi_flex_read_write_byte(spi_n, 0x20) & 0xFF; //set next conversion to channel 1
  uint32_t b1 = spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //read channel 0
  spi_flex_usel(spi_n);
  
  for (i=0;i<3;i++) {
    spi_flex_sel(spi_n); //conversion for channel 1
    spi_flex_read_write_byte(spi_n, 0x20) & 0xFF; //set next conversion to channel 1
    spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //read channel 1
    spi_flex_usel(spi_n);
  }
  spi_flex_sel(spi_n); //conversion for channel 1
  uint32_t b2 = spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //set next conversion to channel 0
  uint32_t b3 = spi_flex_read_write_byte(spi_n, 0x00) & 0xFF; //read channel 1
  spi_flex_usel(spi_n);
  
  uint32_t counts = ((b2<<24) | (b3<<16) | (b0<<8) | (b1<<0));
  return counts;
}

void AD7921::init()
{
  spi_flex_init(spi_n);
}
