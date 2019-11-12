#include "stdafx.h"
#include "Pic.h"

/*
Pic.cpp and Pic.h were modified from https://www.cnblogs.com/grandyang/p/4299100.html
*/

Pic::Pic(QWidget* parent, Qt::WindowFlags f)
	: QLabel(parent) {
	setMinimumSize(1, 1);
}

Pic::~Pic() {}

void Pic::Startwith(QString filename)
{
	Starter = QPixmap(filename);
	if (!Starter.isNull())
		setPixmap(Starter);
}

void Pic::setPixmap(QString filename)
{
	setPixmap(QPixmap(filename));
}

void Pic::mousePressEvent(QMouseEvent* event) {
	emit clicked();
}

void Pic::setPixmap(const QPixmap& p)
{
	image = p;
	QLabel::setPixmap(p);
	this->adjustSize();
}

QPixmap Pic::scaledPixmap() const
{
	return image.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void Pic::resizeEvent(QResizeEvent*)
{
	if (!image.isNull())
		QLabel::setPixmap(scaledPixmap());
}
