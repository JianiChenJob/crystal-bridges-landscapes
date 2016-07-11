//keyboard.cpp
//Purpose: Keyboard

//@author Jiani Chen
#include "keyboard.h"

#include "cmlincludes.h"
#include "inputevents.h"

#include <QKeyEvent>

using namespace Core;
using namespace Scene;

Keyboard::Keyboard() :
	m_caps_on(true),
	m_special_on(false)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::setup(LandscapesMainScene *main_scene)
{
	LandscapeState::setup(main_scene);

	setRootContainer("Keyboard");

	m_cap_keys = m_screen->getContainer("keyboardCapKeys");
	m_lower_keys = m_screen->getContainer("keyboardLowerKeys");
	m_special_keys = m_screen->getContainer("keyboardSpecialKeys");

	m_screen->setText("ANDText", "&");

	QList<std::string> keys = QList<std::string>() <<
		"Q" << "W" << "E" << "R" << "T" << "Y" << "U" << "I" << "O" << "P"
		<< "A" << "S" << "D" << "F" << "G" << "H" << "J" << "K" << "L"
		<< "Z" << "X" << "C" << "V" << "B" << "N" << "M" << "@" << "." << "@1" << ".1" 
		<< "q" << "w" << "e" << "r" << "t" << "y" << "u" << "i" << "o" << "p"
		<< "a" << "s" << "d" << "f" << "g" << "h" << "j" << "k" << "l"
		<< "z" << "x" << "c" << "v" << "b" << "n" << "m"
		<< "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0" 
		<< "!" << "#" << "$" << "%" << "^" << "AND" << "*" << "{" << "}" << "SPACE"
		<< "+" << "_" << "=" << "|" << "/" << "-" << "'" << "?" << "`" << "~" << ".com";

	for (int i = 0; i != keys.size(); ++i)
	{
		connectButton(m_screen, keys[i], &Keyboard::keyPressed);
	}

	connectButton(m_screen, "DELETE", &Keyboard::deleteKeyPressed);

	connectToggle(m_screen, "SHIFT", &Keyboard::shiftStateChanged);

	connectToggle(m_screen, "SPECIAL", &Keyboard::specialStateChanged);
}

void Keyboard::reset()
{
	if (m_screen->getToggle("SHIFT")->isOn())
	{
		m_screen->setToggle("SHIFT", "off");
		shiftStateChanged(m_screen->getToggle("SHIFT"));
	}

	if (m_screen->getToggle("SPECIAL")->isOn())
	{
		m_screen->setToggle("SPECIAL", "off");
		specialStateChanged(m_screen->getToggle("SPECIAL"));
	}
}

void Keyboard::keyPressed(const std::string& id)
{
	qDebug() << "Key pressed " << id.c_str();

	QString key = QString::fromStdString(id);
	if (key == "AND")
	{
		key = "&";
	}

	if (key == "@1")
	{
		key = "@";
	}

	if (key == ".1")
	{
		key = ".";
	}

	if (key == "SPACE")
	{
		key = " ";
	}

	emit keyPress(key);

	std::vector<QKeyEvent> key_events;

	QKeyEvent key_event(QEvent::KeyPress, 0,
		Qt::NoModifier,
		key);

	key_events.push_back(key_event);

	emit keyPressEvents(key_events);
}

void Keyboard::deleteKeyPressed(const std::string& id)
{
	qDebug() << "Delete pressed" << id.c_str();

	emit deletePress();

	std::vector<QKeyEvent> key_events;

	QKeyEvent key_event(QEvent::KeyPress, Qt::Key::Key_Backspace,
		Qt::NoModifier,
		"");

	key_events.push_back(key_event);
	
	emit keyPressEvents(key_events);
}

void Keyboard::shiftStateChanged(CmlToggle *toggle)
{
	if (m_special_on)
	{
		return;
	}

	m_caps_on = toggle->isOn();

	m_cap_keys->setVisible(m_caps_on);
	m_lower_keys->setVisible(!m_caps_on);
}

void Keyboard::specialStateChanged(CmlToggle *toggle)
{
	m_special_on = toggle->isOn();

	if (m_special_on)
	{
		m_special_keys->setVisible(true);
		m_screen->setVisible("nonSpecialKeys", false);

		m_cap_keys->setVisible(false);
		m_lower_keys->setVisible(false);
	}
	else
	{
		m_special_keys->setVisible(false);
		m_screen->setVisible("nonSpecialKeys", true);

		m_cap_keys->setVisible(m_caps_on);
		m_lower_keys->setVisible(!m_caps_on);
	}
}
