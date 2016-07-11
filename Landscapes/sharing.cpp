//sharing.cpp
//Purpose: The sharing screen controls the email and tumblr sent.

//@author Jiani Chen

#include "sharing.h"

#include "cmlincludes.h"
#include "landscape.h"
#include "landscapetextcomposer.h"

#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>


using namespace Scene;

Sharing::Sharing() :
	m_email_active(false),
	m_tumblr_active(true),
	m_complete_email_string(""),
	m_complete_tumblr_string("")
{
	m_fade = true;
	m_fade_time = 0.25f;
}

Sharing::~Sharing()
{
}

void Sharing::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("Sharing");

	connectImageUp(m_screen, "shareCloseButton", &Sharing::closeButtonPressed);

	connectToggle(m_screen, "tumblrToggle", &Sharing::tumblerButtonPressed);

	connectImageUp(m_screen, "shareMainMenuButton", &Sharing::gotoMainButtonPressed);

	connectImageUp(m_screen, "shareTextClear", &Sharing::clearButtonPressed);

	connectImageUp(m_screen, "shareSendButton", &Sharing::sendButtonPressed);

	m_keyboard.setup(main_scene);

	m_back_to_main_dialog.setup(main_scene);

	connect(&m_back_to_main_dialog, &BackToMainMenuDialog::closed,
		this, &Sharing::backToMainDialogClosed);

	m_email_address = m_screen->getLineEdit("shareText");

	m_email_address->setFocus();

	connect(&m_keyboard, &Keyboard::keyPress,
		this, &Sharing::keyPressed);

	connect(&m_keyboard, &Keyboard::keyPressEvents,
		this, &Sharing::keyPressedEvents);
}

void Sharing::reset()
{
	if (isVisible())
	{
		setVisible(false);
	}
	
	if (m_email_address)
	{
		m_email_address->setTextLine("");
	}

	m_keyboard.reset();

	if (!m_tumblr_active)
	{
		m_screen->setToggle("tumblrToggle", "on");

		tumblerButtonPressed(m_screen->getToggle("tumblrToggle"));
	}
}

bool Sharing::mousePressEvent(QMouseEvent *mouse_event)
{
	if (!m_visible)
	{
		return false;
	}

	m_email_address->mousePress(mouse_event);

	return true;
}

bool Sharing::mouseReleaseEvent(QMouseEvent *mouse_event)
{
	if (!m_visible)
	{
		return false;
	}

	m_email_address->mouseRelease(mouse_event);

	return true;
}

bool Sharing::mouseMoveEvent(QMouseEvent *mouse_event, vec2 delta)
{
	if (!m_visible)
	{
		return false;
	}

	m_email_address->mouseMove(mouse_event);

	return true;
}

void Sharing::closeButtonPressed(const std::string& id)
{
	if (m_email_address)
	{
		m_email_address->setTextLine("");
	}

	hide();
}

void Sharing::tumblerButtonPressed(CmlToggle *toggle)
{
	if (toggle->isOn())
	{
		m_tumblr_active = true;
	}
	else
	{
		m_tumblr_active = false;
		
	}

	disableSendButton();
}

void Sharing::disableSendButton()
{
	if (m_email_address->getTextLine() == "" && !m_tumblr_active)
	{
		m_screen->getImage("shareSendButton")->CmlActor::setOpacity(0.5);
		m_screen->setVisible("shareSendButtonBlock", true);
	}
	else
	{
		m_screen->getImage("shareSendButton")->CmlActor::setOpacity(1.0);
		m_screen->setVisible("shareSendButtonBlock", false);
	}
}

void Sharing::gotoMainButtonPressed(const std::string& id)
{
	m_back_to_main_dialog.show();
}

void Sharing::clearButtonPressed(const std::string& id)
{
	if (m_email_address)
	{
		m_email_address->setTextLine("");
	}

	disableSendButton();
}

void Sharing::sendButtonPressed(const std::string& id)
{
	m_screen->playAnimation("shareSuccess", "shareSuccessAnimation");
	backToMainDialogClosed(true);
	m_screen->getImage("selectPaintingItemInstruction")->animateToAlpha(0.0f, 1.0f);

	QString url = "";

	sendEmail();
	saveTumblr();

	if (m_email_active && m_tumblr_active)
	{
		url = m_complete_email_string + "&" + m_complete_tumblr_string;
	}
	else if (m_email_active && !m_tumblr_active)
	{
		url = m_complete_email_string;
	}
	else if (!m_email_active && m_tumblr_active)
	{
		url = m_complete_tumblr_string;
	}


	qDebug() << "url: " << url;

	QEventLoop eventLoop;
	
	QUrl url_string = QUrl(QString("http://localhost:8080/?") + url);
	qDebug() << url_string.toEncoded();

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(url_string);
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if (reply->error() == QNetworkReply::NoError) {
		//success
		qDebug() << "Success" << reply->readAll();
		delete reply;
	}
	else {
		//failure
		qDebug() << "Failure" << reply->errorString();
		delete reply;
	}
}



void Sharing::setSaveImagePath(Landscape landscape)
{
	m_save_image_path = landscape.getSaveImagePath();
}

void Sharing::setPaintingIndex(Landscape landscape)
{
	m_painting_index = landscape.getPaintingIndex();
}

int Sharing::getPaintingIndex() const
{
	return m_painting_index;
}

void Sharing::sendEmail()
{
	QString eSubject = "Your Landscape from Picturing the Americas";
	QString image_path = m_save_image_path;
	//QString body = "Thanks for visiting Picturing the Americas at Crystal Bridges Museum of American Art and creating your own landscape-we've attached it to this email, and you can find it on our Tumblr page too.\r\rFeel free to share your artwork through social media! We always appreciate a tag, and you can follow us on Facebook, Twitter, and Instagram. You can use our hashtag, %23CrystalBridges, plus the exhibition hashtag, %23PicturingtheAmericas. \r\rYou can learn more about Picturing the Americas on our website. While you're there, sign up for our eNewsletter that we'll send directly to your inbox to keep you up to date with events and news from Crystal Bridges! \r\rThanks for visiting us, and come back soon, \r\rYour friends at Crystal Bridges\r\r";
	QString generate_text = LandscapeTextComposer::get().generateEmailText();

	if (m_email_address->getTextLine() == "")
	{
		m_email_active = false;
	}
	else
	{
		m_email_active = true;
	}

	if (m_email_active)
	{
		m_complete_email_string = "email=" + m_email_address->getTextLine() + "&esubject=" + eSubject + "&epath=" + image_path
			+ "&ecaption=" + generate_text;
	}

}


void Sharing::saveTumblr()
{
	if (m_tumblr_active)
	{
		QString image_path = m_save_image_path;
		QString caption = LandscapeTextComposer::get().getTitle();

		m_complete_tumblr_string = "tpath=" + image_path + "&tcaption=" + caption;
	}

}

void Sharing::backToMainDialogClosed(bool exit_to_main)
{
	if (exit_to_main)
	{
		hide();

		emit goBackToMain();
	}
}

void Sharing::keyPressed(QString text)
{
	m_email_address->setFocus();

	if (m_email_address)
	{
		//m_email_address->setFocus();
		const int max_length = 120;
		if (m_email_address->getTextLine().size() < max_length)
		{
		//	m_email_address->insertText(text);
		}
	}
}

void Sharing::keyPressedEvents(std::vector<QKeyEvent> key_events)
{
	m_email_address->setFocus();

	for (QKeyEvent key_event : key_events)
	{
		m_email_address->keyPress(&key_event, false);
	}

	disableSendButton();
}

QString Sharing::getCurrentEmailAddress() const
{
	if (m_email_address)
	{
		return m_email_address->getTextLine();
	}

	return "";
}