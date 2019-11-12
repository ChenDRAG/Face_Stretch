#pragma once
#include <QMainWindow>
#include "Pic.h"


class Strech_Window : public QWidget
{
	Q_OBJECT

public:
	Strech_Window(QWidget *parent = 0);
	~Strech_Window();
private:
	QLabel* interpL;
	QComboBox* interpC;

	Pic* srcP;
	QLabel* srcL;
	Pic* dstP;
	QLabel* dstL;
	Pic* resP;
	QLabel* resL;

	QString srcfile;
	QString dstfile;
	QString resfile;
	QStringList InterM;
	bool inputChanged;
	void update();
	bool load(Pic* p);
};
