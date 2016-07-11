//attractor.cpp
//Purpose: The attract screen 

//@author Jiani Chen

#include "attractor.h"

#include "cmlincludes.h"

using namespace Scene;

Attractor::Attractor() :
	m_playing_animation(false)
{
	//m_fade = true;
	//m_fade_time = 0.25f;
}

Attractor::~Attractor()
{
}

void Attractor::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("Attractor");

	connectImageDown(m_screen, "attractorScreen", &Attractor::screenTouched);

	if (Animation *animation = m_screen->getAnimationById("attractorAnimation"))
	{
		connect(animation, &Animation::finished,
			this, &Attractor::animationFinished);
	}
}

//Show up the attract screen
void Attractor::show()
{
	if (!m_playing_animation)
	{
		m_screen->playAnimation("attractorAnimationImage", "attractorAnimation");
	}

	LandscapeScreen::show();
}

void Attractor::screenTouched(const std::string& id)
{
	emit touched();
}

void Attractor::animationFinished(const std::string& id)
{
	m_playing_animation = false;

	if (m_visible)
	{
		m_screen->playAnimation("attractorAnimationImage", "attractorAnimation");
		m_playing_animation = true;
	}
}