all: ctsta4 ctsts4

# For the output files naming scheme, see ReadMe.md

# Synchronous time client using Boost.Asio, TCPv4
ctsta4: cli_time_sync_tcp_asio.cpp
	g++ -Wall -I ../libs/boost_1_78_0 common.cpp cli_time_sync_tcp_asio.cpp -o ctsta4 -DASIO_STANDALONE -pthread

# Synchronous time client using sockets API, TCPv4
ctsts4: cli_time_sync_tcp_sock.cpp
	g++ -Wall common.cpp cli_time_sync_tcp_sock.cpp -o ctsts4

