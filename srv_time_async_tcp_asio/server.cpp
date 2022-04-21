#include <iostream>
#include <cstdio>
#include <time.h>
#include "server.h"
#include "../common.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////


Server::Server(unsigned short port)
	: m_io(), 
	  m_port(port), 
	  m_endpoint(asio::ip::address_v4::any(), m_port),
	  m_acceptor(m_io, m_endpoint)
{
}

Server::~Server()
{
	close();
}

void Server::start()
{
	std::cout << "Server is starting (press Ctrl+C to stop it)..." << std::endl;

	m_acceptor.listen();

	startAccepting();
}

void Server::close()
{
	m_acceptor.close();
	
	std::cout << "Acceptor is closed" << std::endl;
}

void Server::run()
{
	m_io.run();
}

void Server::startAccepting()
{
	m_clientSockets.insert(std::make_pair(++m_socketId, asio::ip::tcp::socket(m_io)));
	
	std::cout << "Socket " << m_socketId << " created" << std::endl;

	m_acceptor.async_accept(m_clientSockets.at(m_socketId), 
		[this](const system::error_code& err) {
			onAccept(m_socketId, m_clientSockets.at(m_socketId), err);
		});
}

void Server::onAccept(unsigned int sockId, 
	asio::ip::tcp::socket& sock, 
	const system::error_code& err)
{
	if (0 == err.value())
	{
		std::cout << __FUNCTION__ << " success" << std::endl;

		handleClient(sockId, sock);
	}
	else
	{
		std::cerr << __FUNCTION__ << ": error: " << err.value() << " (" << err.message() << ")\n";
	}

	startAccepting();
}

void Server::handleClient(unsigned int sockId, asio::ip::tcp::socket& sock)
{
	std::string clientIp = sock.remote_endpoint().address().to_string();
	
	unsigned short clientPort = sock.remote_endpoint().port();

	std::cout << "Accepted client connection: " << clientIp << ":" << clientPort << std::endl;
	
	// Asynchronously send to the client a string representing current time.
	// Use the "YYYY-MM-DD hh:mm:ss" format.
	
	time_t tm0 = time(nullptr);
	
	tm *loc = localtime(&tm0);
	
	char buff[TimeMessageLength];
	
	snprintf(buff, TimeMessageLength, "%04d-%02d-%02d %02d:%02d:%02d", 
		loc->tm_year + 1900, 
		loc->tm_mon + 1, 
		loc->tm_mday, 
		loc->tm_hour, 
		loc->tm_min, 
		loc->tm_sec);
		
	buff[TimeMessageLength - 1] = '\0';

	async_write(sock, 
		asio::buffer(buff, TimeMessageLength), 
		[] (const system::error_code& err, std::size_t cbSent) {
			if (0 != err.value())
			{
				std::cerr << "async_write() failed: " << err.message() << '\n';
			}
			else
			{
				std::cout << cbSent << " bytes were sent to the client" << std::endl;
			}
		});

	m_clientSockets.erase(sockId);
	
	std::cout << "Socket " << sockId << " deleted" << std::endl;
}

