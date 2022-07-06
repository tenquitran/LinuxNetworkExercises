#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>


struct Arguments
{
public:
	std::string m_ipAddress;
	
	unsigned short m_port = {};
};

#endif

