//gallery.h
#pragma once

#include "landscapescreen.h"

#include "sharing.h"
#include "landscape.h"
#include "backtomainmenudialog.h"

namespace Scene
{
	class CmlText;
	class CmlToggle;
}

class Gallery : public LandscapeScreen
{
	Q_OBJECT

public:
	Gallery();
	~Gallery();

	virtual void setup(LandscapesMainScene *main_scene);

	void showPainting(Landscape landscape);
	
	bool mousePressEvent(QMouseEvent *mouseEvent) override;

	bool mouseReleaseEvent(QMouseEvent *mouseEvent) override;

	bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta) override;

	virtual void reset() override;

private slots:

	void sharePaintingButtonPressed(const std::string& id);

	void backToPaintingButtonPressed(const std::string& id);

	void mainMenuButtonPressed(const std::string& id);

	void backToMainDialogClosed(bool exit_to_main);

	void titleOptionToggleBecameOn(const std::string& id);

	void dropDownArrowPressed(Scene::CmlToggle *toggle);

signals:

	void backToComposing();

	void goBackToMain();

private:

	std::vector<Scene::CmlContainer*> m_galleries;

	Sharing m_sharing;

	BackToMainMenuDialog m_back_to_main_dialog;

	Scene::CmlText *m_dropDownText;

	QList<QPixmap> m_pixmap_list;
	QList<QPoint> m_position_list;
};