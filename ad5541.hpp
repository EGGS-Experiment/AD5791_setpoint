#ifndef AD5541_H
#define AD5541_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD5541 {

public:
  AD5541(const unsigned char spi);

  void init();
  void setCounts(uint16_t counts);

private:
  unsigned char spi_n;
};

#endif // AD5541_H
