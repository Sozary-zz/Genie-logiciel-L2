#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class SkillsBoard : public sf::Drawable
{
public:
	SkillsBoard(const sf::Font& font, sf::Vector2f size, sf::Vector2f position, const std::vector<std::string>& skills_name);
	~SkillsBoard();

	void setActive(bool active);
	bool active() const;
	void changeSkill(int skill_id);
	int getCurrentSkillID() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	sf::RectangleShape m_skills_context;
	sf::RectangleShape m_skill_selector[2];

	std::vector<sf::Text> m_skills_name;
	const std::vector<sf::Vector2f> m_skills_position;

	int m_skill_selected;

	bool m_active;

};

