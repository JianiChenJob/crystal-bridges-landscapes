//screenshottaker.cpp
//Purpose: Taking screen shot for selected landscape

//@author Jiani Chen
#include "screenshottaker.h"

#include <QApplication>
#include <QDesktopWidget>

ScreenshotTaker& ScreenshotTaker::get()
{
	static ScreenshotTaker taker;
	return taker;
}

ScreenshotTaker::ScreenshotTaker()
{
	m_win_id = QApplication::desktop()->winId();
	m_screen = QApplication::screens().at(0);
}

ScreenshotTaker::~ScreenshotTaker()
{
}

QPixmap ScreenshotTaker::getScreenPainting(int paint_index)
{
	switch (paint_index)
	{
	case 1:
		return getScreen(72, 50, 1766, 830);

	case 2:
		return getScreen(120, 50, 1681, 830);

	case 3:
		return getScreen(408, 50, 1104, 830);

	case 4:
		return getScreen(316, 50, 1289, 830);

	default:
		return QPixmap();
	}
}

QPixmap ScreenshotTaker::getSharingScreenPainting(int paint_index)
{
	switch (paint_index)
	{
	case 1:
		return getScreen(50, 0, 1324, 1080);//1766

	case 2:
		return getScreen(86, 0, 1306, 1080);//1681

	case 3:
		return getScreen(278, 31, 1020, 800);//1104

	case 4:
		return getScreen(271, 33, 1000, 800);//1289

	default:
		return QPixmap();
	}
}

QPixmap ScreenshotTaker::getScreen(int left, int top, int width, int height)
{
	if (!m_screen)
	{
		return QPixmap();
	}

	return m_screen->grabWindow(m_win_id,
		left, top, width, height);
}