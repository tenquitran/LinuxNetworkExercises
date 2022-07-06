#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "arguments.h"


class Server
{
public:
	Server() = default;

	bool initialize(const Arguments& args);
	
	// Display usage info.
	// Parameters: appName - program name.
	void showUsage(const char * appName) const;
	
	bool launch();
	
private:
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

private:
	std::string m_ipAddress;
	
	unsigned short m_port = {};
};

#endif

