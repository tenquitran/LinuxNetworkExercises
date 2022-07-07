#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <netinet/in.h>    // in_port_t


class Server
{
public:
	Server() = default;

	// Initialize the server.
	// Parameters: ipAddress - IP address;
	//             port      - port number.
	// Returns: true on success, false otherwise.
	bool initialize(const std::string& ipAddress, in_port_t port);
	
	// Display usage info.
	// Parameters: appName - program name.
	void showUsage(const char * appName) const;
	
	// Start the server.
	// Returns: true on success, false otherwise.
	bool launch();
	
private:
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

private:
	// IP address.
	std::string m_ipAddress;
	
	// Port number.
	in_port_t m_port = {};
};

#endif

