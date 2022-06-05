#include "../../common.h"


// Usage example for the loopback address and port 9988:
//
// $ ./timecli6 ::1 9988
int main(int argc, char* argv[])
{
	std::string ipAddress;
	unsigned short port = {};
	
	if (!parseArgumentsCli(argc, argv, ipAddress, port))
	{
		showUsageCli(argv[0]);
		return 1;
	}
	
	int sock = socket(AF_INET6, SOCK_STREAM, 0);
	
	if (-1 == sock)
	{
		perror("socket()");
		return 2;
	}
	
	sockaddr_in6 srvAddr;
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin6_family = AF_INET6;
	srvAddr.sin6_port   = htons(port);
	
	if (inet_pton(AF_INET6, ipAddress.c_str(), &srvAddr.sin6_addr) < 1)
	{
		perror("inet_pton()");
		return 3;
	}
	
	if (-1 == connect(sock, (const sockaddr *)&srvAddr, sizeof(srvAddr)))
	{
		perror("connect()");
		return 4;
	}
	
	char buff[MAX_LINE + 1];
	int n = {};
	
	while ((n = read(sock, buff, MAX_LINE)) > 0)
	{
		buff[n] = '\0';
		
		if (EOF == fputs(buff, stdout))
		{
			perror("fputs()");
			return 5;
		}
	}
	
	if (n < 0)
	{
		perror("read()");
		return 6;
	}

	return 0;
}

