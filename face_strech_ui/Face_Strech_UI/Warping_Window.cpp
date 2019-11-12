#include "stdafx.h"
#include "Warping_Window.h"
#include "Warping.h"
#include "Interp.h"

Warping_Window::Warping_Window(QWidget *parent)
	: QWidget(parent)
{
	interpL = new QLabel(tr("Interpolation Method"), this);
	interpL->setAlignment(Qt::AlignCenter);
	interpC = new QComboBox(this);
	interpC->setMinimumHeight(20);
	InterM << tr("nearest") << tr("bilinear") << tr("bicubic");
	interpC->addItems(InterM);

	warpL = new QLabel(tr("Warping Method"), this);
	warpL->setAlignment(Qt::AlignCenter);
	warpC = new QComboBox(this);
	warpC->setMinimumHeight(20);
	warpM << tr("Whirlpool") << tr("Distortion");
	warpC->addItems(warpM);

	oriP = new Pic(this);
	oriP->setAlignment(Qt::AlignCenter);
	oriL = new QLabel(tr("Original"), this);
	oriL->setAlignment(Qt::AlignCenter);
	imgP = new Pic(this);
	imgP->setAlignment(Qt::AlignCenter);
	imgL = new QLabel(tr("Result"), this);
	imgL->setAlignment(Qt::AlignCenter);

	slider = new QSlider(Qt::Horizontal);
	sliderL = new QLabel(tr("Intensity"), this);
	slider->setMinimum(0);
	slider->setMaximum(100);
	slider->setValue(50);

	sliderR = new QSlider(Qt::Horizontal);
	sliderRL = new QLabel(tr("R"), this);
	sliderR->setMinimum(0);
	sliderR->setMaximum(100);
	sliderR->setValue(50);

	auto main = new QHBoxLayout;
	auto H1 = new QHBoxLayout;
	auto V2 = new QVBoxLayout;
	auto H1V1 = new QVBoxLayout;
	auto H1V2 = new QVBoxLayout;
	auto V2V1 = new QVBoxLayout;
	auto V2V2 = new QVBoxLayout;
	auto V2V3 = new QVBoxLayout;
	auto V2V4 = new QVBoxLayout;

	H1V1->addStretch();
	H1V1->addWidget(oriP, 4);
	H1V1->addWidget(oriL, 1);
	H1V1->addStretch();

	H1V2->addStretch();
	H1V2->addWidget(imgP, 4);
	H1V2->addWidget(imgL, 1);
	H1V2->addStretch();

	V2V1->addStretch();
	V2V1->addWidget(interpL);
	V2V1->addWidget(interpC);
	V2V1->addStretch();

	V2V2->addStretch();
	V2V2->addWidget(warpL);
	V2V2->addWidget(warpC);
	V2V2->addStretch();

	V2V3->addStretch();
	V2V3->addWidget(sliderL);
	V2V3->addWidget(slider);
	V2V3->addStretch();

	V2V4->addStretch();
	V2V4->addWidget(sliderRL);
	V2V4->addWidget(sliderR);
	V2V4->addStretch();

	H1->addLayout(H1V1, 1);
	H1->addLayout(H1V2, 1);

	V2->addLayout(V2V1, 1);
	V2->addLayout(V2V2, 1);
	V2->addLayout(V2V3, 1);
	V2->addLayout(V2V4, 1);

	main->addLayout(H1, 4);
	main->addLayout(V2, 1);

	this->setLayout(main);

	imgP->Startwith("./Resources/THU.jpg");
	oriP->Startwith("./Resources/THU.jpg");
	oriFile = "./Resources/THU.jpg";
	update();

	connect(oriP, &Pic::clicked, [&]() {
		load(oriP);
		update();
		});
	connect(interpC, &QComboBox::currentTextChanged, [&]() {
		//interpC->currentIndex();
		update();
		});
	connect(warpC, &QComboBox::currentTextChanged, [&]() {
		//interpC->currentIndex();
		if (warpC->currentIndex() == 0)
			sliderR->setVisible(true);
		else
			sliderR->setVisible(false);
		update();
		});
	connect(slider, &QSlider::valueChanged, [&]() {
		update();
		});
	connect(sliderR, &QSlider::valueChanged, [&]() {
		update();
		});
}



Warping_Window::~Warping_Window()
{
}

void Warping_Window::load(Pic *p)
{
	QString filename;
	filename = QFileDialog::getOpenFileName(this, tr("Plese select image"), "../picture/", tr("Images (*.png *.jpg *.bmp)"));
	if (filename.isEmpty())
		return;
	p->setPixmap(filename);
	oriP->setPixmap(filename);
	oriFile = filename;
}

//重新计算目标图像并显示
void Warping_Window::update()
{
	Warp_Method warp_m = Warp_Method(warpC->currentIndex());
	Interp_Method InterpM = Interp_Method(interpC->currentIndex());
	Mat src = imread(oriFile.toStdString());
	if (src.empty()) {
		printf("could not load image...\n");
		return ;
	}
	else
	{
		printf("Image loaded!\n");
	}
	
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	Mat dst_map = Mat::zeros(dst.rows, dst.cols, CV_64FC2);
	
	for (int i = 0; i < dst_map.rows; i++)
	{
		for (int j = 0; j < dst_map.cols; j++)
		{
			if (warp_m == Spherical)
				dst_map.at<Point2d>(i, j) = SphericalWarp(Point2d(i, j), Point2d(src.rows / 2, src.cols / 2), (slider->value()-50)*20);
			else if (warp_m == Alpha)
				dst_map.at<Point2d>(i, j) = AlphaWrap(Point2d(i, j), Point2d(src.rows / 2, src.cols / 2), (slider->value()-50) * 10, (sliderR->value())*10);
		}
	}
	printf("interp!\n");

	interp(dst_map, dst, src, InterpM);
	imwrite("./debug/buffer.jpg", dst);
	imgP->Startwith("./debug/buffer.jpg");
	return ;
}