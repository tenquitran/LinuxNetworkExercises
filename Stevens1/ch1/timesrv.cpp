#include "../../common.h"
#include <time.h>


int main(int argc, char* argv[])
{
	unsigned short port = {};
	
	if (!parseArgumentsSrv(argc, argv, port))
	{
		showUsageSrv(argv[0]);
		return 1;
	}
	
	std::cout << "Press Ctrl^C to exit\n";

	// Listening socket.
	int lsSock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (-1 == lsSock)
	{
		perror("socket()");
		return 2;
	}
	
	sockaddr_in srvAddr;
	
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family      = AF_INET;
	srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvAddr.sin_port        = htons(port);
	
	int res = bind(lsSock, (const sockaddr *)&srvAddr, sizeof(srvAddr));
	
	if (-1 == res)
	{
		perror("bind()");
		return 3;
	}
	
	res = listen(lsSock, LISTEN_Q);
	
	if (-1 == res)
	{
		perror("listen()");
		return 4;
	}
	
	const size_t CbBuff = 100;
	char buff[CbBuff];
	
	while (true)
	{
		sockaddr_in cliAddr;
		memset(&cliAddr, 0, sizeof(cliAddr));
		
		socklen_t len = sizeof(cliAddr);
	
		// Connected socket.
		int cnSock = accept(lsSock, (sockaddr *)&cliAddr, &len);
		
		char addrBuff[INET_ADDRSTRLEN];
		
		inet_ntop(AF_INET, &(cliAddr.sin_addr), addrBuff, INET_ADDRSTRLEN);
		
		std::cout << "Client connection: " << addrBuff << std::endl;
		
		time_t tm = time(nullptr);

		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&tm));
		
		const size_t toWrite = strlen(buff);
		
		ssize_t written = write(cnSock, buff, toWrite);
		
		if (-1 == written)
		{
			perror("write()");
			return 5;
		}
		else if (written != toWrite)
		{
			std::cerr << "Write error: expected " << toWrite 
			          << " bytes, actual " << written << " bytes\n";
		}
		
		if (-1 == close(cnSock))
		{
			perror("close()");
			return 6;
		}
	}

	return 0;
}

