//landscapestate.cpp
//Purpose: Landscape base state screen

//@author Jiani Chen
#include "landscapestate.h"

#include "landscapesmainscene.h"

#include "cmlincludes.h"

LandscapeState::LandscapeState() :
	m_main_scene(nullptr),
	m_screen(nullptr)
{
}

LandscapeState::~LandscapeState()
{
}

void LandscapeState::setup(LandscapesMainScene *main_scene)
{
	m_main_scene = main_scene;
	m_screen = main_scene->getScreen();
}

void LandscapeState::postSetup()
{

}

void LandscapeState::update(const Core::AppTime& app_time)
{
	
}

void LandscapeState::pinchTriggered(QPinchGesture *gesture)
{

}

bool LandscapeState::mousePressEvent(QMouseEvent *mouseEvent)
{
	return false;
}

bool LandscapeState::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	return false;
}

bool LandscapeState::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{
	return false;
}