#include "EditList.h"
#include <iostream>

using namespace std;
using namespace sf;

EditList::EditList(const sf::Font & font, sf::Vector2f size, sf::Vector2f position) :
	m_max_items_visible(size.y / 15.f), m_font(font), m_i_ignore(0)
{
	m_shape[0].setFillColor(Color::Black);
	m_shape[1].setFillColor(Color::White);

	m_shape[0].setSize(size);
	m_shape[1].setSize(Vector2f(size.x - 4.f, size.y - 4.f));

	m_shape[0].setPosition(position);
	m_shape[1].setPosition(position.x + 2, position.y + 2);


}

void EditList::addData(const string & text)
{
	sf::Text tmp;
	tmp.setFont(m_font);
	tmp.setString(text);
	tmp.setCharacterSize(12);
	tmp.setColor(Color::Black);

	tmp.setPosition(Vector2f(m_shape[1].getPosition().x, m_shape[1].getPosition().y + m_shape[1].getSize().y - tmp.getGlobalBounds().height - 8));

	int compt = 1;
	for (int j = m_data.size() - 1; j >= 0; j--)
	{
		if (compt >= m_max_items_visible)
		{
			m_i_ignore = j + 1;
			break;
		}

		m_data[j].move(0, -12);
		compt++;
	}


	m_data.push_back(tmp);
}

void EditList::init()
{
	m_data.clear();
}



void EditList::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_shape[0]);
	target.draw(m_shape[1]);


	for (int j = m_data.size() - 1; j >= m_i_ignore; --j)
		target.draw(m_data[j]);

}

EditList::~EditList()
{
}
