//attractor.h

#pragma once

#include "landscapescreen.h"

class Attractor : public LandscapeScreen
{
	Q_OBJECT

public:
	Attractor();
	~Attractor();

	virtual void show();

	virtual void setup(LandscapesMainScene *main_scene);

private slots:

	void screenTouched(const std::string& id);

	void animationFinished(const std::string& id);

signals:

	void touched();

private:
	bool m_playing_animation;
};

