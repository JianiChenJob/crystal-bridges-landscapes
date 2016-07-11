//landscapeselectiondrawer.cpp
//Purpose: Landscapes selection drawer screen can be expanded and collapsed

//@author Jiani Chen
#include "landscapeselectiondrawer.h"

#include "landscapeselector.h"

#include "cmlincludes.h"

using namespace Scene;

static const float AnimationSpeed = 0.75f;

LandscapeSelectionDrawer::LandscapeSelectionDrawer() :
	m_is_expanded(false),
	m_start_position_x(0.0f),
	m_index(0),
	m_screen(nullptr)
{
}

LandscapeSelectionDrawer::~LandscapeSelectionDrawer()
{
}

void LandscapeSelectionDrawer::setup(CmlScreen *screen, int index)
{
	m_screen = screen;
	m_index = index;

	std::string index_string = QString("%1").arg(index).toStdString();

	m_drawer_container = screen->getContainer("selectionDrawer" + index_string);

	m_drawer_selection = screen->getImage("selectionDrawer" + index_string + "Selection");

	m_drawer_title = screen->getImage("selectionDrawer" + index_string + "Text");

	m_drawer_description = screen->getImage("selectionDrawer" + index_string + "Description");

	m_start_position_x = m_drawer_container->getX();

	connectImageDown(m_screen, "selectionDrawer" + index_string + "Selection",
		&LandscapeSelectionDrawer::selectionTouched);

	m_selection_button = screen->getImage("selectionDrawerButton" + index_string);

	m_expand_drawer_button = screen->getImage("expandDrawerButton" + index_string);

	m_create_landscape_button = screen->getImage("createLandscapeDrawerButton" + index_string);

	m_full_preview_button = screen->getImage("fullPreviewDrawerButton" + index_string);

	m_drawer_close_button = screen->getImage("closeDrawerButton" + index_string);

	connect(m_create_landscape_button, &CmlActor::pressedDown,
		this, &LandscapeSelectionDrawer::createLandscapeButtonPressed);

	connect(m_full_preview_button, &CmlActor::pressedDown,
		this, &LandscapeSelectionDrawer::fullPreviewButtonPressed);

	connect(m_drawer_close_button, &CmlActor::pressedDown,
		this, &LandscapeSelectionDrawer::drawerCloseButtonPressed);

	connect(m_drawer_container, &CmlActor::animationFinishedEvent,
		this, &LandscapeSelectionDrawer::animationFinished);
}

void LandscapeSelectionDrawer::reset(bool animate)
{
	if (animate)
	{
		m_drawer_container->animateToX(m_start_position_x, AnimationSpeed * 0.5f);
	}
	else
	{
		m_drawer_container->setXPosition(m_start_position_x);
	}

	m_selection_button->CmlActor::setOpacity(1.0f);
	m_expand_drawer_button->CmlActor::setOpacity(0.0f);
	m_create_landscape_button->CmlActor::setOpacity(0.0f);
	m_full_preview_button->CmlActor::setOpacity(0.0f);
	m_drawer_close_button->CmlActor::setOpacity(0.0f);
	m_drawer_title->CmlActor::setOpacity(1.0f);
	m_drawer_description->CmlActor::setOpacity(0.0f);
	m_drawer_selection->setCmlEnabled(true);
}

void LandscapeSelectionDrawer::collapse(float x)
{
	m_create_landscape_button->setCmlEnabled(false);
	m_full_preview_button->setCmlEnabled(false);
	m_drawer_close_button->setCmlEnabled(false);

	m_expand_drawer_button->animateToAlpha(1.0f, AnimationSpeed);
	m_drawer_title->animateToAlpha(0.0f, AnimationSpeed);
	m_drawer_description->animateToAlpha(0.0f, AnimationSpeed);
	m_drawer_container->animateToX(x, AnimationSpeed, QEasingCurve::InOutCubic);
	m_drawer_selection->setCmlEnabled(false);
}

void LandscapeSelectionDrawer::expand(float x)
{
	if (m_expand_drawer_button->getOpacity() > 0.0f)
	{
		m_expand_drawer_button->animateToAlpha(0.0f, AnimationSpeed);
	}

	if (m_selection_button->getOpacity() > 0.0f)
	{
		m_selection_button->animateToAlpha(0.0f, AnimationSpeed);
	}

	m_drawer_title->animateToAlpha(0.0f, AnimationSpeed);
	m_drawer_description->animateToAlpha(1.0f, AnimationSpeed);

	m_create_landscape_button->animateToAlpha(1.0f, AnimationSpeed);
	m_full_preview_button->animateToAlpha(1.0f, AnimationSpeed);
	m_drawer_close_button->animateToAlpha(1.0f, AnimationSpeed);

	m_create_landscape_button->setCmlEnabled(false);
	m_full_preview_button->setCmlEnabled(false);
	m_drawer_close_button->setCmlEnabled(false);

	m_drawer_container->animateToX(x, AnimationSpeed, QEasingCurve::InOutCubic);

	m_drawer_selection->setCmlEnabled(false);

}

void LandscapeSelectionDrawer::animationFinished(const std::string& id, const std::string& animation_id)
{
	m_create_landscape_button->setCmlEnabled(true);
	m_full_preview_button->setCmlEnabled(true);
	m_drawer_close_button->setCmlEnabled(true);


	m_drawer_selection->setCmlEnabled(true);
}

void LandscapeSelectionDrawer::selectionTouched(const std::string& id)
{
	emit touched(m_index, m_is_expanded);
}

void LandscapeSelectionDrawer::createLandscapeButtonPressed(const std::string& id)
{
	emit createLandscape(m_index);
}

void LandscapeSelectionDrawer::fullPreviewButtonPressed(const std::string& id)
{
	emit fullPreview(m_index);
}

void LandscapeSelectionDrawer::drawerCloseButtonPressed(const std::string& id)
{
	emit closeDrawers();
}