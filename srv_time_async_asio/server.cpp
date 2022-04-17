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
	//m_acceptor.close();
}

void Server::stop()
{
	m_acceptor.close();
}

void Server::handleClient()
{
	asio::ip::tcp::socket sock = asio::ip::tcp::socket(m_io);
	
	accept(sock);
}

void Server::accept(asio::ip::tcp::socket& sock)
{
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
		// TODO: handle the client
	}
	else
	{
		std::cerr << __FUNCTION__ << ": error: " << err.message() << '\n';
	}
	
	if (!m_shouldStop.load())
	{
		accept(sock);
	}
	else
	{
		stop();
	}
}

