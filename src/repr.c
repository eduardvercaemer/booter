#include <repr.h>

extern char repr_nibble(u8 v)
{
    if (v < 10) return '0' + v;
    else return 'a' + v - 10;
}
