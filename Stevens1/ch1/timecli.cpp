#include "../../common.h"


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		showUsageCli(argv[0]);
		return 1;
	}
	
	std::string ipAddress;
	unsigned short port = {};
	
	if (!parseArgumentsCli(argc, argv, ipAddress, port))
	{
		return 2;
	}
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (-1 == sock)
	{
		perror("socket()");
		return 3;
	}
	
	sockaddr_in srvAddr;
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port   = htons(port);
	
	if (inet_pton(AF_INET, ipAddress.c_str(), &srvAddr.sin_addr) < 1)
	{
		perror("inet_pton()");
		return 4;
	}
	
	if (-1 == connect(sock, (const sockaddr *)&srvAddr, sizeof(srvAddr)))
	{
		perror("connect()");
		return 5;
	}
	
	char buff[MAX_LINE + 1];
	int n = {};
	
	while ((n = read(sock, buff, MAX_LINE)) > 0)
	{
		buff[n] = '\0';
		
		if (EOF == fputs(buff, stdout))
		{
			perror("fputs()");
			return 6;
		}
	}
	
	if (n < 0)
	{
		perror("read()");
		return 7;
	}

	return 0;
}

