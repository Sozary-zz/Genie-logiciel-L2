#include "FontManager.h"

using namespace std;
using namespace sf;

void FontManager::addElement(const string & name, const string & path)
{
	Font tmp;
	if (!tmp.loadFromFile(path)) return;

	m_list[name] = tmp;
}

const Font & FontManager::getElement(const string & name) const
{
	return m_list.at(name);
}
