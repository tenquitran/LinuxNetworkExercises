#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <string>

///////////////////////////////////////////////////////////////////////

// Time server/client: data length in bytes.
// Messages are in the "YYYY-MM-DD hh:mm:ss" format; 
// that is 19 characters plus one byte for a NUL terminator.
const uint16_t TimeMessageLength = 20;

///////////////////////////////////////////////////////////////////////

// Display help on the command-line arguments usage (client version).
void showUsageCli(const char * const exeName);

// Parse the command-line arguments (client version).
bool parseArgumentsCli(int argc, char* argv[],
	std::string& ipAddress, unsigned short& port);

///////////////////////////////////////////////////////////////////////

#endif

