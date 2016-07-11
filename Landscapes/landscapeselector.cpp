//landscapeselector.cpp
//Purpose: Landscapes selectior screen

//@author Jiani Chen
#include "landscapeselector.h"

#include "landscapeselectiondrawer.h"

#include "cmlincludes.h"

#include <QDebug>

static const int DrawerCount = 4;

LandscapeSelector::LandscapeSelector()
{
	m_fade = true;
	m_fade_time = 0.25f;
}

LandscapeSelector::~LandscapeSelector()
{
}

void LandscapeSelector::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("LandscapeSelector");

	for (int i = 0; i != DrawerCount; ++i)
	{
		LandscapeSelectionDrawer *drawer = new LandscapeSelectionDrawer;
		drawer->setup(m_screen, i + 1); // Indexs for paintings are 1-4

		connect(drawer, &LandscapeSelectionDrawer::touched,
			this, &LandscapeSelector::landscapeTouched);

		connect(drawer, &LandscapeSelectionDrawer::fullPreview,
			this, &LandscapeSelector::previewLandscape);

		connect(drawer, &LandscapeSelectionDrawer::createLandscape,
			this, &LandscapeSelector::landscapeSelected);

		connect(drawer, &LandscapeSelectionDrawer::closeDrawers,
			this, &LandscapeSelector::closeDrawers);

		m_selection_drawers.push_back(drawer);
	}

	m_full_previewer.setup(main_scene);
}

void LandscapeSelector::reset()
{
	for (LandscapeSelectionDrawer *drawer : m_selection_drawers)
	{
		drawer->reset(false);
	}

	if (isVisible())
	{
		setVisible(false);
	}

	if (m_full_previewer.isVisible())
	{
		m_full_previewer.hide();
	}
	
}

void LandscapeSelector::closeDrawers()
{
	for (LandscapeSelectionDrawer *drawer : m_selection_drawers)
	{
		drawer->reset(true);
	}
}

void LandscapeSelector::expandLandscape(int index)
{
	if (index <= 0 || index > DrawerCount || m_selection_drawers.empty())
	{
		return;
	}

	switch (index)
	{
	case 1:
	{
		m_selection_drawers[0]->expand(0.0f);
		m_selection_drawers[1]->collapse(1515.0f);
		m_selection_drawers[2]->collapse(1650.0f);
		m_selection_drawers[3]->collapse(1785.0f);
	}
	break;

	case 2:
	{
		m_selection_drawers[0]->collapse(0.0f);
		m_selection_drawers[1]->expand(135.0f);
		m_selection_drawers[2]->collapse(1650.0f);
		m_selection_drawers[3]->collapse(1785.0f);
	}
	break;

	case 3:
	{
		m_selection_drawers[0]->collapse(0.0f);
		m_selection_drawers[1]->collapse(135.0f);
		m_selection_drawers[2]->expand(270.0f);
		m_selection_drawers[3]->collapse(1785.0f);
	}
	break;

	case 4:
	{
		m_selection_drawers[0]->collapse(0.0f);
		m_selection_drawers[1]->collapse(135.0f);
		m_selection_drawers[2]->collapse(270.0f);
		m_selection_drawers[3]->expand(405.0f);
	}
	break;
	}
}

void LandscapeSelector::landscapeTouched(int index, bool is_expanded)
{
	qDebug() << "Landscape touched";

	expandLandscape(index);
}

void LandscapeSelector::previewLandscape(int painting_index)
{
	m_full_previewer.showPreview(painting_index);
}