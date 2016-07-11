//landscapedrawer.cpp
//Purpose: Landscape drawer to hold all the items

//@author Jiani Chen
#include "landscapedrawer.h"

#include "cmlincludes.h"
#include "stringhelper.h"
#include "mainapplication.h"
#include "landscapesmainscene.h"
#include "landscapecontent.h"

#include "landscapecontentlisting.h"

#include "Internal\cmltouchmover.h"
#include "Internal\cmltouchmovementcomponent.h"

#include <QFileInfo>

// TODO: Not hardcode this
static const float s_paint_items_lengths[] =
	{ -1628.0f + 750.0f, -1460.0f + 750.0f, -2586.0f + 750.0f, -1043.0f + 750.0f };


bool LandscapeDrawer::sDraggingObject = false;

using namespace Core;
using namespace Platform;
using namespace Scene;

LandscapeDrawer::LandscapeDrawer() :
	m_scrolling_left(false),
	m_scrolling_right(false),
	m_paint_item_min_x(0.0f)
{
}

LandscapeDrawer::~LandscapeDrawer()
{
}

void LandscapeDrawer::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("LandscapeDrawer");

	connectToggleGroup(m_screen, "paintingItemsToggle", &LandscapeDrawer::landscapeToggleBecameOn);

	connectImageDown(m_screen, "mainMenuButton", &LandscapeDrawer::mainMenuButtonPressed);

	connectImageDown(m_screen, "finishButton", &LandscapeDrawer::finishButtonPressed);

	m_back_to_main_dialog.setup(main_scene);

	m_movers = static_cast<CmlTouchMovementComponent*>(
		main_scene->getService(CmlTouchMovementComponent::typeIdClass()));

	connect(&m_back_to_main_dialog, &BackToMainMenuDialog::closed,
		this, &LandscapeDrawer::backToMainDialogClosed);

	for (int i = 1; i <= 4; ++i)
	{
		if (CmlContainer *container =
			m_screen->getContainer("paintItems" + StringHelper::intToString(i)))
		{
			std::vector<CmlActor*> paint_items = container->getChildren();
			for (CmlActor *paint_item : paint_items)
			{
				connect(paint_item, &CmlActor::pressedDown,
					this, &LandscapeDrawer::paintItemTouched);
			}
		}
	}


	m_left_arrow = m_screen->getButton("movePaintingItemsRightButton");
	m_right_arrow = m_screen->getButton("movePaintingItemsLeftButton");

	m_paint_items_list = m_screen->getContainer("paintItemsContainer");

	if (Animation *animation = m_screen->getAnimationById("warnMessageAnimation"))
	{
		connect(animation, &Animation::finished,
			this, &LandscapeDrawer::warnAnimationFinished);
	}
}

void LandscapeDrawer::reset()
{
	m_screen->setToggleGroupAllOff("paintingItemsToggle");
	m_screen->setVisible("selectPaintingItemImage", true);
	m_screen->setVisible("selectPaintingItemBarBkg", false);

	if (m_back_to_main_dialog.isVisible())
	{
		m_back_to_main_dialog.hide();
	}
	
	sDraggingObject = false;
}

//The drawer scrolling left and right based on which arrow is pressed
void LandscapeDrawer::update(const AppTime& app_time)
{
	if (!m_left_arrow || !m_right_arrow)
	{
		return;
	}

	m_scrolling_left = m_left_arrow->isDown();
	m_scrolling_right = m_right_arrow->isDown();

	if (m_movers->getMoverCount() > 0)
	{
		return;
	}

	static const float move_speed = 1000.0f;
	if (m_scrolling_left && m_paint_items_list->getX() > m_paint_item_min_x)
	{
		m_paint_items_list->moveX(-move_speed * app_time.getElapsedAppTime());
	}
	if (m_scrolling_right && m_paint_items_list->getX() < 0)
	{
		m_paint_items_list->moveX(move_speed * app_time.getElapsedAppTime());
	}
}

void LandscapeDrawer::landscapeToggleBecameOn(const std::string& id)
{
	m_screen->setVisible("selectPaintingItemImage", false);
	m_screen->setVisible("selectPaintingItemBarBkg", true);
	m_screen->getImage("selectPaintingItemInstruction")->animateToAlpha(1.0f, 1.0f);

	if (id == "paintingItemsToggle1")
	{
		m_screen->getContainer("paintItems1")->animateToAlpha(1.0, 0.25);
		m_screen->getContainer("paintItems2")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems3")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems4")->animateToAlpha(0.0, 0.25);
	}
	else if (id == "paintingItemsToggle2")
	{
		m_screen->getContainer("paintItems1")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems2")->animateToAlpha(1.0, 0.25);
		m_screen->getContainer("paintItems3")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems4")->animateToAlpha(0.0, 0.25);
	}
	else if (id == "paintingItemsToggle3")
	{
		m_screen->getContainer("paintItems1")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems2")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems3")->animateToAlpha(1.0, 0.25);
		m_screen->getContainer("paintItems4")->animateToAlpha(0.0, 0.25);
	}
	else if (id == "paintingItemsToggle4")
	{
		m_screen->getContainer("paintItems1")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems2")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems3")->animateToAlpha(0.0, 0.25);
		m_screen->getContainer("paintItems4")->animateToAlpha(1.0, 0.25);
	}

	m_paint_items_list->setXPosition(0.0);

	if (id == "paintingItemsToggle1") { m_paint_item_min_x = s_paint_items_lengths[0]; }
	if (id == "paintingItemsToggle2") { m_paint_item_min_x = s_paint_items_lengths[1]; }
	if (id == "paintingItemsToggle3") { m_paint_item_min_x = s_paint_items_lengths[2]; }
	if (id == "paintingItemsToggle4") { m_paint_item_min_x = s_paint_items_lengths[3]; }

	sDraggingObject = false;
}

void LandscapeDrawer::mainMenuButtonPressed(const std::string& id)
{
	m_back_to_main_dialog.show();

	sDraggingObject = true;
}

void LandscapeDrawer::finishButtonPressed(const std::string& id)
{
	CmlContainer *canvas = m_screen->getContainer("canvasRoot");
	int item_count = canvas->getItem()->childItems().size();
	if (item_count < 3)
	{
		m_screen->setVisible("finishTransparentBlock", true);

		m_screen->playAnimation("minThreshold", "warnMessageAnimation");

		return;
	}
	
	sDraggingObject = false;

	emit composingFinished();
}

void LandscapeDrawer::warnAnimationFinished(const std::string& id)
{
	m_screen->setVisible("finishTransparentBlock", false);
}

void LandscapeDrawer::backToMainDialogClosed(bool exit_to_main)
{
	if (exit_to_main)
	{
		emit goBackToMain();
	}

	sDraggingObject = false;
}

//Dragging an item out of the drawer
void LandscapeDrawer::paintItemTouched(const std::string& id)
{
	//If touch the left or right arrow button
	if (m_scrolling_left || m_scrolling_right)
	{
		return;
	}

	//Item path
	QString path = MainApplication::Instance->getContentPath() + "LandscapesAssets/Landscape Objects/" +
		QString::fromStdString(id);

	if (!QFileInfo(path).exists())
	{
		qDebug() << "Warning could not find paint item " + path;
		return;
	}

	if (!m_movers || m_movers->getMoverCount() > 0)
	{
		return;
	}

	CmlImage *image = m_screen->getImage(id);
	if (!image)
	{
		return;
	}

	std::vector<int> points = image->getActivePoints();
	if (points.empty())
	{
		return;
	}

	//Limit of items on the canvas is 6
	CmlContainer *canvas = m_screen->getContainer("canvasRoot");
	int item_count = canvas->getItem()->childItems().size();
	if (item_count > 6)
	{
		m_screen->setVisible("finishTransparentBlock", true);

		m_screen->playAnimation("maxThresholdReach", "warnMessageAnimation");

		return;
	}

	const int point = points[0];
	//Clone the touched image to the scene
	CmlActor *new_image = image->clone();

	const float x = image->scenePos().x();
	const float y = image->scenePos().y();

	new_image->setX(x);
	new_image->setY(y);
	new_image->setZValue(19.0); // From CML, want above almost everything

	CmlTouchMover *mover = new CmlTouchMover(*(m_screen->getSceneApp()), new_image, point);
	mover->setExtraInfo(QString::fromStdString(id));

	m_screen->setVisible("drawerTransparentBlock", true);

	connect(mover, &CmlTouchMover::touchReleased, this, &LandscapeDrawer::paintItemReleased);
	m_movers->addMover(mover);

	sDraggingObject = true;
}

//When the paint item is release on the canvas, create
// an item to the scene
void LandscapeDrawer::paintItemReleased(int id)
{
	sDraggingObject = false;

	CmlTouchMover *mover = m_movers->getMover(id);
	if (!mover)
	{
		return;
	}

	QString painting_item_id = mover->getExtraInfo();



	CmlActor *actor = mover->getActor();
	double x = mover->getActor()->getItem()->x();
	double y = mover->getActor()->getItem()->y();
	
	emit createLandscapePaintItem(painting_item_id, x, y);
	
	m_screen->setVisible("drawerTransparentBlock", false);
}

