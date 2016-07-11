//landscapeselector.h
#pragma once

#include "landscapescreen.h"
#include "fullpreviewer.h"

class LandscapeSelectionDrawer;

class LandscapeSelector : public LandscapeScreen
{
	Q_OBJECT

public:
	LandscapeSelector();
	~LandscapeSelector();

	virtual void setup(LandscapesMainScene *main_scene);

	virtual void reset() override;

	void expandLandscape(int index);

private slots:
	void landscapeTouched(int index, bool is_expanded);

	void previewLandscape(int painting_index);

	void closeDrawers();

signals:
	void landscapeSelected(int landscape);

private:

	QList<LandscapeSelectionDrawer*> m_selection_drawers;

	FullPreviewer m_full_previewer;
};