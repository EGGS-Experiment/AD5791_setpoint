#ifndef AD5544_H
#define AD5544_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD5544 {

public:
  AD5544(const unsigned char spi);

  void init();
  void setCounts(uint32_t counts, uint32_t output_line);

private:
  unsigned char spi_n;
};

#endif // AD5544_H
