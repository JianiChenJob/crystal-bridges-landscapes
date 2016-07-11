//symbolismmenu.h
#pragma once

#include "landscapescreen.h"

namespace Scene
{
	class CmlScreen;
}

class PaintingItem;

class SymbolismMenu : public LandscapeScreen
{
	Q_OBJECT

public:
	SymbolismMenu();
	~SymbolismMenu();

	virtual void setup(LandscapesMainScene *main_scene) override;

	void updateSymbolism(PaintingItem *item);

private slots:

	void symbolToggleBecameOn(const std::string& id);

private:
	LandscapesMainScene *m_main_scene;

	Scene::CmlScreen *m_screen;

	PaintingItem *m_item;
};

