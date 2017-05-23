#include "CleO.hpp"

CleOClass CleO;

uint8_t *addstr(uint8_t *pc, const char *s)
{
  strcpy((char*)pc, s);
  return pc + strlen(s) + 1;
}
