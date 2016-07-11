//landscapescreen.h
#pragma once

#include "landscapestate.h"

namespace Scene
{
	class CmlContainer;
}

class LandscapeScreen : public LandscapeState
{
public:
	LandscapeScreen();
	~LandscapeScreen();

	virtual void show();

	virtual void hide();

	virtual void reset();

	inline bool isVisible() const;

protected:

	void setVisible(bool visible);

	void setRootContainer(const std::string& id);

private slots:

	void fadeFinished(const std::string& id, const std::string& animation_id);

protected:

	bool m_visible;

	bool m_fade;

	float m_fade_time;

private:

	Scene::CmlContainer *m_root_container;
};

bool LandscapeScreen::isVisible() const
{
	return m_visible;
}
