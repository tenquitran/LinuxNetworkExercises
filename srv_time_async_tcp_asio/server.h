#ifndef _SERVER_H
#define _SERVER_H

#include <map>
#include <boost/asio.hpp>


class Server
{
public:
	explicit Server(unsigned short port);
	
	virtual ~Server();
	
	void start();
	
	void run();
	
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	
private:
	void startAccepting();

	void onAccept(unsigned int sockId, 
		boost::asio::ip::tcp::socket& sock, 
		const boost::system::error_code& err);

	void close();

	void handleClient(unsigned int sockId, 
		boost::asio::ip::tcp::socket& sock);
	
private:
	boost::asio::io_service m_io;

	const unsigned short m_port;

	boost::asio::ip::tcp::endpoint m_endpoint;
	
	boost::asio::ip::tcp::acceptor m_acceptor;
	
	// Client sockets.
	// Key: unique identifier of the socket; value: socket.
	std::map<unsigned int, boost::asio::ip::tcp::socket> m_clientSockets;
	
	// Current socket identifier.
	unsigned int m_socketId = {};
};

#endif

