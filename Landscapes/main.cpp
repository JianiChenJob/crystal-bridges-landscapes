//main.cpp
//Purpose: main

//@author Jiani Chen
#include <QApplication>

#include <QDir>
#include <QSplashScreen>
#include <QSharedMemory>
#include <QMessageBox>

#include "landscapesapplication.h"
#include "scenewindow.h"

using namespace Platform;

static const char * INSTANCE_GUID = "ed6f5a7d-3d06-4042-9ba5-918fba70769e";
static const char * INSTANCE_POPUP_GUID = "779715b7-e97f-4b65-b772-7bc1e1be8d1f";
static const char * DOUBLE_WARNING = "There is another instance of Landscapes running, please exit it and start again.";

int main(int argc, char *argv[])
{
	QSharedMemory shared(INSTANCE_GUID);

	if (!shared.create(512, QSharedMemory::ReadWrite))
	{
		QSharedMemory shared_popup(INSTANCE_POPUP_GUID);

		if (!shared_popup.create(512, QSharedMemory::ReadWrite))
		{
			QMessageBox message;
			message.setText(DOUBLE_WARNING);

			message.setIcon(QMessageBox::Critical);
			message.exec();
		}

		exit(0);
	}

    QApplication a(argc, argv);

	QString splash_path_base = QDir::currentPath() + "\\..\\landscapes\\content";
	QFileInfo content_dir(splash_path_base);

	QString splash_path = content_dir.absoluteFilePath() + "\\LandscapesAssets\\1. Attract Screen\\Attract Screen_Title.png";

	QPixmap splash_pixmap(splash_path);
	QSplashScreen splash(splash_pixmap);
	splash.setWindowFlags(splash.windowFlags() | Qt::WindowStaysOnTopHint);
	if (!splash_pixmap.isNull())
	{
		splash.show();
		a.processEvents();
	}

    LandscapesApplication app;
    app.initialize();

	splash.finish(app.getMainWindow());

    return a.exec();
}
