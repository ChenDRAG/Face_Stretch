#include "stdafx.h"
#include "Strech_Window.h"
#include "Interp.h"
#include "TPS.h"
Strech_Window::Strech_Window(QWidget *parent)
	: QWidget(parent)
{
	interpL = new QLabel(tr("Interpolation"), this);
	interpL->setAlignment(Qt::AlignCenter);
	interpC = new QComboBox(this);
	interpC->setMinimumHeight(20);
	InterM << tr("nearest") << tr("bilinear") << tr("bicubic");
	interpC->addItems(InterM);

	srcP = new Pic(this);
	srcP->setAlignment(Qt::AlignCenter);
	srcL = new QLabel(tr("Source"), this);
	srcL->setAlignment(Qt::AlignCenter);

	resP = new Pic(this);
	resP->setAlignment(Qt::AlignCenter);
	resL = new QLabel(tr("Result"), this);
	resL->setAlignment(Qt::AlignCenter);

	dstP = new Pic(this);
	dstP->setAlignment(Qt::AlignCenter);
	dstL = new QLabel(tr("Destination"), this);
	dstL->setAlignment(Qt::AlignCenter);


	auto main = new QHBoxLayout;
	auto H1 = new QHBoxLayout;
	auto V2 = new QVBoxLayout;
	auto H1V1 = new QVBoxLayout;
	auto H1V2 = new QVBoxLayout;
	auto H1V3 = new QVBoxLayout;
	auto V2V1 = new QVBoxLayout;

	H1V1->addStretch();
	H1V1->addWidget(srcP, 4);
	H1V1->addWidget(srcL, 1);
	H1V1->addStretch();
	H1V2->addStretch();
	H1V2->addWidget(dstP, 4);
	H1V2->addWidget(dstL, 1);
	H1V2->addStretch();
	H1V3->addStretch();
	H1V3->addWidget(resP, 4);
	H1V3->addWidget(resL, 1);
	H1V3->addStretch();

	V2V1->addStretch();
	V2V1->addWidget(interpL);
	V2V1->addWidget(interpC);
	V2V1->addStretch();

	H1->addLayout(H1V1, 1);
	H1->addLayout(H1V2, 1);
	H1->addLayout(H1V3, 1);

	V2->addLayout(V2V1, 1);

	main->addLayout(H1, 4);
	main->addLayout(V2, 1);

	this->setLayout(main);

	resP->Startwith("./Resources/face-images/1.jpg");
	dstP->Startwith("./Resources/face-images/1.jpg");
	srcP->Startwith("./Resources/face-images/1.jpg");
	srcfile = "./Resources/face-images/1.jpg";
	resfile = "./Resources/face-images/1.jpg";
	dstfile = "./Resources/face-images/1.jpg";

	connect(interpC, &QComboBox::currentTextChanged, [&]() {
		update();
		});
	connect(resP, &Pic::clicked, [&]() {
		update(); });
	connect(srcP, &Pic::clicked, [&]() {
		if(load(srcP))
		{
		}
		});
	connect(dstP, &Pic::clicked, [&]() {
		if(load(dstP))
		{
		}
		});

}
Strech_Window::~Strech_Window()
{

}

bool Strech_Window::load(Pic* p)
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this, tr("Plese select image"), "../picture/", tr("Images (*.png *.jpg *.bmp)"));
	if (filename.isEmpty())
		return false;
	p->setPixmap(filename);
	if (p == srcP)
		srcfile = filename;
	else if (p == dstP)
		dstfile = filename;
	return true;
}

//重新计算目标图像并显示
void Strech_Window::update()
{
	Interp_Method InterpM = Interp_Method(interpC->currentIndex());
	Mat src = imread(srcfile.toStdString());
	if (src.empty()) {
		printf("could not load image...\n");
		QMessageBox::warning(this, tr("Illegal Input!"), tr("Not right src image format."), QMessageBox::Ok);
		return;
	}
	else
	{
		printf("Image loaded!\n");
	}
	Mat dstimg = imread(dstfile.toStdString());
	if (dstimg.empty()) {
		printf("could not load image...\n");
		QMessageBox::warning(this, tr("Illegal Input!"), tr("Not right dst image format."), QMessageBox::Ok);
		return;
	}
	else
	{
		printf("Image loaded!\n");
	}

	QString srcs = srcfile;
	QString dsts = dstfile;
	srcs.chop(3);
	dsts.chop(3);
	srcs = srcs + "txt";
	dsts = dsts + "txt";

	TPS tps;
	std::vector<Point2d> from = TPS::readfile(srcs.toStdString());
	std::vector<Point2d> to = TPS::readfile(dsts.toStdString());
	if (from.size() != 68 || to.size() != 68)
	{
		QMessageBox::warning(this, tr("Illegal Input!"), tr("Cannot detect keypoints file."), QMessageBox::Ok);
		return;
	}
	QMessageBox::warning(this, tr("Begin transforming"), tr("Please wait for 10 seconds."), QMessageBox::Ok);
	tps.resetsrc(to);
	tps.resetdst(from);
	Mat res = Mat::zeros(dstimg.rows, dstimg.cols, CV_8UC3);
	Mat dst_map = Mat::zeros(res.rows, res.cols, CV_64FC2);

	for (int i = 0; i < dst_map.rows; i++)
	{
		for (int j = 0; j < dst_map.cols; j++)
		{
			dst_map.at<Point2d>(i, j) = tps.project(Point2d(i, j));
		}
	}
	interp(dst_map, res, src, InterpM);
	imwrite("./debug/buffer.png", res);
	resP->Startwith("./debug/buffer.png");
	return;
}