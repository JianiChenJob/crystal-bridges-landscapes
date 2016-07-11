//landscape.h
#pragma once

#include <QPixmap>

class Landscape
{
public:
	Landscape();
	~Landscape();

	inline void setPaintingIndex(int painting_index);
	inline int getPaintingIndex() const;

	inline void setPixmap(QPixmap pixmap);
	inline QPixmap getPixmap() const;

	inline void setSaveImagePath(QString save_image_path);
	inline QString getSaveImagePath() const;

private:

	int m_painting_index;

	QPixmap m_pixmap;

	QString m_save_image_path;
};

void Landscape::setPaintingIndex(int painting_index)
{
	m_painting_index = painting_index;
}

int Landscape::getPaintingIndex() const
{
	return m_painting_index;
}

void Landscape::setPixmap(QPixmap pixmap)
{
	m_pixmap = pixmap;
}

QPixmap Landscape::getPixmap() const
{
	return m_pixmap;
}

void Landscape::setSaveImagePath(QString save_image_path)
{
	m_save_image_path = save_image_path;
}

QString Landscape::getSaveImagePath() const
{
	return m_save_image_path;
}

Q_DECLARE_METATYPE(Landscape);