#include "TextureManager.h"

using namespace std;
using namespace sf;

void TextureManager::addElement(const string & name, const string & path)
{
	Texture tmp;
	if (!tmp.loadFromFile(path)) return;

	m_list[name] = tmp;
}

const Texture & TextureManager::getElement(const string & name) const
{
	return m_list.at(name);
}
