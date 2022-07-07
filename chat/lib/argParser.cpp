#include "argParser.h"

///////////////////////////////////////////////////////////////////////


bool ArgParser::parse(int argc, char *argv[])
{
	// TODO: stub
	return false;
}

std::string ArgParser::getIpAddress() const
{
	return m_ipAddress;
}
	
in_port_t ArgParser::getPort() const
{
	return m_port;
}

