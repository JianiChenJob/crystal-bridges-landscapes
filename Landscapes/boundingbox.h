//boundingBox.h

#pragma once

#include "Internal/graphicsroundedrectitem.h"

#include <QRectF>

namespace Scene
{
	class CmlScreen;
	class CmlContainer;
	class CmlImage;
	class CmlText;
}

class PaintingItem;

class BoundingBox : public QObject, public Scene::GraphicsRoundedRectItem
{
	Q_OBJECT

public:
	BoundingBox();
	~BoundingBox();

	void setup(Scene::CmlScreen *screen);

	void updateBoundingBox(PaintingItem *item, int total_item_count);

	void updateBox(const QRectF& box);

	inline Scene::GraphicsRoundedRectItem* getRectangle();

	inline void setAxisAlignBoundingBox(bool aabb);
	inline bool getAxisAlignBoundingBox() const;

private slots:
	void deleteButtonPressed(const std::string& id);

	void confirmButtonPressed(const std::string& id);

signals:
	void deleteSelected();

	void confirmSelected();

private:

	bool m_aabb;

	Scene::CmlContainer *m_overlay_container;

	Scene::CmlImage *m_delete_button;
	Scene::CmlText *m_count_text;

	Scene::CmlImage *m_upper_left;
	Scene::CmlImage *m_upper_right;
	Scene::CmlImage *m_lower_left;
	Scene::CmlImage *m_lower_right;
	Scene::CmlImage *m_gesture_icon;
};

void BoundingBox::setAxisAlignBoundingBox(bool aabb)
{
	m_aabb = aabb;
}

bool BoundingBox::getAxisAlignBoundingBox() const
{
	return m_aabb;
}