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
	m_shouldStop.store(false);
}

Server::~Server()
{
	close();
}

void* Server::tpRun(void *arg)
{
	Server *pThis = (Server *)arg;

	// TODO: implement

	return 0;
}

bool Server::start()
{
	std::cout << "Server is starting..." << std::endl;

#if 0
	int res = pthread_create(&m_tid, nullptr, &tpRun, this);
			
	if (0 != res)
	{
		std::cerr << "Failed to create thread: " << res << '\n';
		return false;
	}
#endif

#if 1
	m_acceptor.listen();

	startAccepting();
	
	m_io.run();
#endif

	return true;
}

void Server::stop()
{
	std::cout << "Stopping the server..." << std::endl;

	m_shouldStop.store(true);
}

void Server::close()
{
	std::cout << "Closing the acceptor..." << std::endl;

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
	if (0 == err.value())
	{
		std::cout << __FUNCTION__ << " success" << std::endl;
		
		handleClient(sock);
	}
	else
	{
		std::cerr << __FUNCTION__ << ": error: " << err.value() << " (" << err.message() << ")\n";
		return;
	}

	if (m_shouldStop.load())
	{
		std::cout << __FUNCTION__ << ": going to close()..." << std::endl;
		
		close();
	}
	else
	{
		startAccepting();
	}
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

