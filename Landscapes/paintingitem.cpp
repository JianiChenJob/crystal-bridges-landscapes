//paintingitem.cpp
//Purpose: Initialize the painting item when it's first dragged out the drawer

//@author Jiani Chen
#include "paintingitem.h"

#include "landscapecontent.h"
#include "landscapecontentlisting.h"

PaintingItem::PaintingItem(QString id, double x, double y) :
	m_id(id),
	m_count_id(0),
	m_selected(false),
	m_listing(nullptr),
	m_symbol_selected(-1)
{
	m_setup_ok = initialize(x, y);
}

PaintingItem::~PaintingItem()
{
}

bool PaintingItem::initialize(double x, double y)
{
	LandscapeContentListing *listing = LandscapeContent::get().getListing(m_id);
	
	if (!listing || listing->getImage().isNull())
	{
		return false;
	}

	// New scale system
	// double scale = listing->getScale().toDouble();

	double scale = 1.0;
	const double height = listing->getImage().height();

	double constant_size = 120.0;

	if (m_id == "PeopleAnimals/2.5.png")
	{
		constant_size = 80.0; // for dog
	}

	if (height > 0.0)
	{
		scale = constant_size / height;
	}

	this->setPixmap(listing->getImage());
	
	this->setX(x);
	this->setY(y);

	this->setScale(scale);

	//this->setTransformOriginPoint(listing->getImage().width() * 0.5,
	//	listing->getImage().height() * 0.5);

	m_listing = listing;

	return true;
}