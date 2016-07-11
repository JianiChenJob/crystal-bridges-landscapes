//landscapeselectiondrawer.h
#pragma once

#include <QObject>

namespace Scene
{
	class CmlScreen;
	class CmlContainer;
	class CmlImage;
}

class LandscapeSelector;

class LandscapeSelectionDrawer : public QObject
{
	Q_OBJECT

public:
	LandscapeSelectionDrawer();
	~LandscapeSelectionDrawer();

	void setup(Scene::CmlScreen *screen, int index);

	void reset(bool animate);

	void collapse(float x);

	void expand(float x);

private slots:
	void selectionTouched(const std::string& id);

	void createLandscapeButtonPressed(const std::string& id);

	void fullPreviewButtonPressed(const std::string& id);

	void drawerCloseButtonPressed(const std::string& id);

	void animationFinished(const std::string& id, const std::string& animation_id);

signals:
	void touched(int index, bool is_expanded);

	void createLandscape(int index);

	void fullPreview(int index);

	void closeDrawers();

private:
	bool m_is_expanded;

	float m_start_position_x;

	int m_index;

	Scene::CmlScreen *m_screen;

	Scene::CmlContainer *m_drawer_container;

	Scene::CmlImage *m_drawer_selection;

	Scene::CmlImage *m_selection_button;

	Scene::CmlImage *m_expand_drawer_button;

	Scene::CmlImage *m_create_landscape_button;

	Scene::CmlImage *m_full_preview_button;

	Scene::CmlImage *m_drawer_title;

	Scene::CmlImage *m_drawer_close_button;

	Scene::CmlImage *m_drawer_description;
};

