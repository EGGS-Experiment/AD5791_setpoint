#ifndef AD5209_H
#define AD5209_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD5209 {

public:
  AD5209(const unsigned char spi);

  void init();
  void setCounts(uint16_t counts);

private:
  unsigned char spi_n;
};

#endif // AD5209_H