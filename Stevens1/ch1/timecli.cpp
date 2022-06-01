#include "../common.h"


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Usage:\n\n" 
		          << argv[0] << " <ip_address> <port>" << std::endl;
		return 1;
	}
	
	int port = std::stoi(argv[2]);
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (-1 == sock)
	{
		perror("socket()");
		return 2;
	}
	
	sockaddr_in srvAddr;
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port   = htons(port);
	
	if (inet_pton(AF_INET, argv[1], &srvAddr.sin_addr) < 1)
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

