#include "stdafx.h"

typedef std::string String;

namespace mymath {
	void cut(Mat& cont, const Mat& src, int sx, int fx, int sy, int fy);
	Mat multiply(const Mat& X, const Mat& Y);
	void concatenate(const Mat& x, const Mat& y, Mat& re, const int axis);
	Mat trans(const Mat& x);
	Mat solve(const Mat& X, const Mat& Y);
	Vec3b getcolor(const Mat& src, int x, int y);
}