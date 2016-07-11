#pragma once

#include <QObject>

class PaintingItem;

class LandscapeTextComposer
{
public:

	static LandscapeTextComposer& get();

	void setTitle(QString title);

	QString getTitle() const;

	void setPaintingNumber(int painting_number);

	void setLargestContent(PaintingItem *item);

	void setSecondLargestContent(PaintingItem *item);

	void setThirdLargestContent(PaintingItem *item);

	QString generateText() const;

	QString generateEmailText();

	inline QString getLargestSymbolTitleOption1();

	inline QString getLargestSymbolTitleOption2();

	inline QString getLargestSymbolTitleOption3();

	inline QString getLargestSymbolTitleOption4();
private:
	LandscapeTextComposer();
	~LandscapeTextComposer();

	QString m_landscape_title;

	QString m_base_painting_title;

	QString m_base_painting_artist;

	QString m_largest_symbol_meaning;

	QString m_largest_symbol_description;

	QString m_decade_base_work;

	QString m_location_base_work;

	QString m_second_largest_symbol_name;

	QString m_location_within_painting;

	QString m_state_being_chose_meaning_second_largest_symbol;

	QString m_characteristic_meaning_third_largest_symbol;

	QString m_third_largest_symbol;

	QString m_characteristic_third_largest_symbol;

	QString m_largest_symbol_title_option1;
	QString m_largest_symbol_title_option2;
	QString m_largest_symbol_title_option3;
	QString m_largest_symbol_title_option4;
};

QString LandscapeTextComposer::getLargestSymbolTitleOption1()
{
	return m_largest_symbol_title_option1;
}

QString LandscapeTextComposer::getLargestSymbolTitleOption2()
{
	return m_largest_symbol_title_option2;
}

QString LandscapeTextComposer::getLargestSymbolTitleOption3()
{
	return m_largest_symbol_title_option3;
}

QString LandscapeTextComposer::getLargestSymbolTitleOption4()
{
	return m_largest_symbol_title_option4;
}