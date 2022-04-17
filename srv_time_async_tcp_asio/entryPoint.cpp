#include <iostream>
#include <string>
#include "server.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////

void showUsage(const char * const exeName);

///////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		showUsage(argv[0]);
		return 1;
	}
	
	unsigned short port = {};
	
	try
	{
		port = std::stoi(argv[1]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to convert port number: " << argv[1] << "\n\n";
		showUsage(argv[0]);
		return 2;
	}
	
	// TODO: are there any exceptions possible?
	Server srv(port);

	return 0;
}

void showUsage(const char * const exeName)
{
	std::cout << "Usage:\n"
		      << exeName << " <port_number>" << std::endl;
}

