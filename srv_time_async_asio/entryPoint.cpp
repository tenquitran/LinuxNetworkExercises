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
	
#if 0
	asio::io_service io;
	
	asio::ip::tcp::endpoint endpoint = asio::ip::tcp::endpoint(asio::ip::address_v4::any(),
			port);
	
	asio::ip::tcp::acceptor acceptor = asio::ip::tcp::acceptor(io, endpoint);
	
	while (true)
	{
		asio::ip::tcp::socket sock = asio::ip::tcp::socket(io);
		
		acceptor.async_accept(sock, 
			[this, sock] (const boost::system::error& err) {
				if (0 == err)
				{
					// TODO: handle the client connection
				}
				else
				{
					std::cout << "async_accept() failed: " 
					          << err.message << "(" << err.value() << ")" << std::endl;
				}
			});
	}
#endif

	return 0;
}

void showUsage(const char * const exeName)
{
	std::cout << "Usage:\n"
		      << exeName << " <port_number>" << std::endl;
}

