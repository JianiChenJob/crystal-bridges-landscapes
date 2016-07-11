#pragma once

#include "common.h"

#include <QString>

class OriginalPaintingInfo
{
public:

	struct PaintingInfo
	{
		int painting_number;
		QString title;
		QString artist;
		QString location;
		QString date;
	};

	static OriginalPaintingInfo& get();

	bool loadCSV(QString csv);

	inline QString getTitle(int painting_number) const;

	inline QString getArtist(int painting_number) const;

	inline QString getLocation(int painting_number) const;

	inline QString getDate(int painting_number) const;

private:

	inline PaintingInfo getInfo(int painting_number) const;

	static const int PAINTING_INDEX = 0; // A
	static const int TITLE = 1; // B
	static const int ARTIST = 2; // C
	static const int LOCATION = 3; // D
	static const int DATE = 4; // E

	static const int FIELD_COUNT = 5;

	OriginalPaintingInfo();
	~OriginalPaintingInfo();

	bool readFileAndPath(QString file_path, QString& contents);

	std::vector< std::vector<QString> > parseCsvContents(QString contents);

	void parseListing(const std::vector<QString>& items);

	std::vector<PaintingInfo> m_infos;
};

QString OriginalPaintingInfo::getTitle(int painting_number) const
{
	return getInfo(painting_number).title;
}

QString OriginalPaintingInfo::getArtist(int painting_number) const
{
	return getInfo(painting_number).artist;
}

QString OriginalPaintingInfo::getLocation(int painting_number) const
{
	return getInfo(painting_number).location;
}

QString OriginalPaintingInfo::getDate(int painting_number) const
{
	return getInfo(painting_number).date;
}

OriginalPaintingInfo::PaintingInfo OriginalPaintingInfo::getInfo(int painting_number) const
{
	for (unsigned int i = 0; i != m_infos.size(); ++i)
	{
		if (m_infos[i].painting_number == painting_number)
		{
			return m_infos[i];
		}
	}

	return OriginalPaintingInfo::PaintingInfo();
}