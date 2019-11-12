#include "stdafx.h"
#include "Matmath.h"
//本文件实现所有需要用到的opencv mat数据的数学类运算
void mymath::cut(Mat& cont, const Mat& src, int sx, int fx, int sy, int fy)//最后改动 TODO
{
	for (int i = sx; i < fx; i++)
	{
		for (int j = sy; j < fy; j++)
		{
			if (cont.type() == CV_64F)
				cont.at<double>(i - sx, j - sy) = src.at<double>(i, j);
			else
				cont.at<Vec3b>(i - sx, j - sy) = getcolor(src, i, j);
		}
	}
}

Mat mymath::multiply(const Mat& X, const Mat& Y)
{
	assert(X.cols == Y.rows);
	assert(!(X.channels() == 3 && Y.channels() == 3));
	double sum;
	Mat re;
	if (X.channels() == 1 && Y.channels() == 1)
	{
		re = Mat::zeros(X.rows, Y.cols, CV_64F);
		for (int i = 0; i < re.rows; i++)
		{
			for (int j = 0; j < re.cols; j++)
			{
				sum = 0;
				for (int k = 0; k < X.cols; k++)
				{
					sum += X.at<double>(i, k) * Y.at<double>(k, j);
				}
				re.at<double>(i, j) = sum;
			}
		}
	}
	else if (X.channels() == 3 || Y.channels() == 3)
	{
		re = Mat::zeros(X.rows, Y.cols, CV_8UC3);
		for (int i = 0; i < re.rows; i++)
		{
			for (int j = 0; j < re.cols; j++)
			{
				Vec3f sum = 0;
				for (int k = 0; k < X.cols; k++)
				{
					if (X.channels() == 3)
						sum = sum + Vec3f(X.at<Vec3b>(i, k)) * Y.at<double>(k, j);
					else
						sum = sum + X.at<double>(i, k) * Vec3f(Y.at<Vec3b>(k, j));
				}
				for (int i = 0; i < 3; i++)
				{
					sum[i] = sum[i] < 255 ? sum[i] : 255;
					sum[i] = sum[i] > 0 ? sum[i] : 0;
				}
				re.at<Vec3b>(i, j) = Vec3b(sum);
			}
		}
	}
	return re;
}

void mymath::concatenate(const Mat& x, const Mat& y, Mat& re, const int axis)
{
	if (axis == 0)
	{
		assert(x.rows == y.rows);
		re = Mat(x.rows, x.cols + y.cols, CV_64F);
		for (int i = 0; i < x.rows; i++)
			for (int j = 0; j < x.cols; j++)
				re.at<double>(i, j) = x.at<double>(i, j);
		for (int i = 0; i < y.rows; i++)
			for (int j = 0; j < y.cols; j++)
				re.at<double>(i, j + x.cols) = y.at<double>(i, j);
	}
	else if (axis == 1)
	{
		assert(x.cols == y.cols);
		re = Mat(x.rows + y.rows, y.cols, CV_64F);
		for (int i = 0; i < x.rows; i++)
			for (int j = 0; j < x.cols; j++)
				re.at<double>(i, j) = x.at<double>(i, j);
		for (int i = 0; i < y.rows; i++)
			for (int j = 0; j < y.cols; j++)
				re.at<double>(i + x.rows, j) = y.at<double>(i, j);
	}
}

Mat mymath::trans(const Mat& x)
{
	Mat y(x.cols, x.rows, CV_64F);
	for (int i = 0; i < x.rows; i++)
	{
		for (int j = 0; j < x.cols; j++)
		{
			y.at<double>(j, i) = x.at<double>(i, j);
		}
	}
	return y;
}

Mat mymath::solve(const Mat& X, const Mat& Y)
{
	//TODO
	assert(X.cols == X.rows);
	Mat X_inv;
	invert(X, X_inv, DECOMP_SVD);
	return multiply(X_inv, Y);
}

Vec3b mymath::getcolor(const Mat& src, int x, int y)
{
	if (x < 0 || y < 0 || x >= src.rows || y >= src.cols)
		return Vec3b(0, 0, 0);
	else
		return src.at<Vec3b>(x, y);
}
