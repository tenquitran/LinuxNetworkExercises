#include <iostream>
#include "../lib/argParser.h"
#include "server.h"

///////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	ArgParser ap;
	
	if (!ap.parse(argc, argv))
	{
		std::cerr << "Failed to parse the command-line arguments\n";
		return 1;
	}

	std::string addr = ap.getIpAddress();
	in_port_t port   = ap.getPort();
	
	std::cout << "IP address: " << addr 
	          << ", port: "     << port << std::endl;
	
	Server srv;
	
	if (!srv.initialize(addr, port))
	{
		srv.showUsage(argv[0]);
		return 2;
	}

	if (!srv.launch())
	{
		return 3;
	}

	return 0;
}

