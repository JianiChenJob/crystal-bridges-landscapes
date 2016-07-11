//landscapecomposer.h
#pragma once

#include "landscapescreen.h"
#include "landscape.h"

#include "instructionsscreen.h"
#include "landscapecanvas.h"
#include "landscapedrawer.h"

#include <QPixmap>

class LandscapeComposer : public LandscapeScreen
{
	Q_OBJECT

public:
	LandscapeComposer();
	~LandscapeComposer();

	virtual void setup(LandscapesMainScene *main_scene);

	virtual void reset() override;

	void startComposing(int paint_index);

	virtual void update(const Core::AppTime& app_time) override;

	virtual void pinchTriggered(QPinchGesture *gesture) override;

	virtual bool mousePressEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseReleaseEvent(QMouseEvent *mouseEvent) override;

	virtual bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta) override;

	inline QString getSaveImagePath() const;

private slots:

	void finishedComposing();

signals :

	void goBackToMain();
	
	void composingFinished(Landscape landscape);

private:

	InstructionsScreen m_instructions;

	LandscapeCanvas m_canvas;

	LandscapeDrawer m_landscape_drawer;

	Landscape m_landscape;
};

