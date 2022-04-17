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
}

Server::~Server()
{
	m_acceptor.close();
}

void Server::handleClient()
{
	asio::ip::tcp::socket sock = asio::ip::tcp::socket(m_io);
	
	if (!accept(sock))
	{
		return;
	}
	
	// TODO: unfinished
}

bool Server::accept(asio::ip::tcp::socket& sock)
{
	m_acceptor.async_accept(sock, 
		[this, &sock] (const system::error_code& err) {
			onAccept(err, sock);
		});
		
	return 0;
}

void Server::onAccept(const boost::system::error_code& err, 
		boost::asio::ip::tcp::socket& sock)
{
	// TODO: implement
}

