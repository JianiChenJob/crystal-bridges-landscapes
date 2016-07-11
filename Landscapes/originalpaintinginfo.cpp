#include "originalpaintinginfo.h"

#include "filehelper.h"
#include "stringhelper.h"

#include <QFileInfo>
#include <QDebug>

using namespace Core;
using namespace Platform;

OriginalPaintingInfo& OriginalPaintingInfo::get()
{
	static OriginalPaintingInfo content;
	return content;
}

OriginalPaintingInfo::OriginalPaintingInfo()
{
}

OriginalPaintingInfo::~OriginalPaintingInfo()
{
}

bool OriginalPaintingInfo::loadCSV(QString csv_file)
{
	QString csv;

	if (!readFileAndPath(csv_file, csv))
	{
		return false;
	}

	std::vector<std::vector<QString> > items = parseCsvContents(csv);
	for (int i = 0; i < items.size(); ++i)
	{
		parseListing(items[i]);
	}

	return true;
}

bool OriginalPaintingInfo::readFileAndPath(QString file_path, QString& contents)
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

std::vector< std::vector<QString> > OriginalPaintingInfo::parseCsvContents(QString contents)
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
			QString value_entry = values[j].trimmed();
			temp_values.push_back(value_entry);
		}

		line_values.push_back(temp_values);
	}

	return line_values;
}

void OriginalPaintingInfo::parseListing(const std::vector<QString>& items)
{
	if (items.size() < FIELD_COUNT)
	{
		return;
	}

	PaintingInfo info;
	info.painting_number = StringHelper::stringToInt(
		items[PAINTING_INDEX].toStdString());
	info.title = items[TITLE];
	info.artist = items[ARTIST];
	info.location = items[LOCATION];
	info.date = items[DATE];

	m_infos.push_back(info);
}