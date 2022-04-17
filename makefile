all: ctsta

# For the output files naming scheme, see ReadMe.md

# Synchronous time client using Boost.Asio, TCP
ctsta: cli_time_sync_tcp_asio.cpp
	g++ -Wall -I ../libs/boost_1_78_0 cli_time_sync_tcp_asio.cpp -o ctsta -DASIO_STANDALONE -pthread
