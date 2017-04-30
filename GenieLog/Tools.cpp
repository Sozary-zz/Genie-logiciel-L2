#include "Tools.hpp"

std::vector<std::string> stringSplit(const std::string & s, char c)
{
	std::vector< std::string> res;
	std::stringstream ss;
	ss.str(s);

	std::string item;
	while (std::getline(ss, item, c))
		res.push_back(item);
	return res;
}
