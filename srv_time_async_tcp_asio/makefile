all: srvTime tmpSrv

srvTime: entryPoint.cpp
	g++ -Wall -I ../../libs/boost_1_78_0 server.cpp entryPoint.cpp -o srvtime -DASIO_STANDALONE -pthread

# TODO: temp
tmpSrv: tmpServer.cpp
	g++ -Wall -I ../../libs/boost_1_78_0 tmpServer.cpp -o tmpSrv -DASIO_STANDALONE -pthread
