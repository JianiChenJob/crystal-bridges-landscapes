//symbolismmenu.cpp
//Purpose: Meaning menu

//@author Jiani Chen
#include "symbolismmenu.h"

#include "paintingitem.h"
#include "landscapesmainscene.h"
#include "landscapecontentlisting.h"
#include "paintingitem.h"
#include "stringhelper.h"
#include "cmlincludes.h"

using namespace Scene;
using namespace Core;

SymbolismMenu::SymbolismMenu():
	m_main_scene(nullptr),
	m_screen(nullptr)
{
}

SymbolismMenu::~SymbolismMenu()
{
}

void SymbolismMenu::setup(LandscapesMainScene *main_scene)
{
	m_main_scene = main_scene;
	m_screen = main_scene->getScreen();

	LandscapeState::setup(main_scene);

	setRootContainer("symbolismOverlay");

	connectToggleGroup(m_screen, "symbolismToggle", &SymbolismMenu::symbolToggleBecameOn);
}

//Update the meaning menu when an item is selected
void SymbolismMenu::updateSymbolism(PaintingItem *item)
{
	m_item = item;

	if (!item)
	{
		hide();
		return;
	}

	QRectF box = item->sceneBoundingRect();


	if (LandscapeContentListing *info = item->getListing())
	{
		m_screen->setText("symbolismName", QString::fromStdString(StringHelper::toUpper(info->getDescription().toStdString())));

		m_screen->setText("symbolismTextOff1", QString::fromStdString(StringHelper::toUpper(info->getMeaning1().toStdString())));
		m_screen->setText("symbolismTextOn1", QString::fromStdString(StringHelper::toUpper(info->getMeaning1().toStdString())));

		m_screen->setText("symbolismTextOff2", QString::fromStdString(StringHelper::toUpper(info->getMeaning2().toStdString())));
		m_screen->setText("symbolismTextOn2", QString::fromStdString(StringHelper::toUpper(info->getMeaning2().toStdString())));

		m_screen->setText("symbolismTextOff3", QString::fromStdString(StringHelper::toUpper(info->getMeaning3().toStdString())));
		m_screen->setText("symbolismTextOn3", QString::fromStdString(StringHelper::toUpper(info->getMeaning3().toStdString())));

			
	}

	switch (m_item->getSymbolSelected())
	{
	case 1:
		m_screen->setToggleGroupOnState("symbolismToggle", "symbolismToggle1");
		break;

	case 2:
		m_screen->setToggleGroupOnState("symbolismToggle", "symbolismToggle2");
		break;

	case 3:
		m_screen->setToggleGroupOnState("symbolismToggle", "symbolismToggle3");
		break;

	case -1:
	default:
		m_screen->setToggleGroupOnState("symbolismToggle", "symbolismToggle1");
		m_item->setSymbolSelected(1);
		break;
	}
	
	//Chaning the menu position based on the item's position
	//TODO- hard coding
	qreal x = box.left() - 289;
	qreal y = box.top() - 20;

	if (x < 0)
	{
		x = box.left() + box.width();
	}

	if (y < 0)
	{
		y = box.bottom() + 10;
		x = box.left() - 20;
	}

	if (y > 588)
	{
		x = box.left() - 20;
		y = box.top() - 289 - 70;
	}

	m_screen->getContainer("symbolismOverlay")->setPosition(vec2(x, y));
	

	show();
	
}

void SymbolismMenu::symbolToggleBecameOn(const std::string& id)
{
	if (!m_item)
	{
		return;
	}

	if (id == "symbolismToggle1")
	{
		m_item->setSymbolSelected(1);
	}
	else if (id == "symbolismToggle2")
	{
		m_item->setSymbolSelected(2);
	}
	else if (id == "symbolismToggle3")
	{
		m_item->setSymbolSelected(3);
	}
}

