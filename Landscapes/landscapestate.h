//landscapestate.h
#pragma once

#include "common.h"

#include <QObject>
#include <QPinchGesture>
#include <QMouseEvent>


namespace Scene
{
	class CmlScreen;
}

class LandscapesMainScene;

class LandscapeState : public QObject
{
public:
	LandscapeState();
	~LandscapeState();

	virtual void setup(LandscapesMainScene *main_scene);

	virtual void postSetup();

	virtual void update(const Core::AppTime& app_time);

	virtual void pinchTriggered(QPinchGesture *gesture);

	virtual bool mousePressEvent(QMouseEvent *mouseEvent);

	virtual bool mouseReleaseEvent(QMouseEvent *mouseEvent);

	virtual bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta);

protected:

	LandscapesMainScene *m_main_scene;

	Scene::CmlScreen *m_screen;
};

