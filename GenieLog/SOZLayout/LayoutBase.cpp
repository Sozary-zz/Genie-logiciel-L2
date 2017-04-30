#include "LayoutBase.h"
#include <iostream>

using namespace sf;
using namespace std;

LayoutBase::LayoutBase(int w, int h, string name, Color background_color) :m_window(VideoMode(w, h), name, Style::Close), m_background_color(background_color)
{
}

void LayoutBase::run()
{
	string arg; // the method that I use for share data to the submit button pass from it
	while (m_window.isOpen())
	{
		Event event;
		arg = "";
		while (m_window.pollEvent(event))
		{
			for (auto &x : m_components)
			{
				switch (x->getComponent())
				{
				case INPUT_COMPONENT:
					if (arg.empty())
						arg += x->getString();
					else
						arg += "\n" + x->getString(); // at each moment, I get the informations of all inputs and I save them in arg
					break;
				case FINISH_BUTTON_STATE:
					m_window.close();
					throw INTERRUPT_WINDOW_EXCEPTION;
					break;
				}
				x->update(event, arg); // I finally reshare all these data to all components

			}

			if (event.type == Event::Closed)
			{
				m_window.close();

				throw INTERRUPT_WINDOW_EXCEPTION;
			}




		}
		m_window.clear(m_background_color);
		for (auto &x : m_components)
			m_window.draw(*x);

		m_window.display();
	}
}

void LayoutBase::addComponent(LayoutComponent* l)
{
	if (l->getComponent() == SUBMIT_BUTTON_COMPONENT)
		m_components.push_back(l);
	else
		m_components.insert(m_components.begin(), l);
}


LayoutBase::~LayoutBase()
{
	delete m_submit_button;
}


