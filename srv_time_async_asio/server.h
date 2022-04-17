#ifndef _SERVER_H
#define _SERVER_H

#include <boost/asio.hpp>


class Server
{
public:
	explicit Server(unsigned short port);
	
	virtual ~Server();
	
	void handleClient();
	
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	
private:
	void accept(boost::asio::ip::tcp::socket& sock);
	
	void onAccept(const boost::system::error_code& err, 
		boost::asio::ip::tcp::socket& sock);

	void stop();
	
private:
	const unsigned short m_port;

	boost::asio::io_service m_io;
	
	boost::asio::ip::tcp::endpoint m_endpoint;
	
	boost::asio::ip::tcp::acceptor m_acceptor;
	
	std::atomic<bool> m_shouldStop;
};

#endif

