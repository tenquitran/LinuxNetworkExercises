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

	void onAccept(const boost::system::error_code& err, 
		boost::asio::ip::tcp::socket& sock);

	void close();
	
	void handleClient(boost::asio::ip::tcp::socket& sock);
	
	// TODO: temp
	static void onSent(const boost::system::error_code& err, std::size_t cbSent);
	
private:
	boost::asio::io_service m_io;

	const unsigned short m_port;

	boost::asio::ip::tcp::endpoint m_endpoint;
	
	boost::asio::ip::tcp::acceptor m_acceptor;
	
	std::atomic<bool> m_shouldStop;
	
	// TODO: temp
	static std::atomic<int> tmp2;
};

#endif

