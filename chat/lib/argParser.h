#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <netinet/in.h>    // in_port_t


// Command-line arguments parser.
class ArgParser
{
public:
	ArgParser() = default;

	// Parse the command-line arguments.
	// Returns: true on success, false otherwise.
	bool parse(int argc, char *argv[]);
	
	// Get IP address.
	std::string getIpAddress() const;
	
	// Get port number.
	in_port_t getPort() const;
	
private:
	std::string m_ipAddress;
	
	in_port_t m_port = {};
};

#endif

