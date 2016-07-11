#pragma once

#include <QString>
#include <QPixmap>

#include "common.h"
#include "stringhelper.h"

class LandscapeContentListing
{
public:

	LandscapeContentListing(const std::vector<QString>& items);

	inline QString getDescription() const;

	inline QString getTitleOption1() const;
	inline QString getTitleOption2() const;
	inline QString getTitleOption3() const;
	inline QString getTitleOption4() const;

	inline QString getId() const;

	inline QString getScale() const;

	inline QPixmap getImage() const;

	inline int getPaintingIndex() const;
	
	inline QString getMeaning(int index) const;

	inline QString getMeaningStateBeing(int index) const;

	inline QString getMeaningCharacteristic(int index) const;

	inline QString getMeaningCharacteristicOther(int index) const;

	inline QString getMeaning1AddingA() const;

	inline QString getMeaning2AddingA() const;

	inline QString getMeaning3AddingA() const;

	inline QString getMeaning1() const;

	inline QString getMeaning1StateBeing() const;

	inline QString getMeaning1Characteristic() const;

	inline QString getMeaning2() const;

	inline QString getMeaning2StateBeing() const;

	inline QString getMeaning2Characteristic() const;

	inline QString getMeaning3() const;

	inline QString getMeaning3StateBeing() const;

	inline QString getMeaning3Characteristic() const;

private:

	static const int DESCRIPTION = 0; // A
	static const int IMAGE_PATH = 1; // B
	static const int PAINTING_INDEX = 2; // C
	static const int SCALE = 3; // D
	static const int MEANING_1 = 4; // E 
	static const int MEANING_1_ADD_A = 5; // F
	static const int MEANING_1_STATE_BEING = 6; // G
	static const int MEANING_1_CHARACTERISTIC = 7; // H
	static const int MEANING_2 = 8; // I
	static const int MEANING_2_ADD_A = 9; // J
	static const int MEANING_2_STATE_BEING = 10; // K
	static const int MEANING_2_CHARACTERISTIC = 11; // L
	static const int MEANING_3 = 12; // M
	static const int MEANING_3_ADD_A = 13; // N
	static const int MEANING_3_STATE_BEING = 14; // O
	static const int MEANING_3_CHARACTERISTIC = 15; // P
	static const int CATEGORY = 16; // Q 
	static const int TITLE_OPTION_1 = 17; // R
	static const int TITLE_OPTION_2 = 18; // S
	static const int TITLE_OPTION_3 = 19; // T
	static const int TITLE_OPTION_4 = 20; // U

	static const int FIELD_COUNT = 21;

	mutable std::map<int, QString> m_fields;

	void loadImages();

	void loadImage(QPixmap& pixmap, QString path, QString name);

	QPixmap m_image;
};

QPixmap LandscapeContentListing::getImage() const
{
	return m_image;
}

QString LandscapeContentListing::getId() const
{
	return m_fields[IMAGE_PATH];
}

QString LandscapeContentListing::getDescription() const
{
	return m_fields[DESCRIPTION];
}

QString LandscapeContentListing::getTitleOption1() const
{
	return m_fields[TITLE_OPTION_1];
}

QString LandscapeContentListing::getTitleOption2() const
{
	return m_fields[TITLE_OPTION_2];
}

QString LandscapeContentListing::getTitleOption3() const
{
	return m_fields[TITLE_OPTION_3];
}

QString LandscapeContentListing::getTitleOption4() const
{
	return m_fields[TITLE_OPTION_4];
}

QString LandscapeContentListing::getScale() const
{
	return m_fields[SCALE];
}

int LandscapeContentListing::getPaintingIndex() const
{
	return Core::StringHelper::stringToInt(m_fields[PAINTING_INDEX].toStdString());
}

QString LandscapeContentListing::getMeaning(int index) const
{
	QString a = " a ";
	switch (index)
	{
	case 1:
		if (getMeaning1AddingA() == "yes")
			return a + getMeaning1();
		else
			return getMeaning1();

	case 2:
		if (getMeaning2AddingA() == "yes")
			return a + getMeaning2();
		else
			return getMeaning2();

	case 3:
		if (getMeaning3AddingA() == "yes")
			return a + getMeaning3();
		else
			return getMeaning3();

	default:
		return "";
	}


}

QString LandscapeContentListing::getMeaningStateBeing(int index) const
{
	switch (index)
	{
	case 1:
		return getMeaning1StateBeing();

	case 2:
		return getMeaning2StateBeing();

	case 3:
		return getMeaning3StateBeing();

	default:
		return "";
	}
}

QString LandscapeContentListing::getMeaningCharacteristic(int index) const
{
	switch (index)
	{
	case 1:
		return getMeaning1Characteristic();

	case 2:
		return getMeaning2Characteristic();

	case 3:
		return getMeaning3Characteristic();

	default:
		return "";
	}
}


QString LandscapeContentListing::getMeaningCharacteristicOther(int index) const
{
	switch (index)
	{
	case 1:
		return getMeaning2Characteristic();

	case 2:
		return getMeaning3Characteristic();

	case 3:
	default:
		return getMeaning1Characteristic();
	}
}

QString LandscapeContentListing::getMeaning1AddingA() const
{
	return m_fields[MEANING_1_ADD_A];
}

QString LandscapeContentListing::getMeaning2AddingA() const
{
	return m_fields[MEANING_2_ADD_A];
}

QString LandscapeContentListing::getMeaning3AddingA() const
{
	return m_fields[MEANING_3_ADD_A];
}

QString LandscapeContentListing::getMeaning1() const
{
	return m_fields[MEANING_1];
}

QString LandscapeContentListing::getMeaning1StateBeing() const
{
	return m_fields[MEANING_1_STATE_BEING];
}

QString LandscapeContentListing::getMeaning1Characteristic() const
{
	return m_fields[MEANING_1_CHARACTERISTIC];
}

QString LandscapeContentListing::getMeaning2() const
{
	return m_fields[MEANING_2];
}

QString LandscapeContentListing::getMeaning2StateBeing() const
{
	return m_fields[MEANING_2_STATE_BEING];
}

QString LandscapeContentListing::getMeaning2Characteristic() const
{
	return m_fields[MEANING_2_CHARACTERISTIC];
}

QString LandscapeContentListing::getMeaning3() const
{
	return m_fields[MEANING_3];
}

QString LandscapeContentListing::getMeaning3StateBeing() const
{
	return m_fields[MEANING_3_STATE_BEING];
}

QString LandscapeContentListing::getMeaning3Characteristic() const
{
	return m_fields[MEANING_3_CHARACTERISTIC];
}