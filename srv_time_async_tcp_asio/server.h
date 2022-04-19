#ifndef _SERVER_H
#define _SERVER_H

#include <boost/asio.hpp>


class Server
{
public:
	explicit Server(unsigned short port);
	
	virtual ~Server();
	
	void start();
	
	void run();
	
	void stop();
	
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	
private:
	void startAccepting();

	void onAccept(std::shared_ptr<boost::asio::ip::tcp::socket>& sock, 
		const boost::system::error_code& err);

	void close();
	
	void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket>& sock);
	
private:
	boost::asio::io_service m_io;

	const unsigned short m_port;

	boost::asio::ip::tcp::endpoint m_endpoint;
	
	boost::asio::ip::tcp::acceptor m_acceptor;
	
	std::atomic<bool> m_shouldStop;
};

#endif

