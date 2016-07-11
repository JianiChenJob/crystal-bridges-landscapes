//landscapepaintitemsscene.h
#pragma once

#include "common.h"
#include "symbolismmenu.h"

#include <QPinchGesture>
#include <QMouseEvent>
#include <QGraphicsScene>

namespace Scene
{
	class CmlContainer;
	class GraphicsAdvancedTextItem;
	class CmlScreen;
	class CmlImage;
}

namespace Core
{
	class BasicInputManager;
}

class PaintingItem;
class BoundingBox;

class LandscapePaintItemsScene : public QObject
{
	Q_OBJECT

public:
	LandscapePaintItemsScene(
		Scene::CmlScreen *screen,
		Scene::CmlContainer *root, Scene::CmlContainer *overlay_root, 
		QGraphicsScene *scene);
	~LandscapePaintItemsScene();

	void setup(LandscapesMainScene *main_scene);

	void addItem(PaintingItem *item);

	void finishComposing();

	void clear();

	void pinchTriggered(QPinchGesture *gesture);

	void mousePressEvent(QMouseEvent *mouseEvent);

	void mouseReleaseEvent(QMouseEvent *mouseEvent);

	void mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta);

private slots:

	void deletedSelected();

	void confirmSelected();

private:

	void setSelectedItem(PaintingItem* selected);

	void unselect();

	void updateBoundingBox();

	void updateItemCount();

	void configureMeaningText();

	bool onCanvasItem(float x, float y, QString cml_id);

	std::vector<PaintingItem*> itemsAt(float x, float y);

	Scene::CmlContainer *m_root;

	QGraphicsScene *m_scene;

	PaintingItem *m_selected_item;

	SymbolismMenu m_symbolism_menu;

	BoundingBox *m_bounding_box;

	Core::BasicInputManager *m_input;

	int m_item_count;

	Scene::CmlImage *m_gesture_icon;
};

