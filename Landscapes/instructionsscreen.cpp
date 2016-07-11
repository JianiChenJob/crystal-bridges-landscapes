//instructionsscreen.cpp
//Purpose: Instruction screen to show users how to interact with the scene

//@author Jiani Chen
#include "instructionsscreen.h"

#include "cmlincludes.h"

using namespace Scene;

InstructionsScreen::InstructionsScreen()
{
	m_fade = true;
	m_fade_time = 0.5f;
}

InstructionsScreen::~InstructionsScreen()
{
}

void InstructionsScreen::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("Instructions");

	for (int i = 1; i <= 4; ++i)
	{
		std::string image_id = QString("instructionsBackground%1").arg(i).toStdString();

		connectImageDown(m_screen, image_id, &InstructionsScreen::instructionsTouched);

		CmlImage *image = m_screen->getImage(image_id);
		m_images.push_back(image);
	}
}

void InstructionsScreen::showInstructions(int painting_index)
{
	const int index = painting_index - 1;
	for (int i = 0; i != m_images.size(); ++i)
	{
		m_images[i]->setVisible(i == index);
	}

	show();
}

void InstructionsScreen::instructionsTouched(const std::string& id)
{
	hide();

}