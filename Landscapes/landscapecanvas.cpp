//landscapecanvas.cpp
//Purpose: The canvas for composing the landscape 

//@author Jiani Chen
#include "landscapecanvas.h"

#include "cmlincludes.h"
#include "sceneapp.h"
#include "paintingitem.h"

#include <QDebug>

using namespace Scene;

LandscapeCanvas::LandscapeCanvas() :
	m_landscape_scene(nullptr)
{
}

LandscapeCanvas::~LandscapeCanvas()
{
	DeleteAObject(m_landscape_scene);
}

void LandscapeCanvas::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	for (int i = 1; i <= 4; ++i)
	{
		std::string index_string = QString("%1").arg(i).toStdString();

		CmlImage *background_image = m_screen->getImage("canvasBackground" + index_string);

		m_background_images.push_back(background_image);
	}

	m_landscape_scene = new LandscapePaintItemsScene(
		m_screen,
		m_screen->getContainer("canvasRoot"),
		m_screen->getContainer("canvasOverlayRoot"),
		m_screen->getSceneApp()->getScene());

	m_landscape_scene->setup(main_scene);
}

//Clear up the canvas
void LandscapeCanvas::reset()
{
	if (m_landscape_scene)
	{
		m_screen->getImage("gestureIcon")->CmlActor::setOpacity(1.0);

		m_screen->getImage("selectPaintingItemInstruction")->CmlActor::setOpacity(0.0);

		m_landscape_scene->clear();
	}
}

//Add a background image to the canvas
void LandscapeCanvas::startComposing(int paint_index)
{
	m_paint_index = paint_index - 1; // Painting index is 1-4
	for (unsigned int i = 0; i != m_background_images.size(); ++i)
	{
		m_background_images[i]->setVisible(i == m_paint_index);
	}
}

void LandscapeCanvas::finishComposing()
{
	m_landscape_scene->finishComposing();
}

void LandscapeCanvas::pinchTriggered(QPinchGesture *gesture)
{
	m_landscape_scene->pinchTriggered(gesture);
}

bool LandscapeCanvas::mousePressEvent(QMouseEvent *mouseEvent)
{
	m_landscape_scene->mousePressEvent(mouseEvent);

	return true;
}

bool LandscapeCanvas::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	m_landscape_scene->mouseReleaseEvent(mouseEvent);

	return true;
}

bool LandscapeCanvas::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{
	m_landscape_scene->mouseMoveEvent(mouseEvent, delta);

	return true;
}

//Create an object on the canvas when the object is dragged out of the drawer
void LandscapeCanvas::createLandscapePaintItem(QString painting_item_id, double x, double y)
{
	qDebug() << "Create item " << painting_item_id << " " << x << " " << y;

	//Limit dragging space for each painting
	if (m_paint_index == 0)
	{
		if (x > 1838 || y > 880)
		{
			return;
		}
	}
	else if (m_paint_index == 1)
	{
		if (x > 1800.5 || y > 880)
		{
			return;
		}
	}
	else if (m_paint_index == 2)
	{
		if (x > 1512 || y > 880)
		{
			return;
		}
	}
	else if (m_paint_index == 3)
	{
		if (x > 1604.5 || y > 880)
		{
			return;
		}
	}

	PaintingItem *item = new PaintingItem(painting_item_id, x, y);


	if (!item->isSetupOK())
	{
		qDebug() << "Error setting up item " << painting_item_id;
		return;
	}

	m_landscape_scene->addItem(item);
}