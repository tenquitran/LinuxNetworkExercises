#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include "arguments.h"


// Command-line arguments parser.
class ArgParser
{
public:
	static Arguments parse(int argc, char *argv[]);
};

#endif

