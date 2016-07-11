//backtomainmenudialog.cpp
//Purpose: Back to main dialog

//@author Jiani Chen
#include "backtomainmenudialog.h"

#include "cmlincludes.h"

using namespace Scene;

BackToMainMenuDialog::BackToMainMenuDialog()
{
	m_fade = true;
	m_fade_time = 0.25f;
}

BackToMainMenuDialog::~BackToMainMenuDialog()
{
}

void BackToMainMenuDialog::setup(LandscapesMainScene *main_scene)
{
	LandscapeScreen::setup(main_scene);

	setRootContainer("returnToMainMenu");

	connectButton(m_screen, "returnToMainMenuNo", &BackToMainMenuDialog::stayHereButtonPressed);

	connectButton(m_screen, "returnToMainMenuYes", &BackToMainMenuDialog::goBackButtonPressed);
}

void BackToMainMenuDialog::goBackButtonPressed(const std::string& id)
{
	if (!m_visible)
	{
		return;
	}

	m_screen->getImage("selectPaintingItemInstruction")->animateToAlpha(0.0f, 1.0f);
	hide();

	emit closed(true);
}

void BackToMainMenuDialog::stayHereButtonPressed(const std::string& id)
{
	if (!m_visible)
	{
		return;
	}

	hide();

	emit closed(false);
}