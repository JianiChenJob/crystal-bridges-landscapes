#include "landscapecontentlisting.h"

#include "stringhelper.h"
#include "mainapplication.h"
#include "imagehelper.h"

#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

static int MaxImageWarnings = 5;

using namespace Core;
using namespace Platform;

LandscapeContentListing::LandscapeContentListing(const std::vector<QString>& items)
{
	if (items.size() < FIELD_COUNT)
	{
#ifdef QT_DEBUG
		QString description = "";
		if (!items.empty())
		{
			description = items[DESCRIPTION];
		}

		qDebug() << "Bad listing " << 
			"Error incomplete listing for entry.";

#endif
		return;
	}

	for (int i = 0; i != FIELD_COUNT; ++i)
	{
		m_fields[i] = items[i].trimmed();
	}

	loadImages();
}

void LandscapeContentListing::loadImages()
{
	QString base_path =  MainApplication::getContentPath();

	QString image_path = m_fields[IMAGE_PATH];

	loadImage(m_image, base_path + "/LandscapesAssets/Landscape Objects/" + 
		image_path, "Image");
}

void LandscapeContentListing::loadImage(QPixmap& pixmap, QString path, QString name)
{
	bool success_loading = false;

	QFileInfo file_info(path);
	if (file_info.exists() && !file_info.isDir())
	{
		success_loading = pixmap.load(path);

		if (pixmap.isNull())
		{
			success_loading = false;
		}
	}

	if (!success_loading && MaxImageWarnings-- > 0)
	{
		qDebug() << "Error loading content image" <<
			"Could not load content image " + name + ": " + path;
	}
}