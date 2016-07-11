//usagetracker.h
#pragma once

#include <QString>
#include "common.h"

class UsageTracker
{
public:

	static UsageTracker& get();

	void setup();

	void shutdown();

	void paintingSelected(int painting_index);

	void writeUsageStats();

private:
	UsageTracker();
	~UsageTracker();

	std::vector<int> m_painting_session_count;

	QString m_html_path;
};

