//landscapecanvas.h
#pragma once

#include "landscapescreen.h"
#include "landscapepaintitemsscene.h"

namespace Scene
{
	class CmlImage;
}

class LandscapeCanvas : public LandscapeScreen
{
	Q_OBJECT

public:
	LandscapeCanvas();
	~LandscapeCanvas();

	virtual void setup(LandscapesMainScene *main_scene) override;

	virtual void reset() override;

	void startComposing(int paint_index);

	void finishComposing();

	virtual void pinchTriggered(QPinchGesture *gesture) override;

	virtual bool mousePressEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseReleaseEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta) override;

public slots:

	void createLandscapePaintItem(QString painting_item_id, double x, double y);

private:

	std::vector<Scene::CmlImage*> m_background_images;

	LandscapePaintItemsScene *m_landscape_scene;

	int m_paint_index;
};

