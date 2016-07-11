//sharing.h

#pragma once

#include "landscapescreen.h"
#include "keyboard.h"
#include "backtomainmenudialog.h"
#include "landscape.h"

namespace Scene
{
	class CmlText;
	class CmlLineEdit;
	class CmlToggle;
}

class Sharing : public LandscapeScreen
{
	Q_OBJECT

public:
	Sharing();
	~Sharing();

	virtual void setup(LandscapesMainScene *main_scene) override;

	void setSaveImagePath(Landscape landscape);

	void setPaintingIndex(Landscape landscape);

	int getPaintingIndex() const;

	QString getCurrentEmailAddress() const;

	void reset();

	bool mousePressEvent(QMouseEvent *mouse_event) override;

	bool mouseReleaseEvent(QMouseEvent *mouseEvent) override;

	bool mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta) override;

private slots:

	void closeButtonPressed(const std::string& id);

	void tumblerButtonPressed(Scene::CmlToggle *toggle);

	void gotoMainButtonPressed(const std::string& id);

	void sendButtonPressed(const std::string& id);

	void backToMainDialogClosed(bool exit_to_main);

	void keyPressed(QString text);

	void keyPressedEvents(std::vector<QKeyEvent> key_events);

	void clearButtonPressed(const std::string& id);

signals:

	void goBackToMain();

private:

	Keyboard m_keyboard;

	BackToMainMenuDialog m_back_to_main_dialog;

	Scene::CmlLineEdit *m_email_address;

	bool m_email_active;

	bool m_tumblr_active;

	void sendEmail();

	void saveTumblr();

	QString m_complete_email_string;

	QString m_complete_tumblr_string;

	QString m_save_image_path;

	int m_painting_index;

	void disableSendButton();
};

