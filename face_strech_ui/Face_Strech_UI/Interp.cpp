
#include "stdafx.h"
#include "Interp.h"
#include "Matmath.h"
void nearestInterp(const Mat& map, Mat& dst, const Mat& src)
{

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int x = floor(map.at<Point2d>(i, j).x + 0.5);
			int y = floor(map.at<Point2d>(i, j).y + 0.5);
			dst.at<Vec3b>(i, j) = mymath::getcolor(src, x, y);
		}
	}
}

void bi_linearInterp(const Mat& map, Mat& dst, const Mat& src)
{
	//     y1  y2
	//x1
	//x2
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int x1 = floor(map.at<Point2d>(i, j).x);
			int x2 = x1 + 1;
			int y1 = floor(map.at<Point2d>(i, j).y);
			int y2 = y1 + 1;
			Vec3b color1, color2, color3, color4;
			color1 = mymath::getcolor(src, x1, y1);
			color2 = mymath::getcolor(src, x1, y2);
			color3 = mymath::getcolor(src, x2, y1);
			color4 = mymath::getcolor(src, x2, y2);
			dst.at<Vec3b>(i, j)
				= color1 * (x2 - map.at<Point2d>(i, j).x) * (y2 - map.at<Point2d>(i, j).y)
				+ color2 * (x2 - map.at<Point2d>(i, j).x) * (map.at<Point2d>(i, j).y - y1)
				+ color3 * (map.at<Point2d>(i, j).x - x1) * (y2 - map.at<Point2d>(i, j).y)
				+ color4 * (map.at<Point2d>(i, j).x - x1) * (map.at<Point2d>(i, j).y - y1);
		}
	}
}

float S(float uv)
{
	if (fabs(uv) < 1)
		return 1 - 2 * pow(fabs(uv), 2) + pow(fabs(uv), 3);
	else if (fabs(uv) < 2)
		return 4 - 8 * fabs(uv) + 5 * pow(fabs(uv), 2) - pow(fabs(uv), 3);
	else
		return 0.;
}

void bicubicInterp(const Mat& map, Mat& dst, const Mat& src)
{
	// x0 x1 x2 x3
	int  x1, y1;
	double u, v;
	Mat X = Mat::zeros(1, 4, CV_64F);
	Mat Y = Mat::zeros(4, 1, CV_64F);
	Mat C = Mat::zeros(4, 4, CV_8UC3);
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			x1 = floor(map.at<Point2d>(i, j).x);
			y1 = floor(map.at<Point2d>(i, j).y);
			u = map.at<Point2d>(i, j).x - x1;
			v = map.at<Point2d>(i, j).y - y1;
			for (int i = 0; i < 4; i++)
				X.at<double>(0, i) = S(u - i + 1);
			for (int i = 0; i < 4; i++)
				Y.at<double>(i, 0) = S(v - i + 1),
				//all out of range points will be considered as black
				mymath::cut(C, src, x1 - 1, x1 + 3, y1 - 1, y1 + 3);

			dst.at<Vec3b>(i, j) = mymath::multiply(mymath::multiply(X, C), Y).at<Vec3b>(0, 0);
			//dst.at<Vec3b>(i, j) = (X * C * Y).at<Vec3b>(0, 0);
		}
	}
	return;
}

//插值调用函数
void interp(const Mat& map, Mat& dst, const Mat& src, Interp_Method method)
{
	if (method == nearest)
		nearestInterp(map, dst, src);
	else if (method == bi_linear)
		bi_linearInterp(map, dst, src);
	else if (method == bicubic)
		bicubicInterp(map, dst, src);

}


