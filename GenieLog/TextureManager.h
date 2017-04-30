#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <string>

class TextureManager
{
public:
	void addElement(const std::string& name, const std::string& path);

	const sf::Texture& getElement(const std::string& name) const;
	
private:
	std::map<std::string, sf::Texture> m_list;
};

