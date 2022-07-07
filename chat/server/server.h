#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <netinet/in.h>    // in_port_t


class Server
{
public:
	// Parameters: port - port number.
	explicit Server(in_port_t port);

	// Initialize the server.
	// Returns: true on success, false otherwise.
	bool initialize();

	// Start the server.
	// Returns: true on success, false otherwise.
	bool launch();
	
private:
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

private:
	// Port number.
	in_port_t m_port = {};
};

#endif

