//backtomainmenudialog.h
#pragma once

#include "landscapescreen.h"

class BackToMainMenuDialog : public LandscapeScreen
{
	Q_OBJECT

public:
	BackToMainMenuDialog();
	~BackToMainMenuDialog();

	virtual void setup(LandscapesMainScene *main_scene);

signals:
	void closed(bool exit_to_main_menu);

private slots:

	void goBackButtonPressed(const std::string& id);

	void stayHereButtonPressed(const std::string& id);
};

