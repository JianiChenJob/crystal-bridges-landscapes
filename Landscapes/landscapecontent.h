#pragma once

#include "common.h"

#include <QString>

class LandscapeContentListing;

class LandscapeContent
{
public:
	
	static LandscapeContent& get();

	bool loadCSV(QString csv);

	LandscapeContentListing* getListing(int index) const;

	LandscapeContentListing* getListing(QString id) const;

private:
	LandscapeContent();

	bool readFileAndPath(QString file_path, QString& contents);

	std::vector< std::vector<QString> > parseCsvContents(QString contents);

	mutable std::vector<LandscapeContentListing*> m_listings;
};

