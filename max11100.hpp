#ifndef MAX11100_H
#define MAX11100_H 1

#include <stdint.h>
#include "spi_flex.h"

class MAX11100 {

public:
  MAX11100(const unsigned char spi);

  void init();
  uint16_t readCounts();

private:
  unsigned char spi_n;
};

#endif // MAX11100_H