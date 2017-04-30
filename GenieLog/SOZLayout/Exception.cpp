#include "Exception.h"

using namespace std;

bool Exception::isNumber(string& s)
{
	double a;
	istringstream iss(s);

	return (iss >> a) && !(iss >> s);
}

bool Exception::isPureString(string& s)
{
	for (int i = 0; i < s.size(); ++i)
		if (isdigit(s[i]))
			return false;
	return true;
}
