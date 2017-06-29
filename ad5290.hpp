#ifndef AD5290_H
#define AD5290_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD5290 {

public:
  AD5290(const unsigned char spi);

  void init();
  void setCounts(uint32_t counts);

private:
  unsigned char spi_n;
};

#endif // AD5290_H