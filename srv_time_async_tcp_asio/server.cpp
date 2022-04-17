#include <iostream>
#include "server.h"

///////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////


Server::Server(unsigned short port)
	: m_port(port), 
	  m_endpoint(asio::ip::address_v4::any(), m_port),
	  m_acceptor(m_io, m_endpoint)
{
	m_shouldStop.store(false);
}

Server::~Server()
{
	close();
}

void Server::start()
{
	m_acceptor.listen();
	
	startAccepting();
}

void Server::stop()
{
	m_shouldStop.store(true);
}

void Server::close()
{
	m_acceptor.close();
}

void Server::startAccepting()
{
	asio::ip::tcp::socket sock = asio::ip::tcp::socket(m_io);
	
	m_acceptor.async_accept(sock, 
		[this, &sock] (const system::error_code& err) {
			onAccept(err, sock);
		});
}

void Server::onAccept(const boost::system::error_code& err, 
		boost::asio::ip::tcp::socket& sock)
{
	if (0 == err.value())
	{
		handleClient(sock);
	}
	else
	{
		std::cerr << __FUNCTION__ << ": error: " << err.message() << '\n';
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

void Server::handleClient(boost::asio::ip::tcp::socket& sock)
{
	// TODO: stub
}

