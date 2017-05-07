#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>


class EditList:public sf::Drawable
{
public:
	EditList(const sf::Font& font, sf::Vector2f size, sf::Vector2f position);

	~EditList();

	void addData(const std::string& text);
	void init();


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<sf::Text> m_data;
	sf::RectangleShape m_shape[2];
	sf::Font m_font;

	const int m_max_items_visible;
	int m_i_ignore;
};

