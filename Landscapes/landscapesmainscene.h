//landscapesmainscene.h
#pragma once

#include "mainscene.h"
#include "landscapes.h"

namespace Scene
{
	class CmlTimeline;
	class CmlText;
	class CmlImage;
	class CmlLayer;
}

class LandscapesMainScene : public Platform::MainScene
{
public:
	LandscapesMainScene(UINT screen_width, UINT screen_height, QString window_title, const Scene::SceneAppOptions& options);

	virtual ~LandscapesMainScene();

	virtual void setupMainScreen() override;

	virtual void postSetup() override;

	virtual void update(const Core::AppTime& app_time) override;

	virtual void scenePinchEvent(QPinchGesture *pinch) override;
	virtual void scenePressEvent(QMouseEvent *e) override;
	virtual void sceneMoveEvent(QMouseEvent *e, const vec2& delta) override;
	virtual void sceneReleaseEvent(QMouseEvent *e) override;

private slots:

private:
	Landscapes m_landscapes;
};
