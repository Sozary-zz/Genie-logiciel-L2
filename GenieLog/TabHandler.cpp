#include "TabHandler.hpp"

TabHandler::TabHandler(std::vector<Tab*> tabs, sf::RenderWindow& window) :
	m_tabs(tabs),  m_window_context(window)
{
	if (!m_tabs.empty())
		m_current_tab = m_tabs.front();
}

void TabHandler::switchTab(int i_tab)
{
}

void TabHandler::run()
{
	sf::Clock clock;

	while (m_window_context.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (m_tabs.empty()) continue;
		m_current_tab->eventLoop();
		m_current_tab->update(dt);
		m_window_context.clear(sf::Color::Black);
		m_current_tab->draw(dt);
		m_window_context.display();
	}
}
