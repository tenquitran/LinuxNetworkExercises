#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <string>
#include <iostream>
#include <cstring>    // memset()
#include <climits>


#include <sys/socket.h>
#include <netinet/in.h>    // sockaddr_in
#include <arpa/inet.h>     // inet_pton()
#include <unistd.h>        // read()


// Maximum line length.
const size_t MAX_LINE = 4096;

// Backlog (the 2nd argument to listen().
const int LISTEN_Q = 1024;

///////////////////////////////////////////////////////////////////////

// Time server/client: data length in bytes.
// Messages are in the "YYYY-MM-DD hh:mm:ss" format; 
// that is 19 characters plus one byte for a NUL terminator.
const uint16_t TimeMessageLength = 20;

///////////////////////////////////////////////////////////////////////

// Display help on the command-line arguments usage (client version).
void showUsageCli(const char * const exeName);

// Display help on the command-line arguments usage (server version).
void showUsageSrv(const char * const exeName);

// Parse the command-line arguments (client version).
bool parseArgumentsCli(int argc, char* argv[],
	std::string& ipAddress, unsigned short& port);

// Parse the command-line arguments (server version).
bool parseArgumentsSrv(int argc, char* argv[],
	unsigned short& port);

///////////////////////////////////////////////////////////////////////

#endif

