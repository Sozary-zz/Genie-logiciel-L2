#include "SkillsBoard.h"

using namespace std;
using namespace sf;

SkillsBoard::SkillsBoard(const Font& font, Vector2f size, Vector2f position, const vector<string>& skills_name) :
	m_skills_position({ Vector2f(33,465),Vector2f(33,536), Vector2f(450,465), Vector2f(450,536) }), m_skill_selected(0),m_active(true)
{
	m_skills_context.setSize(size);
	m_skills_context.setPosition(position);
	m_skills_context.setFillColor(Color::White);

	changeSkill(m_skill_selected);	

	int compt = 0;
	if (skills_name.size() <= 4)
		for (auto&x : skills_name) {
			Text tmp;
			tmp.setFont(font);
			tmp.setColor(Color::Black);
			tmp.setString(x);
			tmp.setCharacterSize(22);

			auto pos_ref = m_skills_position[compt++];

			tmp.setPosition(
				Vector2f(pos_ref.x + (size.x / 2.5f) / 2.f - tmp.getGlobalBounds().width / 2.f, pos_ref.y + (size.y / 2.5f) / 2.f - tmp.getGlobalBounds().height)
			);


			m_skills_name.push_back(tmp);
		}

}


SkillsBoard::~SkillsBoard()
{
	delete[] m_skill_selector;
}

void SkillsBoard::setActive(bool active)
{
	m_active = active;
	if (!active)
	{
		m_skills_context.setFillColor(Color(64, 64, 64));
		m_skill_selector[1].setFillColor(Color(64, 64, 64));
	}
	else
	{
		m_skills_context.setFillColor(Color::White);
		m_skill_selector[1].setFillColor(Color::White);
	}
}

bool SkillsBoard::active() const
{
	return m_active;
}


void SkillsBoard::changeSkill(int skill_id)
{
	m_skill_selected = skill_id;

	auto size = m_skills_context.getSize();

	m_skill_selector[0].setPosition(m_skills_position[m_skill_selected]);
	m_skill_selector[0].setSize(Vector2f(size.x / 2.5f, size.y / 2.5f));
	m_skill_selector[0].setFillColor(Color::Black);

	m_skill_selector[1].setPosition(m_skills_position[m_skill_selected].x + 2, m_skills_position[m_skill_selected].y + 2);
	m_skill_selector[1].setSize(Vector2f(size.x / 2.5f - 4, size.y / 2.5f - 4));
	m_skill_selector[1].setFillColor(Color::White);
}

int SkillsBoard::getCurrentSkillID() const
{
	return m_skill_selected;
}


void SkillsBoard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_skills_context);
	target.draw(m_skill_selector[0]);
	target.draw(m_skill_selector[1]);
	for (auto&x : m_skills_name)
		target.draw(x);
}

