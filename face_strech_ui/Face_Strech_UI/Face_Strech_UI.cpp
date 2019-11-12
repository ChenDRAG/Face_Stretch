#include "stdafx.h"
#include "Face_Strech_UI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets/QApplication>
#include <direct.h>
#include <QWidget>
#include <QtWidgets>

void clearLayout(QLayout* layout)

{

	QLayoutItem* child;

	while (0 != (child = layout->takeAt(0)))

	{

		if (auto w = child->widget())

		{

			if (w->layout())

			{

				clearLayout(w->layout());

			}

			delete w;

		}

		if (auto l = child->layout())

		{

			clearLayout(l);

		}

		delete child;

	}

}

Face_Strech_UI::Face_Strech_UI(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);
	this ->setFixedSize(this->width(), this->height());
	setWindowTitle(tr("NA_project"));
	connect(ui.warping, &QPushButton::clicked, [&]() {
		Warping_Window* ww = new Warping_Window();
		//close();
		ww->show();
		});
	connect(ui.strech, &QPushButton::clicked, [&]() {
		Strech_Window* sw = new Strech_Window();
		//close();
		sw->show();
		});

}
