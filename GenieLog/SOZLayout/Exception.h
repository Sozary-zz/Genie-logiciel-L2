#pragma once
#define INTERRUPT_WINDOW_EXCEPTION 0x1
#define BAD_TYPE_OF_DATA		   0x2

#include <string>
#include <sstream>

class Exception // very useless class, but instead of delete it, I use it for handle some static functions that I can qualify by "can handle an exception" function
{
public:

	static bool isNumber(std::string&);
	static bool isPureString(std::string&);
};

