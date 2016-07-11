//landscapescreen.cpp
//Purpose: Landscape base screen

//@author Jiani Chen
#include "landscapescreen.h"

#include "cmlincludes.h"

using namespace Scene;

LandscapeScreen::LandscapeScreen() :
	m_visible(false),
	m_fade(false),
	m_fade_time(1.0f),
	m_root_container(nullptr)
{
}

LandscapeScreen::~LandscapeScreen()
{
}

void LandscapeScreen::show()
{
	if (m_fade && m_root_container)
	{
		m_screen->setVisible("finishTransparentBlock", true);

		m_root_container->animateToAlpha(1.0f, m_fade_time);

		m_root_container->setVisible(true);
		//setVisible(true);
	}
	else
	{
		setVisible(true);
	}
}

void LandscapeScreen::hide()
{
	if (m_fade)
	{
		m_screen->setVisible("finishTransparentBlock", true);

		m_root_container->animateToAlpha(0.0f, m_fade_time);
		//setVisible(false);
	}
	else
	{
		setVisible(false);
	}
}

void LandscapeScreen::reset()
{
	hide();
}

void LandscapeScreen::setVisible(bool visible)
{
	if (m_root_container)
	{
		m_root_container->setVisible(visible);
	}

	m_visible = visible;
}

void LandscapeScreen::setRootContainer(const std::string& id)
{
	if (m_screen)
	{
		if (m_root_container = m_screen->getContainer(id))
		{
			connect(m_root_container, &CmlActor::animationFinishedEvent,
				this, &LandscapeScreen::fadeFinished);
		}
	}
}

void LandscapeScreen::fadeFinished(const std::string& id, const std::string& animation_id)
{
	m_screen->setVisible("finishTransparentBlock", false);

	setVisible(!m_visible);
}