#include <iostream>
#include "../lib/argParser.h"
#include "server.h"

///////////////////////////////////////////////////////////////////////

// Display usage information.
// Parameters: appName - program name.
void showUsage(const char * appName);

///////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	ArgParser ap;
	
	if (!ap.parse(true, argc, argv))
	{
		showUsage(argv[0]);
		return 2;
	}

	in_port_t port   = ap.getPort();
	
	std::cout << "Command-line arguments parsed. "
                 "Port number: " << port << std::endl;
	
	Server srv(port);
	
	if (!srv.initialize())
	{
		return 3;
	}

	if (!srv.launch())
	{
		return 4;
	}

	return 0;
}

void showUsage(const char * appName)
{
	std::cout << "\nUsage:\n" 
	          << appName << " <port_number>" << std::endl;
}

