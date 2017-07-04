#ifndef AD7921_H
#define AD7921_H 1

#include <stdint.h>
#include "spi_flex.h"

class AD7921 {

public:
  AD7921(const unsigned char spi);

  void init();
  uint32_t  readCounts();

private:
  unsigned char spi_n;
};

#endif // AD7921_H
