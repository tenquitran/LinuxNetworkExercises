all: srvtime

srvtime: entryPoint.cpp
	g++ -Wall -I ../libs/boost_1_78_0 server.cpp entryPoint.cpp -o srvtime -DASIO_STANDALONE -pthread

