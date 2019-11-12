#include "stdafx.h"
#include "TPS.h"
#include "Matmath.h"
#include <fstream>

TPS::TPS(std::vector<Point2d>& src_ps, std::vector<Point2d>& dst_ps)
{
	assert(src_ps.size() == dst_ps.size());
	this->src_ps = src_ps;
	this->dst_ps = dst_ps;
	this->updated = false;

}

TPS::TPS()
{
	this->updated = false;
}

//旨在剥离初始化程序与运算程序，在计算之前检查相关参数是否计算完毕，若否则计算
bool TPS::update()
{
	if (this->updated == true)
		return true;
	//update n V P Y
	_n = src_ps.size();
	_V = Mat::zeros(2, _n, CV_64F);
	for (int j = 0; j < _n; j++)
		_V.at<double>(0, j) = dst_ps[j].x;
	for (int j = 0; j < _n; j++)
		_V.at<double>(1, j) = dst_ps[j].y;
	mymath::concatenate(_V, Mat::zeros(2, 3, CV_64F), _Y, 0);
	_Y = mymath::trans(_Y);
	_P = Mat::zeros(_n, 3, CV_64F);
	for (int j = 0; j < _n; j++)
		_P.at<double>(j, 0) = 1;
	for (int j = 0; j < _n; j++)
		_P.at<double>(j, 1) = src_ps[j].x;
	for (int j = 0; j < _n; j++)
		_P.at<double>(j, 2) = src_ps[j].y;

	//update K L
	_K = Mat::zeros(_n, _n, CV_64F);
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _n; j++)
		{
			if (i == j)
				continue;
			double rij = sqrt((src_ps[i].x - src_ps[j].x) * (src_ps[i].x - src_ps[j].x) + (src_ps[i].y - src_ps[j].y) * (src_ps[i].y - src_ps[j].y));
			_K.at<double>(i, j) = this->U(rij);
		}
	}
	Mat temp1, temp2;
	mymath::concatenate(_K, _P, temp1, 0);
	mymath::concatenate(mymath::trans(_P), Mat::zeros(3, 3, CV_64F), temp2, 0);
	mymath::concatenate(temp1, temp2, _L, 1);

	//solve
	_A = mymath::solve(_L, _Y);
	a1 = Mat::zeros(1, 2, CV_64F);
	ax = Mat::zeros(1, 2, CV_64F);
	ay = Mat::zeros(1, 2, CV_64F);
	w = Mat::zeros(_n, 2, CV_64F);

	mymath::cut(a1, _A, _n, _n + 1, 0, 2);
	mymath::cut(ax, _A, _n + 1, _n + 2, 0, 2);
	mymath::cut(ay, _A, _n + 2, _n + 3, 0, 2);
	mymath::cut(w, _A, 0, _n, 0, 2);

	updated = true;
	return true;
}

//对外调用，接口函数，二维点映射
Point2d TPS::project(const Point2d& p)
{
	if (!updated)
		update();
	std::vector<double> u(_n);
	double rs;
	Point2d re;
	for (int i = 0; i < _n; i++)
	{
		rs = (src_ps[i].x - p.x) * (src_ps[i].x - p.x) + (src_ps[i].y - p.y) * (src_ps[i].y - p.y);
		u[i] = rs > 0.0001 ? rs * log(rs) : 0.0;
	}
	re.x = a1.at<double>(0, 0) + ax.at<double>(0, 0) * p.x + ay.at<double>(0, 0) * p.y;
	re.y = a1.at<double>(0, 1) + ax.at<double>(0, 1) * p.x + ay.at<double>(0, 1) * p.y;
	for (int i = 0; i < _n; i++)
	{
		re.x = re.x + u[i] * w.at<double>(i, 0);
		re.y = re.y + u[i] * w.at<double>(i, 1);
	}
	return re;
}

bool TPS::resetsrc(std::vector<Point2d>& ps)
{
	src_ps = ps;
	updated = false;
	return true;
}

bool TPS::resetdst(std::vector<Point2d>& ps)
{
	dst_ps = ps;
	updated = false;
	return true;
}

std::vector<Point2d> TPS::readfile(String filename)
{
	std::ifstream in(filename);
	double x, y;
	std::vector<Point2d> points;
	if (in.is_open())
	{
		while (!in.eof())
		{
			if (in >> x && in >> y)
				points.push_back(Point2d(y, x));
		}
	}

	return points;
}