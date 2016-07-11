//usagetracker.cpp
//Purpose: Tracking usage of the App

//@author Jiani Chen
#include "usagetracker.h"

#include "appsettings.h"
#include "originalpaintinginfo.h"
#include "stringhelper.h"

#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

using namespace Core;
using namespace Platform;

UsageTracker& UsageTracker::get()
{
	static UsageTracker tracker;
	return tracker;
}

UsageTracker::UsageTracker()
{
	for (unsigned int i = 0; i <= 4; ++i)
	{
		m_painting_session_count.push_back(0);
	}
}

UsageTracker::~UsageTracker()
{
}

void UsageTracker::setup()
{
	AppSettings::setApplicationInfo("Ideum", "Landscapes");

	m_html_path = QStandardPaths::writableLocation(
		QStandardPaths::DocumentsLocation) + "/Landscapes_usage.html";
}

void UsageTracker::shutdown()
{
	writeUsageStats();
}

void UsageTracker::paintingSelected(int painting_index)
{
	const int total_count = 
		AppSettings::getSettingInt("Landscape" + StringHelper::intToString(painting_index));

	AppSettings::setSettingInt("Landscape" + StringHelper::intToString(painting_index), total_count + 1);

	m_painting_session_count[painting_index]++;

	writeUsageStats();
}

void UsageTracker::writeUsageStats()
{
	QFileInfo out_file_info(m_html_path);
	
	if (out_file_info.exists())
	{
		QFile::remove(out_file_info.absolutePath());
	}

	QFile out_file(m_html_path);
	if (out_file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream html(&out_file);

		html << "<!DOCTYPE html>" << "\n";

		html << "<html>" << "\n";
		html << "		<head>" << "\n";
		html << "			<meta charset = \"UTF-8\">" << "\n";
		html << "				<title>Picturing the Americas - Landscapes Usage </title>" << "\n";
		html << "		</head>" << "\n";
		html << "\n";
		html << "	<body>" << "\n";
		html << "		<h1> Picturing the Americas - Landscapes Usage </h1>" << "\n";

		float total;
		for (int i = 1; i <= 4; ++i)
		{
			total += AppSettings::getSettingInt("Landscape" + StringHelper::intToString(i));
		}

		if (total < 0.0f) { total = 1.0f; }

		for (int i = 1; i <= 4; ++i)
		{
			const int use_count = AppSettings::getSettingInt("Landscape" + StringHelper::intToString(i));
			const int session_count = m_painting_session_count[i];
			const float percent = (use_count / total) * 100.0f;
			
			QString name = OriginalPaintingInfo::get().getTitle(i).toHtmlEscaped();
			if (name.contains("Paulo")) { name = "Sao Paulo"; }
			html << "		<h2> " << 
				name << ", Uses: " << use_count 
					<< ", Session: " << session_count << ", Total Percent: " << percent 
					<< "</h2> \n";
		}

		html << "	</body>" << "\n";
		html << "</html>" << "\n";
	}

	out_file.close();
}