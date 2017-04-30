#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class TabHandler
{
public:
	TabHandler(std::vector<Tab*> tabs, sf::RenderWindow& window);
	void switchTab(int i_tab);
	void run();

private:
	std::vector<Tab*> m_tabs;
	Tab* m_current_tab;
	sf::RenderWindow& m_window_context;
};

class Tab
{
public:
	virtual void draw(const float delta_time) = 0;
	virtual void update(const float delta_time) = 0;
	virtual void eventLoop() = 0;
};