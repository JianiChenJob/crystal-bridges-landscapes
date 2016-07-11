#include "landscapetextcomposer.h"

#include "landscapecontentlisting.h"
#include "originalpaintinginfo.h"
#include "paintingitem.h"

#include <QDebug>

LandscapeTextComposer& LandscapeTextComposer::get()
{
	static LandscapeTextComposer composer;
	return composer;
}

void LandscapeTextComposer::setTitle(QString title)
{
	m_landscape_title = title;
}

QString LandscapeTextComposer::getTitle() const
{
	return m_landscape_title;
}

void LandscapeTextComposer::setPaintingNumber(int painting_number)
{
	m_base_painting_title = OriginalPaintingInfo::get().getTitle(painting_number);

	m_base_painting_artist = OriginalPaintingInfo::get().getArtist(painting_number);
	qDebug() << m_base_painting_artist;
	m_decade_base_work = OriginalPaintingInfo::get().getDate(painting_number);

	m_location_base_work = OriginalPaintingInfo::get().getLocation(painting_number);
}

LandscapeTextComposer::LandscapeTextComposer()
{
}

LandscapeTextComposer::~LandscapeTextComposer()
{
}

void LandscapeTextComposer::setLargestContent(PaintingItem *item)
{
	if (!item)
	{
		return;
	}

	if (LandscapeContentListing *listing = item->getListing())
	{
		m_largest_symbol_meaning = listing->getMeaning(item->getSymbolSelected());

		m_largest_symbol_description = listing->getDescription();

		m_largest_symbol_title_option1 = listing->getTitleOption1();

		m_largest_symbol_title_option2 = listing->getTitleOption2();

		m_largest_symbol_title_option3 = listing->getTitleOption3();

		m_largest_symbol_title_option4 = listing->getTitleOption4();
	}
}

void LandscapeTextComposer::setSecondLargestContent(PaintingItem *item)
{
	if (!item)
	{
		return;
	}

	if (LandscapeContentListing *listing = item->getListing())
	{
		m_second_largest_symbol_name = listing->getDescription();

		m_location_within_painting = item->getLocation();

		m_state_being_chose_meaning_second_largest_symbol = 
			listing->getMeaningStateBeing(item->getSymbolSelected());
	}
}

void LandscapeTextComposer::setThirdLargestContent(PaintingItem *item)
{
	if (!item)
	{
		return;
	}

	if (LandscapeContentListing *listing = item->getListing())
	{
		m_characteristic_meaning_third_largest_symbol = 
			listing->getMeaningCharacteristic(item->getSymbolSelected());

		m_third_largest_symbol = listing->getDescription();

		m_characteristic_third_largest_symbol = 
			listing->getMeaningCharacteristicOther(item->getSymbolSelected());
	}
}

QString LandscapeTextComposer::generateText() const
{
	QString text = m_landscape_title +
		", which is reminiscent of " + m_base_painting_title + " by " + m_base_painting_artist +
		", depicts " + m_largest_symbol_meaning + " with its focus on the " + m_largest_symbol_description + ". Set in " +
		m_decade_base_work + "'s " + m_location_base_work + ", the prominent " + m_second_largest_symbol_name +
		" " + m_location_within_painting + " alludes to a time when Americans were " + m_state_being_chose_meaning_second_largest_symbol + "." +
		" Some may view this work as " + m_characteristic_meaning_third_largest_symbol +
		" due to the presence of the " + m_third_largest_symbol + ", while others may interpret it as " +
		m_characteristic_third_largest_symbol + ".";

	return text;
}

QString LandscapeTextComposer::generateEmailText()
{
	QString artist = "Tarsila do Amaral";
	QString encoded_title = "S%E3o Paulo";

	if (m_base_painting_artist == artist)
	{
		m_base_painting_title = encoded_title;
		m_location_base_work = encoded_title;
	}

	QString text = m_landscape_title +
		", which is reminiscent of " + m_base_painting_title + " by " + m_base_painting_artist +
		", depicts " + m_largest_symbol_meaning + " with its focus on the " + m_largest_symbol_description + ". Set in " +
		m_decade_base_work + "'s " + m_location_base_work + ", the prominent " + m_second_largest_symbol_name +
		" " + m_location_within_painting + " alludes to a time when Americans were " + m_state_being_chose_meaning_second_largest_symbol + "." +
		" Some may view this work as " + m_characteristic_meaning_third_largest_symbol +
		" due to the presence of the " + m_third_largest_symbol + ", while others may interpret it as " +
		m_characteristic_third_largest_symbol + ".";

	return text;
}

