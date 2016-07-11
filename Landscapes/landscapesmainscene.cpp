//landscapesmainscene.cpp
//Purpose: Set up main scene

//@author Jiani Chen
#include "landscapesmainscene.h"

#include "cmlincludes.h"
#include "mainapplication.h"
#include "landscapecontent.h"
#include "originalpaintinginfo.h"
#include "usagetracker.h"

#include "Internal/cmltouchmovementcomponent.h"

#include <QProcess>

using namespace Platform;
using namespace Core;
using namespace Scene;

LandscapesMainScene::LandscapesMainScene(UINT screen_width, UINT screen_height, QString window_title,
	const Scene::SceneAppOptions& options) :
	MainScene(screen_width, screen_height, window_title, options)
{
}

LandscapesMainScene::~LandscapesMainScene()
{
	UsageTracker::get().shutdown();
}

void LandscapesMainScene::setupMainScreen()
{
	CmlTouchMovementComponent *movers = new CmlTouchMovementComponent(*this);
	movers->setScreen(m_main_screen);
	m_services.addService(CmlTouchMovementComponent::typeIdClass(), movers);
	m_components.push_back(movers);

	m_landscapes.setup(this);
}

void LandscapesMainScene::postSetup()
{
	LandscapeContent::get().loadCSV(MainApplication::getContentPath() + 
		"Landscapes Carry Meaning Content.csv");

	OriginalPaintingInfo::get().loadCSV(MainApplication::getContentPath() +
		"Landscapes Carry Meaning Paintings.csv");

	UsageTracker::get().setup();

	m_landscapes.postSetup();

	QProcess *process = new QProcess(this);
	QString program = "SocialMediaService.exe";

	process->start(program);
	QProcess::ProcessState state = process->state();
}

void LandscapesMainScene::update(const AppTime& app_time)
{
	MainScene::update(app_time);

	m_landscapes.update(app_time);
}

void LandscapesMainScene::scenePinchEvent(QPinchGesture *pinch)
{
	m_landscapes.pinchTriggered(pinch);
}

void LandscapesMainScene::scenePressEvent(QMouseEvent *e)
{
	m_landscapes.mousePressEvent(e);
}

void LandscapesMainScene::sceneMoveEvent(QMouseEvent *e, const vec2& delta)
{
	m_landscapes.mouseMoveEvent(e, delta);
}

void LandscapesMainScene::sceneReleaseEvent(QMouseEvent *e)
{
	m_landscapes.mouseReleaseEvent(e);
}