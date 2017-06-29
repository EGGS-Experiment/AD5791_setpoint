#ifndef AD5621_H
#define AD5621_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD5621 {

public:
  AD5621(const unsigned char spi);

  void init();
  void setCounts(uint16_t counts);

private:
  unsigned char spi_n;
};


#endif // AD5621_H