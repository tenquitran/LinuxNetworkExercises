#include "arguments.h"
#include "argParser.h"
#include "server.h"

///////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	Arguments args = ArgParser::parse(argc, argv);
	
	Server srv;
	
	if (!srv.initialize(args))
	{
		srv.showUsage(argv[0]);
		return 1;
	}

	if (!srv.launch())
	{
		return 2;
	}

	return 0;
}

