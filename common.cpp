#include <iostream>
#include <climits>
#include "common.h"

///////////////////////////////////////////////////////////////////////


void showUsageCli(const char * const exeName)
{
	std::cout << "Usage:\n"
	          << exeName << " <ip_address> <port_number>" << std::endl;
}

bool parseArgumentsCli(int argc, char* argv[],
	std::string& ipAddress, unsigned short& port)
{
	if (argc < 3)
	{
		return false;
	}
	
	ipAddress = argv[1];

	if (ipAddress.empty())
	{
		std::cerr << "Empty IP address\n";
		return false;
	}

	try
	{
		int portInt = std::stoi(argv[2]);
		
		std::cout << "Port: " << portInt << std::endl;
		
		if (   portInt < 1
		    || portInt > USHRT_MAX)
		{
			std::cerr << "Port number should be between 1 and " << USHRT_MAX << ": " << portInt << "\n";
			return false;
		}
		
		port = portInt;
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to convert port number: " << argv[2] << "\n\n";
		return false;
	}
	
	return true;
}

