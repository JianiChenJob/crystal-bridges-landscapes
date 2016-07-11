//landscapedrawer.h
#pragma once

#include "landscapescreen.h"

#include "backtomainmenudialog.h"

namespace Scene
{
	class CmlContainer;
	class CmlButton;
	class CmlTouchMovementComponent;
}

class LandscapeDrawer : public LandscapeScreen
{
	Q_OBJECT

public:
	LandscapeDrawer();
	~LandscapeDrawer();

	virtual void setup(LandscapesMainScene *main_scene) override;

	virtual void reset() override;

	virtual void update(const Core::AppTime& app_time) override;

	static bool sDraggingObject;

private slots:
	
	void landscapeToggleBecameOn(const std::string& id);

	void mainMenuButtonPressed(const std::string& id);

	void finishButtonPressed(const std::string& id);

	void backToMainDialogClosed(bool exit_to_main);

	void paintItemTouched(const std::string& id);

	void paintItemReleased(int id);

	void warnAnimationFinished(const std::string& id);

signals:

	void goBackToMain();

	void composingFinished();

	void createLandscapePaintItem(QString painting_item_id, double x, double y);

private:

	BackToMainMenuDialog m_back_to_main_dialog;

	Scene::CmlTouchMovementComponent *m_movers;

	bool m_scrolling_left, m_scrolling_right;

	Scene::CmlButton *m_left_arrow, *m_right_arrow;

	Scene::CmlContainer *m_paint_items_list;
	double m_paint_item_min_x;
};

