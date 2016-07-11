//screenshottaker.h
#pragma once

#include <QObject>
#include <QScreen>

class ScreenshotTaker : public QObject
{
	Q_OBJECT

public:
	
	static ScreenshotTaker& get();

	QPixmap getScreenPainting(int paint_index);

	QPixmap getSharingScreenPainting(int paint_index);

private:
	ScreenshotTaker();
	~ScreenshotTaker();

	QPixmap getScreen(int left, int top, int width, int height);

	QScreen *m_screen;

	WId m_win_id;
};

