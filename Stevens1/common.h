#include <iostream>
#include <cstring>    // memset()


#include <sys/socket.h>
#include <netinet/in.h>    // sockaddr_in
#include <arpa/inet.h>     // inet_pton()
#include <unistd.h>        // read()


// Maximum line length.
const size_t MAX_LINE = 4096;

