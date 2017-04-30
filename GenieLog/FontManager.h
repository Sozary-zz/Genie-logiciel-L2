#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>

class FontManager
{
public:
	void addElement(const std::string& name, const std::string& path);

	const sf::Font& getElement(const std::string& name) const;

private:
	std::map<std::string, sf::Font> m_list;
};

