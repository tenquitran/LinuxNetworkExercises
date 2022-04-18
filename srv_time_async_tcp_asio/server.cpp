#include <iostream>
#include <cstdio>
#include <time.h>
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

// TODO: temp
void acceptHandler(const system::error_code& err)
{
	if (0 != err.value())
	{
		std::cerr << __FUNCTION__ << ": error: " << err.message() << '\n';
	}
	else
	{
		std::cout << __FUNCTION__ << " : accepted" << std::endl;
	}
}

void Server::startAccepting()
{
	asio::ip::tcp::socket sock(m_io);

#if 0
	// TODO: temp: sync accept
	m_acceptor.accept(sock);
	handleClient(sock);
#else
	// TODO: temp
	m_acceptor.async_accept(sock, 
	
#if 1
		//[this, &sock] (const system::error_code& err) {
		[] (const system::error_code& err) {		
			if (0 != err.value())
			{
				std::cerr << "async_accept() error: " << err.value() << " (" << err.message() << ")\n";
			}
			else
			{
				std::cout << "async_accept() success" << std::endl;
			}
		});
#else
	acceptHandler);
	
	// TODO: temp
	std::cout << "After async_accept()" << std::endl;
#endif

#endif

	// TODO: temp
#if 0	
	m_acceptor.async_accept(sock, 
		[this, &sock] (const system::error_code& err) {
			onAccept(err, sock);
		});
#endif
}

void Server::onAccept(const system::error_code& err, asio::ip::tcp::socket& sock)
{
	// TODO: temp
	std::cout << "Entering " << __FUNCTION__ << std::endl;

	if (0 == err.value())
	{
		handleClient(sock);
	}
	else
	{
		std::cerr << __FUNCTION__ << ": error: " << err.message() << '\n';
		return;
	}
	
	if (m_shouldStop.load())
	{
		close();
	}
	else
	{
		startAccepting();
	}
}

void Server::handleClient(asio::ip::tcp::socket& sock)
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
}

