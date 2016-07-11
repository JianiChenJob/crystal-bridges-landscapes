//instructionsscreen.h
#pragma once

#include "landscapescreen.h"

namespace Scene
{
	class CmlImage;
}

class InstructionsScreen : public LandscapeScreen
{
	Q_OBJECT

public:
	InstructionsScreen();
	~InstructionsScreen();

	virtual void setup(LandscapesMainScene *main_scene);

	void showInstructions(int painting_index);

private slots:
	
	void instructionsTouched(const std::string& id);

private:

	std::vector<Scene::CmlImage*> m_images;
};

