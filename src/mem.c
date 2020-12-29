#include <mem.h>

extern char _kstart;
extern char _kend;

char *kstart = &_kstart;
char *kend = &_kend;
u16 klowmem = 0;
