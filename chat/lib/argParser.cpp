#include <iostream>
#include <climits>    // USHRT_MAX
#include "argParser.h"

///////////////////////////////////////////////////////////////////////


bool ArgParser::parse(bool isServer, int argc, char *argv[])
{
	// We assume that the server needs a port number, 
	// and the client - IP address and port number.
	if (   ( isServer && 2 != argc)
	    || (!isServer && 3 != argc))
	{
		std::cerr << "Invalid number of command-line arguments.\n";
		return false;
	}

	if (!isServer)
	{
		m_ipAddress = argv[1];
	}

	std::string portStr;
	int portInt = {};
	
	try
	{
		portStr = (isServer ? argv[1] : argv[2]);

		portInt = std::stoi(portStr);
	}
	catch (const std::invalid_argument& ex)
	{
		std::cerr << "Failed to parse port number \"" << portStr << "\": "
		          << "invalid argument\n";
		return false;
	}
	catch (const std::out_of_range& ex)
	{
		std::cerr << "Failed to parse port number \"" << portStr << "\": "
		          << "out of range\n";
		return false;
	}
	
	if (   portInt < 1
		|| portInt > USHRT_MAX)
	{
		std::cerr << "Port number should be between 1 and " << USHRT_MAX << '\n';
		return false;
	}
	
	m_port = portInt;

	return true;
}

std::string ArgParser::getIpAddress() const
{
	return m_ipAddress;
}
	
in_port_t ArgParser::getPort() const
{
	return m_port;
}

