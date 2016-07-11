//gallery.cpp
//Purpose: The gallery screen controls which gallery image is showing and related title text

//@author Jiani Chen

#include "gallery.h"

#include "cmlincludes.h"
#include "landscapetextcomposer.h"
#include "screenshottaker.h"
#include "imagehelper.h"
#include "stringhelper.h"
#include "mainapplication.h"

#include <QStandardPaths>
#include <QDir>
#include <QDate>

using namespace Scene;
using namespace Platform;
using namespace Core;

Gallery::Gallery()
{
}

Gallery::~Gallery()
{
}

void Gallery::setup(LandscapesMainScene *main_scene)
{
	LandscapeScreen::setup(main_scene);

	setRootContainer("GalleryView");

	for (int i = 1; i <= 4; ++i)
	{
		std::string index_string = QString("%1").arg(i).toStdString();

		CmlContainer *gallery = m_screen->getContainer("gallery" + index_string);

		m_galleries.push_back(gallery);

		connectImageUp(m_screen, "sharePaintingButton" + index_string, &Gallery::sharePaintingButtonPressed);

		connectImageUp(m_screen, "backToPaintingButton" + index_string, &Gallery::backToPaintingButtonPressed);

		connectImageUp(m_screen, "mainMenuPaintingButton" + index_string, &Gallery::mainMenuButtonPressed);
	}

	connectToggle(m_screen, "dropDownArrow", &Gallery::dropDownArrowPressed);

	m_sharing.setup(main_scene);

	connect(&m_sharing, &Sharing::goBackToMain,
		this, &Gallery::goBackToMain);

	m_back_to_main_dialog.setup(main_scene);

	connect(&m_back_to_main_dialog, &BackToMainMenuDialog::closed,
		this, &Gallery::backToMainDialogClosed);

	connectToggleGroup(m_screen, "titleOptionsToggles", &Gallery::titleOptionToggleBecameOn);
}

void Gallery::reset()
{
	if (isVisible())
	{
		setVisible(false);
	}

	m_sharing.reset();
}

//Which gallery is showing based on previous selections.
void Gallery::showPainting(Landscape landscape)
{


	int paint_index = landscape.getPaintingIndex();

	QPixmap painting = landscape.getPixmap();

	//double title_option_bkg_x;
	//double title_option_bkg_y;


	m_dropDownText = m_screen->getText("dropDownText");
	//title_option_bkg_x = m_dropDownText->getX() - 10;
	//title_option_bkg_y = m_dropDownText->getY() + 30;

	//CmlToggleGroup* titleOptionsToggles = m_screen->getToggleGroup("titleOptionsToggles");
	//titleOptionsToggles->CmlActor::setX(title_option_bkg_x);
	//titleOptionsToggles->CmlActor::setY(title_option_bkg_y);

	int index = paint_index - 1; // Painting index is 1-4
	for (unsigned int i = 0; i != m_galleries.size(); ++i)
	{
		m_galleries[i]->setVisible(i == index);

		if (CmlImage *gallery_image = static_cast<CmlImage*>(
			m_galleries[i]->getChildById("galleryPainting")))
		{
			if (!painting.isNull())
			{
				gallery_image->setImage(painting, false);
			}
		}

	}

	m_screen->setVisible("dropdown", true);

	LandscapeTextComposer::get().setPaintingNumber(paint_index);

	LandscapeTextComposer::get().setTitle("LANDSCAPE");

	QDate createDate = QDate::currentDate();
	QString createdDateString;
	createdDateString = createDate.longMonthName(createDate.month()) + " " + QString::number(createDate.day()) + ", " + QString::number(createDate.year());

	m_screen->setText("date", QString::fromStdString(StringHelper::toUpper(createdDateString.toStdString())));

	m_screen->setText("galleryText", LandscapeTextComposer::get().generateText());

	std::string largest_symbol_title_option1 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption1().toStdString());

	std::string largest_symbol_title_option2 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption2().toStdString());

	std::string largest_symbol_title_option3 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption3().toStdString());

	std::string largest_symbol_title_option4 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption4().toStdString());

	m_screen->setText("titleOptionsTextOff1", QString::fromStdString(largest_symbol_title_option1));
	m_screen->setText("titleOptionsTextOn1", QString::fromStdString(largest_symbol_title_option1));

	m_screen->setText("titleOptionsTextOff2", QString::fromStdString(largest_symbol_title_option2));
	m_screen->setText("titleOptionsTextOn2", QString::fromStdString(largest_symbol_title_option2));

	m_screen->setText("titleOptionsTextOff3", QString::fromStdString(largest_symbol_title_option3));
	m_screen->setText("titleOptionsTextOn3", QString::fromStdString(largest_symbol_title_option3));

	m_screen->setText("titleOptionsTextOff4", QString::fromStdString(largest_symbol_title_option4));
	m_screen->setText("titleOptionsTextOn4", QString::fromStdString(largest_symbol_title_option4));

	m_sharing.setSaveImagePath(landscape);

	m_sharing.setPaintingIndex(landscape);

	reset();

	m_screen->setToggleGroupAllOff("titleOptionsToggles");
	titleOptionToggleBecameOn("titleOptionsToggle1");

	show();
}

bool Gallery::mousePressEvent(QMouseEvent *mouse_event)
{
	return m_sharing.mousePressEvent(mouse_event);
}

bool Gallery::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
	return m_sharing.mouseReleaseEvent(mouseEvent);
}

bool Gallery::mouseMoveEvent(QMouseEvent *mouseEvent, vec2 delta)
{
	return m_sharing.mouseMoveEvent(mouseEvent, delta);
}

//Generate title options for this gallery
void Gallery::titleOptionToggleBecameOn(const std::string& id)
{
	std::string largest_symbol_title_option1 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption1().toStdString());

	std::string largest_symbol_title_option2 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption2().toStdString());

	std::string largest_symbol_title_option3 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption3().toStdString());

	std::string largest_symbol_title_option4 = StringHelper::toUpper(LandscapeTextComposer::get().getLargestSymbolTitleOption4().toStdString());

	m_screen->setToggle("dropDownArrow", "off");
	m_screen->setVisible("titleOptionsToggles", false);
	if (id == "titleOptionsToggle1")
	{
		LandscapeTextComposer::get().setTitle(LandscapeTextComposer::get().getLargestSymbolTitleOption1());
		m_screen->setText(m_dropDownText->getId(), QString::fromStdString(largest_symbol_title_option1));
		m_screen->setText("galleryText", LandscapeTextComposer::get().generateText());
	}
	else if (id == "titleOptionsToggle2")
	{
		LandscapeTextComposer::get().setTitle(LandscapeTextComposer::get().getLargestSymbolTitleOption2());
		m_screen->setText(m_dropDownText->getId(), QString::fromStdString(largest_symbol_title_option2));
		m_screen->setText("galleryText", LandscapeTextComposer::get().generateText());
	}
	else if (id == "titleOptionsToggle3")
	{
		LandscapeTextComposer::get().setTitle(LandscapeTextComposer::get().getLargestSymbolTitleOption3());
		m_screen->setText(m_dropDownText->getId(), QString::fromStdString(largest_symbol_title_option3));
		m_screen->setText("galleryText", LandscapeTextComposer::get().generateText());
	}
	else if (id == "titleOptionsToggle4")
	{
		LandscapeTextComposer::get().setTitle(LandscapeTextComposer::get().getLargestSymbolTitleOption4());
		m_screen->setText(m_dropDownText->getId(), QString::fromStdString(largest_symbol_title_option4));
		m_screen->setText("galleryText", LandscapeTextComposer::get().generateText());
	}
}

//When share painting button pressed, then add a watermark to the painting image and save it
void Gallery::sharePaintingButtonPressed(const std::string& id)
{
	QString folder_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Landscapes";
	if (!QDir(folder_path).exists())
	{
		QDir().mkdir(folder_path);
	}

	QString email_image_path = folder_path + "/email_painting.jpg";

	QString watermark_path = MainApplication::Instance->getContentPath() + "LandscapesAssets/13. Share Screen/watermark.png";

	QPixmap watermark = QPixmap(watermark_path);
	QPixmap pixmap = ScreenshotTaker::get().getSharingScreenPainting(m_sharing.getPaintingIndex());

	pixmap = pixmap.scaled(700, 545, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	m_pixmap_list.push_back(pixmap);
	m_position_list.push_back(QPoint(0, 0));

	m_pixmap_list.push_back(watermark);
	m_position_list.push_back(QPoint(0, 0));

	if (!m_pixmap_list.empty() && !m_position_list.empty())
	{
		QPointF upper_left;
		pixmap = ImageHelper::combineImages(m_pixmap_list, m_position_list, upper_left);
	}

	QFileInfo out_file_info(email_image_path);

	if (out_file_info.exists())
	{
		QFile::remove(out_file_info.absolutePath());
	}

	if (!pixmap.isNull())
	{
		QFile file(email_image_path);
		file.open(QIODevice::WriteOnly);
		pixmap.save(&file, "jpg", 97);
	}

	m_sharing.reset();

	m_sharing.show();
}

void Gallery::backToPaintingButtonPressed(const std::string& id)
{
	emit backToComposing();
}

void Gallery::mainMenuButtonPressed(const std::string& id)
{
	m_back_to_main_dialog.show();
}

void Gallery::backToMainDialogClosed(bool exit_to_main)
{
	if (exit_to_main)
	{
		emit goBackToMain();
	}
}

void Gallery::dropDownArrowPressed(CmlToggle *toggle)
{
	if (toggle->isOn())
	{
		m_screen->setVisible("titleOptionsToggles", true);
	}
	else
	{
		m_screen->setVisible("titleOptionsToggles", false);
	}
}