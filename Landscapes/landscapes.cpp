//landscapes.cpp
//Purpose: Set up all main classes

//@author Jiani Chen
#include "landscapes.h"

#include "cmlincludes.h"
#include "usagetracker.h"

#include "landscapesmainscene.h"
#include "basicinputmanager.h"
#include "apptime.h"

static double TimoutTime = 105.0; // This is overriden in main.cml "attractorTimeoutTime"

using namespace Core;
using namespace Scene;

Landscapes::Landscapes() :
	m_input(nullptr)
{
}

Landscapes::~Landscapes()
{
}

void Landscapes::setup(LandscapesMainScene *main_scene)
{
	m_attractor.setup(main_scene);

	m_landscape_selector.setup(main_scene);

	m_landscape_composer.setup(main_scene);

	m_gallery.setup(main_scene);

	connect(&m_attractor, &Attractor::touched,
		this, &Landscapes::attractorTouched);

	connect(&m_landscape_selector, &LandscapeSelector::landscapeSelected,
		this, &Landscapes::landscapeSelected);

	connect(&m_landscape_composer, &LandscapeComposer::composingFinished,
		this, &Landscapes::landscapeComposingFinished);

	connect(&m_landscape_composer, &LandscapeComposer::goBackToMain,
		this, &Landscapes::exitToMain);

	connect(&m_gallery, &Gallery::backToComposing,
		this, &Landscapes::galleryBackToComposing);

	connect(&m_gallery, &Gallery::goBackToMain,
		this, &Landscapes::exitToMain);

	if (CmlScreen *screen = main_scene->getScreen())
	{
		m_input = screen->getInput();

		if (CmlContainer *timeout_time = 
			screen->getContainer("attractorTimeoutTime"))
		{
			double timeout = timeout_time->getX();
			if (timeout > 0.0)
			{
				TimoutTime = timeout;
			}
		}
	}
}

void Landscapes::postSetup()
{
	m_attractor.show();

	// m_landscape_selector.show();

	// m_landscape_composer.startComposing(1);

	 //m_gallery.showPainting(Landscape());
}

void Landscapes::update(const AppTime& app_time)
{
	m_landscape_composer.update(app_time);

	updateTimeout(app_time);
}

void Landscapes::updateTimeout(const AppTime& app_time)
{
	if (m_input)
	{
		static double timeout_time = 0.0;

		if (m_input->getActiveTouchPointsCount() == 0)
		{
			timeout_time += app_time.getElapsedAppTime();

			if (timeout_time >= TimoutTime)
			{
				resetApp();

				timeout_time = 0;
			}
		}
		else
		{
			timeout_time = 0;
		}
	}
}

void Landscapes::pinchTriggered(QPinchGesture *gesture)
{
	m_landscape_composer.pinchTriggered(gesture);
}

bool Landscapes::mousePressEvent(QMouseEvent *mouseEvent)
{
	if (m_landscape_composer.mousePressEvent(mouseEvent))
	{
		return true;
	}
	else if (m_gallery.mousePressEvent(mouseEvent))
	{
		return true;
	}

	return false;
}

bool Landscapes::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	if (m_landscape_composer.mouseReleaseEvent(mouseEvent))
	{
		return true;
	}
	else if (m_gallery.mouseReleaseEvent(mouseEvent))
	{
		return true;
	}
	
	return false;
}

bool Landscapes::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{
	if (m_landscape_composer.mouseMoveEvent(mouseEvent, delta))
	{
		return true;
	}
	else if (m_gallery.mouseMoveEvent(mouseEvent, delta))
	{
		return true;
	}

	return false;
}

void Landscapes::attractorTouched()
{
	m_attractor.hide();

	m_landscape_selector.show();
}

void Landscapes::landscapeSelected(int landscape)
{
	m_landscape_selector.hide();

	UsageTracker::get().paintingSelected(landscape);

	m_landscape_composer.startComposing(landscape);
}

void Landscapes::landscapeComposingFinished(Landscape landscape)
{
	m_landscape_composer.hide();

	m_gallery.showPainting(landscape);
}

void Landscapes::galleryBackToComposing()
{
	m_gallery.hide();

	m_landscape_composer.show();
}

void Landscapes::exitToMain()
{
	m_landscape_composer.reset();

	m_landscape_selector.reset();

	m_gallery.hide();

	m_landscape_selector.show();
}

void Landscapes::resetApp()
{
	if (m_attractor.isVisible())
	{
		return;
	}

	m_landscape_composer.reset();

	m_landscape_selector.reset();

	m_gallery.reset();

	m_attractor.show();
}