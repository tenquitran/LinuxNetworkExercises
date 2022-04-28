#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "common.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////

std::string receiveData(asio::ip::tcp::socket& sock);

///////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	// IP address and port of the server.
	std::string ipAddress;
	unsigned short port = {};

	if (!parseArgumentsCli(argc, argv, ipAddress, port))
	{
		showUsageCli(argv[0]);
		return 1;
	}

	try
	{
		asio::ip::tcp::endpoint ep(
			asio::ip::address::from_string(ipAddress), 
			port);

		asio::ip::tcp protocol = asio::ip::tcp::v4();
		
		asio::io_service io;
		
		asio::ip::tcp::socket sock(io, protocol);

		sock.connect(ep);

		std::string response = receiveData(sock);
		
		if (response.empty())
		{
			std::cerr << "Failed to receive response from the server\n";
		}
		else
		{
			std::cout << "Server response: " << response << std::endl;
		}
		
		sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		
		sock.close();
	}
	catch (system::system_error& ex)
	{
		std::cerr << "Exception: " << ex.what() << '\n';
		return 2;
	}

	return 0;
}

std::string receiveData(asio::ip::tcp::socket& sock)
{
	std::string received;

	try
	{
		std::vector<char> buff(TimeMessageLength);
	
		std::size_t cbReceived = sock.receive(
			boost::asio::buffer(buff),
			0);
			
		if (cbReceived < TimeMessageLength)
		{
			std::cerr << __FUNCTION__ 
			          << ": receive error: expected " <<  TimeMessageLength << " bytes, "
			          << "received " << cbReceived << " bytes\n";
			return "";
		}
		
		std::cout << cbReceived << " bytes received from the server" << std::endl;

		received.reserve(cbReceived);

		for (auto c : buff)
		{
			received += c;
		}
	}
	catch (system::system_error& ex)
	{
		std::cerr << __FUNCTION__ << ": exception: " << ex.what() << '\n';
		return "";
	}
	
	return received;
}

