#include <iostream>
#include <cstdio>
#include <time.h>
//#include <boost/bind/bind.hpp>
#include "server.h"
#include "../common.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////

std::atomic<int> Server::tmp2;

///////////////////////////////////////////////////////////////////////


Server::Server(unsigned short port)
	: m_io(), 
	  m_port(port), 
	  m_endpoint(asio::ip::address_v4::any(), m_port),
	  m_acceptor(m_io, m_endpoint)
{
	m_shouldStop.store(false);
	
	tmp2.store(1);
}

Server::~Server()
{
	close();
}

void Server::start()
{
	std::cout << "Server is starting..." << std::endl;

	m_acceptor.listen();

	startAccepting();
}

void Server::stop()
{
	std::cout << "Server is stopping..." << std::endl;

	m_shouldStop.store(true);
}

void Server::close()
{
	std::cout << "tmp2 = " << tmp2.load() << std::endl;

	m_acceptor.close();
	
	std::cout << "Acceptor is closed" << std::endl;
}

void Server::run()
{
	m_io.run();
}

void Server::startAccepting()
{
	std::shared_ptr<asio::ip::tcp::socket> sock = std::make_shared<asio::ip::tcp::socket>(m_io);

	m_acceptor.async_accept(*sock.get(), 
		[this, &sock](const system::error_code& err) {
			onAccept(sock, err);
		});
}

void Server::onAccept(std::shared_ptr<boost::asio::ip::tcp::socket>& sock, 
	const boost::system::error_code& err)
{
	if (0 != err.value())
	{
		std::cerr << __FUNCTION__ << ": error: " << err.value() << " (" << err.message() << ")\n";
		return;
	}
	
	std::cout << __FUNCTION__ << " success" << std::endl;
	
	// TODO: temp
	handleClient(sock);
	
#if 0
	if (m_shouldStop.load())
	{
		close();
	}
	else
	{
		startAccepting();
	}
#endif
}

void Server::handleClient(std::shared_ptr<boost::asio::ip::tcp::socket>& sock)
{
	std::string clientIp = sock->remote_endpoint().address().to_string();
			
	unsigned short clientPort = sock->remote_endpoint().port();
			
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
	
	async_write(*sock.get(), 
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
}

