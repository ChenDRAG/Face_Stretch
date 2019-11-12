#pragma once

#include <QMainWindow>
#include "Pic.h"


class Warping_Window : public QWidget
{
	Q_OBJECT

public:
	Warping_Window(QWidget *parent = 0);
	~Warping_Window();
private:
	QLabel* interpL;
	QComboBox* interpC;
	QStringList InterM;

	Pic* imgP;
	QLabel* imgL;
	QString imgFile;
	
	Pic* oriP;
	QLabel* oriL;
	QString oriFile;

	QLabel* warpL;
	QComboBox* warpC;
	QStringList warpM;

	QSlider* slider;
	QLabel* sliderL;

	QSlider* sliderR;
	QLabel* sliderRL;

	void load(Pic* p);
	void Warping_Window::update();
};
