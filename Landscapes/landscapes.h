//landscapes.h
#pragma once

#include "landscapestate.h"

#include "attractor.h"
#include "landscapeselector.h"
#include "landscapecomposer.h"
#include "gallery.h"

#include "landscape.h"
#include "common.h"

class Landscapes : public LandscapeState
{
	Q_OBJECT

public:
	Landscapes();
	~Landscapes();

	virtual void setup(LandscapesMainScene *main_scene);

	virtual void postSetup();
	
	virtual void update(const Core::AppTime& app_time) override;

	void updateTimeout(const Core::AppTime& app_time);

	virtual void pinchTriggered(QPinchGesture *gesture) override;

	virtual bool mousePressEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseReleaseEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta) override;

private slots:

	void attractorTouched();

	void landscapeSelected(int landscape);

	void landscapeComposingFinished(Landscape landscape);

	void galleryBackToComposing();

	void exitToMain();

	void resetApp();

private:

	Attractor m_attractor;

	LandscapeSelector m_landscape_selector;

	LandscapeComposer m_landscape_composer;

	Gallery m_gallery;

	Core::BasicInputManager *m_input;
};

