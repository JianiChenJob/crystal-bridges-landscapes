//landscapepaintitemsscene.cpp
//Purpose: The scene for composing the landscape.
//Dragging, pinching, scaling, rotating, pressing an object of the scene

//@author Jiani Chen
#include "landscapepaintitemsscene.h"

#include "paintingitem.h"
#include "boundingbox.h"
#include "basicinputmanager.h"

#include "landscapetextcomposer.h"
#include "landscapecontentlisting.h"
#include "landscapedrawer.h"

#include "cmlincludes.h"
#include "mathhelper.h"

#include <QApplication>

static const float MaxScale = 5.0f;
static const float MinScale = 0.7f;

using namespace Scene;

LandscapePaintItemsScene::LandscapePaintItemsScene(
	CmlScreen *screen,
	CmlContainer *root, 
	CmlContainer *overlay_root, 
	QGraphicsScene *scene) :
	m_root(root),
	m_scene(scene),
	m_selected_item(nullptr)
{
	m_bounding_box = new BoundingBox;
	m_bounding_box->setup(screen);

	connect(m_bounding_box, &BoundingBox::deleteSelected,
		this, &LandscapePaintItemsScene::deletedSelected);

	connect(m_bounding_box, &BoundingBox::confirmSelected,
		this, &LandscapePaintItemsScene::confirmSelected);

	m_bounding_box->setParentItem(overlay_root->getItem());
	m_bounding_box->setVisible(false);

	m_input = screen->getInput();
	m_gesture_icon = screen->getImage("gestureIcon");
}

LandscapePaintItemsScene::~LandscapePaintItemsScene()
{

}

void LandscapePaintItemsScene::setup(LandscapesMainScene *main_scene)
{
	m_symbolism_menu.setup(main_scene);
}

//Add a item to the scene
void LandscapePaintItemsScene::addItem(PaintingItem *item)
{
	item->setParentItem(m_root->getItem());

	updateItemCount();

	setSelectedItem(item);
}

//Finish composing
void LandscapePaintItemsScene::finishComposing()
{
	configureMeaningText();

	setSelectedItem(nullptr);
	
	m_scene->update();

	QApplication::processEvents();
}

//Clear up the scene
void LandscapePaintItemsScene::clear()
{
	unselect();

	while (m_root->getItem()->childItems().size())
	{
		QGraphicsItem *item = m_root->getItem()->childItems().takeFirst();
		item->setGraphicsEffect(nullptr);
		item->setVisible(false);

		delete item;
	}

	updateItemCount();
}

//Rotate an item
static void smartRotate(QGraphicsItem *item, double dx, Qt::Axis axis = Qt::ZAxis)
{
	item->setRotation(item->rotation() + dx);
}

//Scale an item
static void smartScale(QGraphicsItem *item, double dx)
{
	item->setScale(item->scale() * dx);
}

//Pinch an item
void LandscapePaintItemsScene::pinchTriggered(QPinchGesture *gesture)
{
	m_gesture_icon->animateToAlpha(0.0, 0.25);

	QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();

	std::vector<PaintingItem*> items = itemsAt((qreal)gesture->centerPoint().x(), 
		(qreal)gesture->centerPoint().y());

	if (items.empty())
	{
		return;
	}

	PaintingItem *item = items[0];

	if (item != m_selected_item)
	{
		return;
	}

	if (item) 
	{
		if (changeFlags & QPinchGesture::ScaleFactorChanged) 
		{
			if (LandscapeContentListing *info = item->getListing())
			{
				float scale_factor = gesture->scaleFactor();
				float diff = scale_factor - 1.0f;
				diff *= 0.25f;
				scale_factor = 1.0f + diff;

				double original_scale = info->getScale().toDouble();
				double item_scale = item->scale() / original_scale;
				if ((item_scale <= MaxScale && gesture->scaleFactor() > 1.0) ||
					(item_scale >= MinScale && gesture->scaleFactor() < 1.0))
				{
					smartScale(item, scale_factor);
				}

				updateBoundingBox();
			}
		}
		if (changeFlags & QPinchGesture::RotationAngleChanged) 
		{
			qreal angledx = gesture->rotationAngle() - gesture->lastRotationAngle();
			smartRotate(item, angledx);

			updateBoundingBox();
		}
	}
}

//Press an item
void LandscapePaintItemsScene::mousePressEvent(QMouseEvent *mouseEvent)
{
	bool hit_symbolism_menu = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"on") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"off") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"paintingItemsToggle3");
	if (hit_symbolism_menu)
	{
		return;
	}

	bool hit_delete_button = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"overlayDeleteButton");
	if (hit_delete_button)
	{
		return;
	}

	bool hit_finish_button = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"finishButton");
	if (hit_finish_button)
	{
		return;
	}

	bool hit_main_menu_button = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"mainMenuButton");
	if (hit_main_menu_button)
	{
		return;
	}

	unselect();

	std::vector<PaintingItem*> items = 
		itemsAt(mouseEvent->screenPos().x(), mouseEvent->screenPos().y());
	if (items.empty())
	{
		return;
	}

	setSelectedItem(items[0]);
}

//Update the meaning of an item when mouse released
void LandscapePaintItemsScene::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	bool hit_canvas = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground1") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground2") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground3") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground4");
	if (!hit_canvas)
	{
		return;
	}

	bool hit_symbolism_menu = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismMenu") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"overlayDeleteButton") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle1") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle2") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle3");
	if (hit_symbolism_menu)
	{
		return;
	}

	if (m_selected_item)
	{
		m_symbolism_menu.updateSymbolism(m_selected_item);
	}
}

//Moving an item
void LandscapePaintItemsScene::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{

	bool hit_canvas = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground1") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground2") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground3") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"canvasBackground4");
	if (!hit_canvas)
	{
		return;
	}

	bool hit_symbolism_menu = onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismMenu") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"overlayDeleteButton") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle1") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle2") || onCanvasItem(mouseEvent->screenPos().x(), mouseEvent->screenPos().y(),
		"symbolismToggle3");
	if (hit_symbolism_menu)
	{
		return;
	}

	if (LandscapeDrawer::sDraggingObject)
	{
		return;
	}

	if (m_selected_item)
	{
		static const float MAX_MOVE = 50;
		delta.x = glm::max(-MAX_MOVE, delta.x);
		delta.x = glm::min(MAX_MOVE, delta.x);
		delta.y = glm::max(-MAX_MOVE, delta.y);
		delta.y = glm::min(MAX_MOVE, delta.y);

		const float new_bb_x = m_bounding_box->x() + delta.x;
		const float new_bb_y = m_bounding_box->y() + delta.y;

		// TODO: Update bounding box check
		// if ((new_bb_x > (150 - m_bounding_box->rect().width())) &&
		//	(new_bb_y > (150 - m_bounding_box->rect().height())) &&
		// 	(new_bb_x < 900) && (new_bb_y < 650))
		{
			m_selected_item->moveBy(delta.x, delta.y);
			updateBoundingBox();
		}

		m_symbolism_menu.hide();
		m_gesture_icon->animateToAlpha(0.0, 0.25);
	}
}

//Delete an item of the scene
void LandscapePaintItemsScene::deletedSelected()
{
	if (m_selected_item)
	{
		m_scene->removeItem(m_selected_item);
		unselect();
	}

	updateItemCount();
}

//Confirm an item
void LandscapePaintItemsScene::confirmSelected()
{
	if (m_selected_item)
	{
		unselect();
	}
}

//Set selected item default meaning
void LandscapePaintItemsScene::setSelectedItem(PaintingItem* selected)
{
	if (!selected)
	{
		unselect();
		return;
	}

	if (LandscapeDrawer::sDraggingObject)
	{
		return;
	}

	if (m_selected_item)
	{
		m_selected_item->setSceneSelected(false);
	}

	m_selected_item = selected;

	m_selected_item->setSceneSelected(true);

	updateBoundingBox();

	if (m_input)
	{
		if (m_input->getActiveTouchPointsCount() > 1)
		{
			m_symbolism_menu.updateSymbolism(nullptr);
		}
		else
		{
			m_symbolism_menu.updateSymbolism(selected);
		}
	}
	else
	{
		m_symbolism_menu.updateSymbolism(selected);
	}
}

//Unselect an item
void LandscapePaintItemsScene::unselect()
{
	if (m_selected_item)
	{
		m_selected_item->setSceneSelected(false);
	}

	m_selected_item = nullptr;

	updateBoundingBox();
}

//Update bounding box
void LandscapePaintItemsScene::updateBoundingBox()
{
	m_bounding_box->updateBoundingBox(m_selected_item, m_item_count);

	if (!m_selected_item)
	{
		m_symbolism_menu.hide();
	}
}

//Update how many items are in the scene
void LandscapePaintItemsScene::updateItemCount()
{
	m_item_count = m_root->getItem()->childItems().size();

	for (int i = 0; i != m_item_count; ++i)
	{
		QGraphicsItem *item = m_root->getItem()->childItems().at(i);
		if (item)
		{
			if (PaintingItem *painting_item = static_cast<PaintingItem*>(item))
			{
				painting_item->setCountId(i + 1); // Id count not zero based index
			}
		}
	}
}

std::vector<PaintingItem*> itemsToPaintItems(QList<QGraphicsItem*> graphics_items)
{
	std::vector<PaintingItem*> items;
	for (QGraphicsItem *graphics_item : graphics_items)
	{
		if (graphics_item->type() == PaintingItem::Type)
		{
			PaintingItem *item = static_cast<PaintingItem*>(graphics_item);
			if (item)
			{
				items.push_back(item);
			}
		}
	}

	return items;
}

//Configure the meaning text for generating the caption of the gallery
void LandscapePaintItemsScene::configureMeaningText()
{
	std::vector<PaintingItem*> items;

	int item_count = m_root->getItem()->childItems().size();

	for (int i = 0; i != item_count; ++i)
	{
		QGraphicsItem *item = m_root->getItem()->childItems().at(i);
		if (item)
		{
			if (PaintingItem *painting_item = static_cast<PaintingItem*>(item))
			{
				items.push_back(painting_item);
			}
		}
	}

	PaintingItem *largest = nullptr, 
		*second_largest = nullptr, *third_largest = nullptr;

	for (PaintingItem *item : items)
	{
		if (largest == nullptr || item->getSize() > largest->getSize())
		{
			largest = item;
		}
	}

	for (PaintingItem *item : items)
	{
		if (second_largest == nullptr || item->getSize() > second_largest->getSize())
		{
			if (item != largest)
			{
				second_largest = item;
			}
		}
	}

	for (PaintingItem *item : items)
	{
		if (third_largest == nullptr || item->getSize() > third_largest->getSize())
		{
			if (item != largest && item != second_largest)
			{
				third_largest = item;
			}
		}
	}

	LandscapeTextComposer::get().setLargestContent(largest);
	LandscapeTextComposer::get().setSecondLargestContent(second_largest);
	LandscapeTextComposer::get().setThirdLargestContent(third_largest);
}

//If the item is on canvas
bool LandscapePaintItemsScene::onCanvasItem(float x, float y, QString cml_id)
{
	vec2 position = vec2(x, y);

	QList<QGraphicsItem *> graphics_items = m_scene->items(
		QPointF(position.x, position.y), Qt::IntersectsItemBoundingRect);

	for (int i = 0; i != graphics_items.size(); ++i)
	{
		QGraphicsItem *item = graphics_items[i];

		QString cml_d_id = item->data(CmlActor::CML_ID_KEY).toString();
		if (cml_d_id.contains(cml_id))
		{
			return true;
		}
	}
	
	return false;
}

//Item's position
std::vector<PaintingItem*> LandscapePaintItemsScene::itemsAt(float x, float y)
{
	vec2 position = vec2(x, y);

	QList<QGraphicsItem *> graphics_items = m_scene->items(
		QPointF(position.x, position.y), Qt::IntersectsItemShape);

	std::vector<PaintingItem*> items = itemsToPaintItems(graphics_items);

	items = itemsToPaintItems(graphics_items);

	if (items.empty())
	{
		// Second pass bounding box
		graphics_items = m_scene->items(QPointF(position.x, position.y), Qt::IntersectsItemBoundingRect);

		items = itemsToPaintItems(graphics_items);
	}

	return items;
}
