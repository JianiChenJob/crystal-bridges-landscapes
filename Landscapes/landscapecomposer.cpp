//landscapecomposer.cpp
//Purpose: Landscape composer

//@author Jiani Chen
#include "landscapecomposer.h"

#include "screenshottaker.h"
#include "imagehelper.h"

#include "cmlscreen.h"


#include <QStandardPaths>
#include <QDir>

using namespace Core;
using namespace Scene;
using namespace Platform;

LandscapeComposer::LandscapeComposer()
{
	m_fade = true;
	m_fade_time = 0.25f;
}

LandscapeComposer::~LandscapeComposer()
{
}

void LandscapeComposer::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("LandscapeComposer");

	m_instructions.setup(main_scene);

	m_canvas.setup(main_scene);

	m_landscape_drawer.setup(main_scene);

	connect(&m_landscape_drawer, &LandscapeDrawer::goBackToMain,
		this, &LandscapeComposer::goBackToMain);

	connect(&m_landscape_drawer, &LandscapeDrawer::composingFinished,
		this, &LandscapeComposer::finishedComposing);

	connect(&m_landscape_drawer, &LandscapeDrawer::createLandscapePaintItem,
		&m_canvas, &LandscapeCanvas::createLandscapePaintItem);
}

void LandscapeComposer::reset()
{
	m_canvas.reset();

	m_landscape_drawer.reset();

	setVisible(false);
}

void LandscapeComposer::startComposing(int paint_index)
{
	m_landscape.setPaintingIndex(paint_index);

	show();

	m_canvas.startComposing(paint_index);

	m_instructions.showInstructions(paint_index);
}

void LandscapeComposer::finishedComposing()
{
	m_canvas.finishComposing();

	QString folder_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Landscapes";
	if (!QDir(folder_path).exists())
	{
		QDir().mkdir(folder_path);
	}

	QString save_image_path = folder_path + "/custom_painting.jpg";
	QString email_image_path = folder_path + "/email_painting.jpg";

	QPixmap pixmap = ScreenshotTaker::get().getScreenPainting(m_landscape.getPaintingIndex());

	if (!pixmap.isNull())
	{
		QFile file(save_image_path);
		file.open(QIODevice::WriteOnly);
		pixmap.save(&file, "jpg", 97);
	}

	m_landscape.setPixmap(pixmap);
	
	m_landscape.setSaveImagePath(email_image_path);

	emit composingFinished(m_landscape);
}

void LandscapeComposer::update(const AppTime& app_time)
{
	if (!m_visible)
	{
		return;
	}

	m_landscape_drawer.update(app_time);
}


void LandscapeComposer::pinchTriggered(QPinchGesture *gesture)
{
	if (!m_visible)
	{
		return;
	}

	m_canvas.pinchTriggered(gesture);
}

bool LandscapeComposer::mousePressEvent(QMouseEvent *mouseEvent)
{
	if (!m_visible)
	{
		return false;
	}

	m_canvas.mousePressEvent(mouseEvent);

	return true;
}

bool LandscapeComposer::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if (!m_visible)
	{
		return false;
	}

	m_canvas.mouseReleaseEvent(mouseEvent);

	return true;
}

bool LandscapeComposer::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{
	if (!m_visible)
	{
		return false;
	}

	m_canvas.mouseMoveEvent(mouseEvent, delta);

	return true;
}
