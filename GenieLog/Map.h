#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

struct Tile {
	
};

class Map 
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	virtual sf::Vector2f getSize() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Vector2f m_size;
};

