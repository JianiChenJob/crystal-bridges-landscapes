//landscapesapplication.h
#pragma once

#include "mainapplication.h"

namespace Platform
{
    class MainScene;
    class MatScene;
}

class LandscapesApplication : public Platform::MainApplication
{
public:
	LandscapesApplication();
	~LandscapesApplication();

    virtual QString getLocalPath() const override;

	virtual Platform::MainScene* createMainScene(UINT screen_width, UINT screen_height, QString window_title,
		const Scene::SceneAppOptions& options) const override;
};
