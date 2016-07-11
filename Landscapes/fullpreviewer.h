//fullpreviewer.h
#pragma once

#include "landscapescreen.h"

#include "sharing.h"

namespace Scene
{
	class CmlContainer;
}

class FullPreviewer : public LandscapeScreen
{
	Q_OBJECT

public:
	FullPreviewer();
	~FullPreviewer();

	virtual void setup(LandscapesMainScene *main_scene) override;

	void showPreview(int painting_index);

private slots:
	void close(const std::string& id);

signals:
	void previewClosed();

private:

	std::vector<Scene::CmlContainer*> m_previews;

	Sharing m_sharing;
};

