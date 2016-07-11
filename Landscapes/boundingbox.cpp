//boundingBox.cpp
//Purpose: The bounding box around an object containing 
//delete and confirm buttons

//@author Jiani Chen

#include "boundingbox.h"

#include "paintingitem.h"
#include "landscapepaintitemsscene.h"

#include "cmlincludes.h"

#include <QPen>
#include <QDebug>

using namespace Scene;

static const QColor PenColor(255, 255, 255);
static const float PenAlpha = 1.0f;
static const float PenWidth = 2.0f;

BoundingBox::BoundingBox() :
	m_aabb(false)
{
	QColor pen_color = PenColor;
	pen_color.setAlphaF(PenAlpha);

	QPen pen;
	pen.setColor(pen_color);
	pen.setWidth(PenWidth);
	pen.setCosmetic(true);

	setPen(pen);

	QBrush brush;
	brush.setStyle(Qt::NoBrush);
	
	setBrush(brush);
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::setup(CmlScreen *screen)
{
	m_overlay_container = screen->getContainer("overlayUI");


	m_delete_button = screen->getImage("overlayDeleteButton");

	connectImageUp(screen, "overlayDeleteButton", &BoundingBox::deleteButtonPressed);

	connectImageUp(screen, "overlayConfirmButton", &BoundingBox::confirmButtonPressed);

	m_count_text = screen->getText("overlayCountText");

	m_upper_left = screen->getImage("overlayUpperLeft");
	m_upper_right = screen->getImage("overlayUpperRight");
	m_lower_left = screen->getImage("overlayLowerLeft");
	m_lower_right = screen->getImage("overlayLowerRight");
	m_gesture_icon = screen->getImage("gestureIcon");
}


//update the bounding box when the object is dragged out of the drawer
void BoundingBox::updateBoundingBox(PaintingItem *item, int total_item_count)
{
	//if the object is deleted, then the bounding is invisible
	if (!item)
	{
		setVisible(false);
		m_overlay_container->setVisible(false);
		m_count_text->setVisible(false);
		m_delete_button->setVisible(false);
		return;
	}

	//if the object is dragged out of the drawer, then the bouding box is visible
	setVisible(true);
	m_overlay_container->setVisible(true);
	m_count_text->setVisible(true);
	m_delete_button->setVisible(true);

	QString item_text = "(" + QString("%1 / 7").arg(item->getCountId()) + ")";
	m_count_text->setText(item_text);

	//set position, rotation, scale of the bounding box
	if (m_aabb)
	{
		setPos(item->pos());
		setRotation(item->rotation());
		setScale(item->scale());
		setTransformOriginPoint(item->transformOriginPoint());
		updateBox(item->boundingRect());
	}
	else
	{
		setPos(0.0, 0.0);
		updateBox(item->sceneBoundingRect());
	}
}

//Update the gesture icon
void BoundingBox::updateBox(const QRectF& box)
{
	setRect(box);

	//const float box_width = 10.0f;
	const float gesture_icon_width = 100.0f;

	//m_upper_left->setPosition(vec2(box.left() - 3 * box_width, box.top() - 3 * box_width));
	//m_upper_right->setPosition(vec2(box.right() - box_width, box.top() - 3 * box_width));
	//m_lower_left->setPosition(vec2(box.left() - 3 * box_width, box.bottom() - box_width));
	//m_lower_right->setPosition(vec2(box.right() - box_width, box.bottom() - box_width));

	m_gesture_icon->setPosition(vec2(box.center().x() - gesture_icon_width / 2, box.center().y() - gesture_icon_width / 2));
	//const float corner_width = 50.0f; 

	//const bool hide_extra_buttons = (box.width() < corner_width) ||
	//	(box.height() < corner_width);

	//m_delete_button->setVisible(!hide_extra_buttons);
	//m_count_container->setVisible(!hide_extra_buttons);

	//m_delete_button->setPosition(vec2(box.left() - 289, box.top() - 20 + 289));
	//m_count_container->setPosition(vec2(box.left(), box.bottom() - corner_width));
}

void BoundingBox::deleteButtonPressed(const std::string& id)
{
	emit deleteSelected();
}

void BoundingBox::confirmButtonPressed(const std::string& id)
{
	emit confirmSelected();
}