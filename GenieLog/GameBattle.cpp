#include "GameBattle.hpp"
#include <iostream>
#define BAR_SIZE 156

using namespace std;/// INFOS DE CE Q U IL SE PASSE
using namespace sf;

GameBattle::GameBattle(Game * game, Joueur* player, Monstre* monster, int* battle_issue) :
	m_tick(0), m_player(player), m_monster(monster), m_enemy_bar(156, 0), m_player_bar(156, 0), m_battle_issue(battle_issue)
{


	m_attack.load("data\\songs\\sounds_effect\\emerald_000D_hit.wav");
	m_attack.sample.setVolume(10);
	m_attack.running = false;

	m_final_attack.load("data\\songs\\sounds_effect\\emerald_000E_end.wav");
	m_final_attack.sample.setVolume(10);
	m_final_attack.running = false;

	m_dis = uniform_int_distribution<>(1, 100);
	random_device rd;
	m_gen = mt19937(rd());

	m_buffer = new string*[2];
	m_buffer[0] = new string[3];
	m_buffer[1] = new string[3];


	this->game = game;
	auto x = (Vector2f)this->game->window.getSize();

	m_view.setSize(x);
	m_view.setCenter(x*.5f);

	GameState::texture_manager->addElement("battle_background", "data\\dpblatle-1.png");
	GameState::texture_manager->addElement("player", "data\\ray.png");
	GameState::texture_manager->addElement("enemy", "data\\enemy.png");


	m_background.setTexture(GameState::texture_manager->getElement("battle_background"));
	m_background.setScale(x.x / m_background.getTexture()->getSize().x, x.y / m_background.getTexture()->getSize().y);

	entities[0].setTexture(GameState::texture_manager->getElement("player"));
	entities[1].setTexture(GameState::texture_manager->getElement("enemy"));

	entities[1].setPosition(503, 52);
	entities[1].setScale(194.f / GameState::texture_manager->getElement("enemy").getSize().x, 220.f / GameState::texture_manager->getElement("enemy").getSize().y);
	entities[0].setPosition(80, 220);
	entities[0].setScale(223.f / GameState::texture_manager->getElement("player").getSize().x, 231.f / GameState::texture_manager->getElement("player").getSize().y);


	m_base_battle_sound_buffer.loadFromFile("data\\songs\\009_Battle_Wild_Pok_mon_.ogg");
	m_base_battle_sound.setBuffer(m_base_battle_sound_buffer);
	m_base_battle_sound.setLoop(true);

	m_base_battle_sound.setPlayingOffset(seconds(3.f));
	m_base_battle_sound.play();
	m_base_battle_sound.setVolume(1);

	Text name_a, name_b;
	Text hp;
	name_a.setFont(GameState::font_manager->getElement("main_font"));
	name_b.setFont(GameState::font_manager->getElement("main_font"));
	hp.setFont(GameState::font_manager->getElement("main_font"));

	name_a.setColor(Color(0, 0, 0));
	name_b.setColor(Color(0, 0, 0));
	hp.setColor(Color(0, 0, 0));

	name_a.setString(player->recupNom());
	name_b.setString(monster->recupNom());

	hp.setString(to_string(player->recupVie()) + "/" + to_string(player->recupMaxVie()));

	name_b.setPosition(20, 80);
	name_a.setPosition(480, 319);

	hp.setPosition(700, 385);
	hp.setCharacterSize(22);

	m_texts.push_back(name_a);
	m_texts.push_back(name_b);
	m_texts.push_back(hp);

	m_hp_enemy[0].setPosition(153 + m_enemy_bar.x, 128);
	m_hp_enemy[0].setSize(Vector2f(m_enemy_bar.y, 3));
	m_hp_enemy[0].setFillColor(Color(148, 154, 135));

	m_hp_enemy[1].setPosition(153 + m_enemy_bar.x, 131);
	m_hp_enemy[1].setSize(Vector2f(m_enemy_bar.y, 7));
	m_hp_enemy[1].setFillColor(Color(108, 114, 101));

	m_hp_enemy[2].setPosition(153 + m_enemy_bar.x, 138);
	m_hp_enemy[2].setSize(Vector2f(m_enemy_bar.y, 3));
	m_hp_enemy[2].setFillColor(Color(148, 154, 135));

	m_hp_player[0].setPosition(616 + m_player_bar.x, 366);
	m_hp_player[0].setSize(Vector2f(m_player_bar.y, 3));
	m_hp_player[0].setFillColor(Color(148, 154, 135));

	m_hp_player[1].setPosition(616 + m_player_bar.x, 369);
	m_hp_player[1].setSize(Vector2f(m_player_bar.y, 7));
	m_hp_player[1].setFillColor(Color(108, 114, 101));

	m_hp_player[2].setPosition(616 + m_player_bar.x, 376);
	m_hp_player[2].setSize(Vector2f(m_player_bar.y, 3));
	m_hp_player[2].setFillColor(Color(148, 154, 135));

	m_actions = new EditList(GameState::font_manager->getElement("main_font"), Vector2f(136, 121), Vector2f(314, 465));

	auto a = player->recupNomCompetences();
	m_skills_board = new SkillsBoard(GameState::font_manager->getElement("main_font"), Vector2f(703, 125), Vector2f(31, 463), a);


	Competence* comp = m_monster->choisir_competence();
	m_turns.push_back(Turn{ comp->getTempsIncantation(),m_monster,0,comp });
	m_skills_board->setActive(true);

	*m_battle_issue = 0;
}

GameBattle::~GameBattle()
{
	m_base_battle_sound.stop();
}

void GameBattle::draw(const float delta_time)
{
	game->window.setView(m_view);
	game->window.draw(m_background);

	game->window.draw(entities[0]);
	game->window.draw(entities[1]);

	game->window.draw(*m_skills_board);

	for (int i = 0; i < 3; ++i)
	{
		game->window.draw(m_hp_enemy[i]);
		game->window.draw(m_hp_player[i]);
	}

	game->window.draw(*m_actions);

	for (auto&x : m_texts)
		game->window.draw(x);


}
void GameBattle::player_attack() {
	if (m_monster->recupVie() - m_turns.front().skill->getDamages() <= 0) {
		if (!m_final_attack.running)
			m_final_attack.run();
	}
	else {
		if (!m_attack.running)
			m_attack.run();
	}
	m_monster->prendreDegats(m_turns.front().skill->getDamages());
	m_enemy_bar.x -= float(m_turns.front().skill->getDamages()*BAR_SIZE) / (float)m_monster->recupMaxVie();
	m_enemy_bar.y += float(m_turns.front().skill->getDamages()*BAR_SIZE) / (float)m_monster->recupMaxVie();

	m_actions->addData(m_monster->recupNom() + ": -" + to_string(m_turns.front().skill->getDamages()) + " hp.");
	m_actions->addData("");

	if (m_enemy_bar.x < 0)
		m_enemy_bar.x = 0;

	if (m_enemy_bar.y > 156)
		m_enemy_bar.y = 156;

	updateBars(0);

	m_turns.erase(m_turns.begin());

	m_skills_board->setActive(true);
	sleep(seconds(1.f));
}

void GameBattle::monster_attack() {
	if (m_player->recupVie() - m_turns.front().skill->getDamages() <= 0) {
		if (!m_final_attack.running)
			m_final_attack.run();
	}
	else {
		if (!m_attack.running)
			m_attack.run();
	}
	

	m_player->prendreDegats(m_turns.front().skill->getDamages());
	m_player_bar.x -= float(m_turns.front().skill->getDamages()*BAR_SIZE) / (float)m_player->recupMaxVie();
	m_player_bar.y += float(m_turns.front().skill->getDamages()*BAR_SIZE) / (float)m_player->recupMaxVie();

	m_actions->addData(m_player->recupNom() + ": -" + to_string(m_turns.front().skill->getDamages()) + " hp.");
	m_actions->addData("");

	if (m_player_bar.x < 0)
		m_player_bar.x = 0;

	if (m_player_bar.y > 156)
		m_player_bar.y = 156;

	m_texts.back().setString(to_string(m_player->recupVie()) + "/" + to_string(m_player->recupMaxVie()));

	updateBars(1);

	m_turns.erase(m_turns.begin());

	auto comp = m_monster->choisir_competence();
	m_turns.push_back(Turn{ comp->getTempsIncantation(),m_monster,0,comp });
	sleep(seconds(1.f));
}
bool GameBattle::endBattle()
{
	bool changed = false;
	if (!m_monster->estVivant())
	{
		m_skills_board->setActive(false);
		*m_battle_issue = 1;
		m_actions->addData(m_monster->recupNom() + " est mort!");
		changed = true;
	}

	if (!m_player->estVivant()) {
		m_actions->addData(m_player->recupNom() + " est mort!");
		m_skills_board->setActive(false);
		*m_battle_issue = 2;

		changed = true;
	}

	if (changed)
	{
		m_base_battle_sound.stop();
		game->popState();
		return false;
	}

	return true;
}
void GameBattle::update(const float delta_time)
{

	m_final_attack.update();
	m_attack.update();

	if (!endBattle())
		return;

	sort(m_turns.begin(), m_turns.end(), [](const Turn &a, const Turn &b) {return a.tick_rest < b.tick_rest; });

	if (m_turns.front().tick_rest == 0) {
		if (m_turns.front().type == 0)
			monster_attack();
		else
		{
			m_actions->init();
			player_attack();
		}

	}

	if (!endBattle())
		return;

	if (m_turns.front().tick_rest == 0) {
		if (m_turns.front().type == 0)
			monster_attack();
		else
			player_attack();
	}
	if (!endBattle())
		return;
	if (!m_skills_board->active())
		for (auto&x : m_turns)
			x.tick_rest--;

}

void GameBattle::eventLoop()
{
	Event event;


	while (game->window.pollEvent(event))
	{


		switch (event.type)
		{
		case Event::Closed:
		{
			game->window.close();
			break;
		}

		case Event::KeyPressed:
		{
			if (event.key.code == Keyboard::Escape) {
				game->window.close();
				break;
			}

			if (event.key.code == Keyboard::Up && m_skills_board->active()) {
				if (m_skills_board->getCurrentSkillID() == 1)
					m_skills_board->changeSkill(0);
				else if (m_skills_board->getCurrentSkillID() == 3)
					m_skills_board->changeSkill(2);
			}
			else if (event.key.code == Keyboard::Down && m_skills_board->active())
			{
				if (m_skills_board->getCurrentSkillID() == 0)
					m_skills_board->changeSkill(1);
				else if (m_skills_board->getCurrentSkillID() == 2)
					m_skills_board->changeSkill(3);
			}

			else if (event.key.code == Keyboard::Left && m_skills_board->active()) {
				if (m_skills_board->getCurrentSkillID() == 2)
					m_skills_board->changeSkill(0);
				else if (m_skills_board->getCurrentSkillID() == 3)
					m_skills_board->changeSkill(1);
			}

			else if (event.key.code == Keyboard::Right && m_skills_board->active()) {
				if (m_skills_board->getCurrentSkillID() == 0)
					m_skills_board->changeSkill(2);
				else if (m_skills_board->getCurrentSkillID() == 1)
					m_skills_board->changeSkill(3);
			}
			else if (event.key.code == Keyboard::Space && m_skills_board->active()) {
				auto comp = m_player->choisir_competence(m_skills_board->getCurrentSkillID());
				m_turns.push_back(Turn{ comp->getTempsIncantation(),m_player,1,comp });
				m_skills_board->setActive(false);

			}
		}
		default: break;
		}
	}

}

void GameBattle::updateBars(int type)
{
	switch (type)
	{
	case 0:
		m_hp_enemy[0].setPosition(153 + m_enemy_bar.x, 128);
		m_hp_enemy[0].setSize(Vector2f(m_enemy_bar.y, 3));

		m_hp_enemy[1].setPosition(153 + m_enemy_bar.x, 131);
		m_hp_enemy[1].setSize(Vector2f(m_enemy_bar.y, 7));

		m_hp_enemy[2].setPosition(153 + m_enemy_bar.x, 138);
		m_hp_enemy[2].setSize(Vector2f(m_enemy_bar.y, 3));
		break;

	case 1:

		m_hp_player[0].setPosition(616 + m_player_bar.x, 366);
		m_hp_player[0].setSize(Vector2f(m_player_bar.y, 3));

		m_hp_player[1].setPosition(616 + m_player_bar.x, 369);
		m_hp_player[1].setSize(Vector2f(m_player_bar.y, 7));

		m_hp_player[2].setPosition(616 + m_player_bar.x, 376);
		m_hp_player[2].setSize(Vector2f(m_player_bar.y, 3));
	}



}
