//fullpreviewer.cpp
//Purpose: preview screen of Landscapes

//@author Jiani Chen
#include "fullpreviewer.h"

#include "cmlincludes.h"

using namespace Scene;

FullPreviewer::FullPreviewer()
{
	m_fade = true;
	m_fade_time = 0.25f;
}

FullPreviewer::~FullPreviewer()
{
}

void FullPreviewer::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("fullPreviewer");

	for (int i = 1; i <= 4; ++i)
	{
		std::string index_string = QString("%1").arg(i).toStdString();

		CmlContainer *container = m_screen->getContainer("fullPreview" + index_string);

		m_previews.push_back(container);

		std::string close_id = "fullPreviewerClose" + index_string;

		connectImageDown(m_screen, close_id, &FullPreviewer::close);
	}
}

void FullPreviewer::showPreview(int painting_index)
{
	int index = painting_index - 1; // Painting index is 1-4
	for (unsigned int i = 0; i != m_previews.size(); ++i)
	{
		m_previews[i]->setVisible(i == index);
	}

	show();
}

void FullPreviewer::close(const std::string& id)
{
	hide();

	emit previewClosed();
}