#include <iostream>
#include <boost/asio.hpp>

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////

void showUsage(const char * const exeName);

bool parseArguments(
	int argc, char* argv[],
	std::string& ipAddress, unsigned short& port);

///////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	std::string ipAddress;
	unsigned short port = {};

	if (!parseArguments(argc, argv, ipAddress, port))
	{
		showUsage(argv[0]);
		return 1;
	}

	;

	return 0;
}

void showUsage(const char * const exeName)
{
	std::cout << "Usage:\n"
	          << exeName << " <ip_address> <port_number>" << std::endl;
}

bool parseArguments(int argc, char* argv[],
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
		port = std::stoi(argv[2]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to convert port number: " << argv[2] << "\n\n";
		return false;
	}
	
	return true;
}

