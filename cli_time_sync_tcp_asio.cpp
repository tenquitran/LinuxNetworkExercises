#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "common.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////

void showUsage(const char * const exeName);

bool parseArguments(
	int argc, char* argv[],
	std::string& ipAddress, unsigned short& port);

std::string receiveData(asio::ip::tcp::socket& sock);

///////////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
	// IP address and port of the server.
	std::string ipAddress;
	unsigned short port = {};

	if (!parseArguments(argc, argv, ipAddress, port))
	{
		showUsage(argv[0]);
		return 1;
	}

	try
	{
		asio::ip::tcp::endpoint ep(
			asio::ip::address::from_string(ipAddress), 
			port);
		
		asio::io_service io;
		
		asio::ip::tcp protocol = asio::ip::tcp::v4();
		
		asio::ip::tcp::socket sock = asio::ip::tcp::socket(io, protocol);
		
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

void showUsage(const char * const exeName)
{
	std::cout << "Usage:\n"
	          << exeName << " <ip_address> <port_number>" << std::endl;
}

bool parseArguments(int argc, char* argv[],
	std::string& ipAddress, unsigned short& port)
{
	if (argc < 3)
	{
		return false;
	}
	
	ipAddress = argv[1];

	if (ipAddress.empty())
	{
		std::cerr << "Empty IP address\n";
		return false;
	}

	try
	{
		port = std::stoi(argv[2]);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to convert port number: " << argv[2] << "\n\n";
		return false;
	}
	
	return true;
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

