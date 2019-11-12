#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Face_Strech_UI.h"
#include "Strech_Window.h"
#include "Warping_Window.h"

class Face_Strech_UI : public QMainWindow
{
	Q_OBJECT

public:
	Face_Strech_UI(QWidget *parent = Q_NULLPTR);

private:
	Ui::Face_Strech_UIClass ui;
};
