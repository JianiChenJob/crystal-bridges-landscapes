//landscapesapplication.cpp
//Purpose: Set up application and create main scene

//@author Jiani Chen
#include "landscapesapplication.h"

#include "matscene.h"
#include "mainscene.h"
#include "landscapesmainscene.h"

using namespace Platform;

LandscapesApplication::LandscapesApplication()
{

}

LandscapesApplication::~LandscapesApplication()
{

}

QString LandscapesApplication::getLocalPath() const
{
    return "../../landscapes/content/";
}

MainScene* LandscapesApplication::createMainScene(UINT screen_width, UINT screen_height, QString window_title,
	const Scene::SceneAppOptions& options) const
{
	return new LandscapesMainScene(screen_width, screen_height, window_title, options);
}