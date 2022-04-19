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
	
	try
	{
#if 0
		// TODO: temp
		std::cout << "Port: " << port << std::endl;
		asio::io_service io;
		asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port);
	  	asio::ip::tcp::acceptor acceptor(io, ep);

	  	acceptor.listen();
	  	
	  	//io.run();

	  	asio::ip::tcp::socket sock(io);
	
		acceptor.async_accept(sock, 
			[] (const system::error_code& err) {
				std::cout << "Inside" << std::endl;
			
				if (0 != err.value())
				{
					std::cerr << __FUNCTION__ << ": error: " << err.message() << '\n';
				}
				else
				{
					std::cout << __FUNCTION__ << " : accepted" << std::endl;
				}
			});
		
		io.run();
			
		std::cout << "After async_accept()" << std::endl;

		sleep(10);
#else
		Server srv(port);
		
		if (srv.start())
		{
			return 3;
		}
		
		//srv.run();
		
		// TODO: temp
		sleep(10);
		
		srv.stop();
#endif
	}
	catch (system::system_error& ex)
	{
		std::cerr << "Exception: " << ex.what() << '\n';
		return 4;
	}

	return 0;
}

void showUsage(const char * const exeName)
{
	std::cout << "Usage:\n"
		      << exeName << " <port_number>" << std::endl;
}

