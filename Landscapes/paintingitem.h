//paintingitem.h
#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "common.h"

class LandscapeContentListing;

class PaintingItem : public QObject, public QGraphicsPixmapItem
{
public:
	PaintingItem(QString id, double x, double y);
	~PaintingItem();

	enum { Type = 8888 };
	virtual int type() const override
	{
		return Type;
	}

	inline bool isSetupOK() const;

	inline void setSceneSelected(bool selected);
	inline bool getSceneSelected() const;

	inline void setCountId(int index);
	inline int getCountId() const;

	inline void setSymbolSelected(int number);
	inline int getSymbolSelected() const;

	inline vec2 getCenter() const;

	inline QString getLocation() const;

	inline float getSize() const;

	inline LandscapeContentListing* getListing() const;

private:

	bool initialize(double x, double y);

	QString m_id;

	LandscapeContentListing *m_listing;

	bool m_setup_ok;

	int m_count_id;

	bool m_selected;

	int m_symbol_selected;
};

bool PaintingItem::isSetupOK() const
{
	return m_setup_ok;
}

void PaintingItem::setSceneSelected(bool selected)
{
	m_selected = selected;
}

bool PaintingItem::getSceneSelected() const
{
	return m_selected;
}

void PaintingItem::setCountId(int index)
{
	m_count_id = index;
}

int PaintingItem::getCountId() const
{
	return m_count_id;
}

void PaintingItem::setSymbolSelected(int number)
{
	m_symbol_selected = number;
}

int PaintingItem::getSymbolSelected() const
{
	return m_symbol_selected;
}

vec2 PaintingItem::getCenter() const
{
	QRectF box = sceneBoundingRect();

	return vec2(box.center().x(), box.center().y());
}

QString PaintingItem::getLocation() const
{
	// This is just an estimate:
	vec2 center = getCenter();

	if (center.x >= 633 && center.x <= 1267 &&
		center.y >= 360 && center.y <= 720)
	{
		return "in the center";
	}

	QString location = center.y <= 540 ? "in the upper " : "in the lower ";
	location += center.x < 960 ? "left" : "right";

	return location;
}

float PaintingItem::getSize() const
{
	QRectF box = sceneBoundingRect();

	return box.width() * box.height();
}

LandscapeContentListing* PaintingItem::getListing() const
{
	return m_listing;
}