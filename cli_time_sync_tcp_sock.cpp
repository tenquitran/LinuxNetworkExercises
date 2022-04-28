#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.h"

///////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	// IP address and port of the server.
	std::string ipAddress;
	unsigned short port = {};

	if (!parseArgumentsCli(argc, argv, ipAddress, port))
	{
		showUsageCli(argv[0]);
		return 1;
	}
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (-1 == sock)
	{
		perror("socket()");
		return 2;
	}
	
	sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port   = htons(port);
	
	int res = inet_pton(AF_INET, ipAddress.c_str(), &srvaddr.sin_addr);
	
	if (0 == res)
	{
		std::cerr << "Invalid IP address: " << ipAddress << '\n';
		return 3;
	}
	else if (res < 0)
	{
		perror("inet_pton()");
		return 4;
	}
	
	if (-1 == connect(sock, (sockaddr *)&srvaddr, sizeof(srvaddr)))
	{
		perror("connect()");
		return 5;
	}
	
	std::cout << "Server response: ";

	char buff[TimeMessageLength + 1];
	
	int cbRead = {};
	
	while ((cbRead = read(sock, buff, TimeMessageLength)) > 0)
	{
		buff[cbRead] = '\0';

		std::cout << buff << std::endl;
	}
	
	if (cbRead < 0)
	{
		perror("read()");
		return 6;
	}
	
	if (-1 == shutdown(sock, SHUT_RDWR))
	{
		perror("shutdown()");
		return 7;
	}
	
	if (-1 == close(sock))
	{
		perror("close()");
		return 8;
	}

	return 0;
}

