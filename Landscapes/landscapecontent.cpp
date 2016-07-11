#include "landscapecontent.h"

#include "landscapecontentlisting.h"
#include "filehelper.h"

#include <QFileInfo>
#include <QDebug>

using namespace Platform;

LandscapeContent& LandscapeContent::get()
{
	static LandscapeContent content;
	return content;
}

bool LandscapeContent::loadCSV(QString csv_file)
{
	QString csv;

	if (!readFileAndPath(csv_file, csv))
	{
		return false;
	}

	std::vector<std::vector<QString> > items = parseCsvContents(csv);

	// Start at 1 to skip comment line
	for (int i = 0; i < items.size(); ++i)
	{
		LandscapeContentListing *listing = new LandscapeContentListing(items[i]);

#ifdef QT_DEBUG
		qDebug() << "Reading listing: " << listing->getDescription();
#endif
		m_listings.push_back(listing);
	}

	return true;
}

LandscapeContentListing* LandscapeContent::getListing(int index) const
{
	if (index < 0 || index >= m_listings.size())
	{
		return nullptr;
	}

	return m_listings[index];
}

LandscapeContentListing* LandscapeContent::getListing(QString id) const
{
	for (LandscapeContentListing *listing : m_listings)
	{
		if (listing->getId() == id)
		{
			return listing;
		}
	}

	return nullptr;
}

LandscapeContent::LandscapeContent()
{
}

bool LandscapeContent::readFileAndPath(QString file_path, QString& contents)
{
	contents = FileHelper::readFile(file_path, true);

	if (contents.isEmpty())
	{
		qDebug() << "Could not read file contents " << file_path;
		return false;
	}


	QFileInfo file_info(file_path);
	if (!file_info.exists())
	{
		qDebug() << "Could not load file " << file_path;
		return false;
	}

	return true;
}

std::vector< std::vector<QString> > LandscapeContent::parseCsvContents(QString contents)
{
	std::vector< std::vector<QString> > line_values;

	QStringList entries = contents.split('\n');
	if (entries.empty())
	{
		return line_values;
	}

	bool first = true;

	for (int i = 0; i != entries.size(); ++i)
	{
		QString entry = entries[i];

		// Skip first
		if (first)
		{
			first = false;
			continue;
		}

		for (unsigned int i = 0; i != entry.size(); ++i)
		{
			QCharRef c = entry[i];
			if (c == '^')
			{
				entry[i] = ' ';
			}
		}

		QStringList values = entry.split('|');
		std::vector<QString> temp_values;
		for (int j = 0; j != values.size(); ++j)
		{
			QString value_entry = values[j];
			temp_values.push_back(value_entry);
		}

		line_values.push_back(temp_values);
	}

	return line_values;
}
