//keyboard.h
#pragma once

#include "landscapescreen.h"

namespace Scene
{
	class CmlContainer;
	class CmlToggle;
}

class Keyboard : public LandscapeScreen
{
	Q_OBJECT

public:
	Keyboard();
	~Keyboard();

	virtual void setup(LandscapesMainScene *main_scene) override;

	void reset();
private slots:

	void keyPressed(const std::string& id);

	void deleteKeyPressed(const std::string& id);

	void shiftStateChanged(Scene::CmlToggle *toggle);

	void specialStateChanged(Scene::CmlToggle *toggle);

signals:
	void keyPress(QString text);

	void keyPressEvents(std::vector<QKeyEvent> key_events);

	void deletePress();

private:

	Scene::CmlContainer *m_cap_keys;
	Scene::CmlContainer *m_lower_keys;
	Scene::CmlContainer *m_special_keys;

	bool m_caps_on;
	bool m_special_on;
};

