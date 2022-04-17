#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////


// Time server/client: data length in bytes.
// Messages are in the "YYYY-MM-DD hh:mm:ss" format; 
// that is 19 characters plus one byte for a NUL terminator.
uint16_t TimeMessageLength = 20;

#endif

