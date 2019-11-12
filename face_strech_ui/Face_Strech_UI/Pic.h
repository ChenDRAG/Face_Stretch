#pragma once
#include "stdafx.h"
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QResizeEvent>

class Pic : public QLabel
{
	Q_OBJECT
public:
	explicit Pic(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~Pic();
	QPixmap Starter;
	QPixmap image;
	QPixmap scaledPixmap() const;


signals:
	void clicked();

public slots:
	void Startwith(QString filename);
	void setPixmap(QString filename);
	void resizeEvent(QResizeEvent *);
private:
	void mousePressEvent(QMouseEvent* event);
	void setPixmap(const QPixmap&);
};

