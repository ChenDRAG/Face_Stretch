
#include "Warping.h"
#include "stdafx.h"
//旋转畸变
Point2d AlphaWrap(const Point2d& p, const Point2d& c, float alpha_max, float r)
{
	Point2d t;
	alpha_max = alpha_max / 180. * 3.1415926;
	double dis = sqrt((p - c).x * (p - c).x + (p - c).y * (p - c).y);
	double alpha = alpha_max * (r - dis) / r;
	t.x = (p - c).x * cos(alpha) - (p - c).y * sin(alpha);
	t.y = (p - c).x * sin(alpha) + (p - c).y * cos(alpha);
	t = t + c;
	return t;
}

//球形畸变
Point2d SphericalWarp(const Point2d& p, const Point2d& c, float r)
{
	Point2d re;
	float dx = p.x - c.x;
	float dy = p.y - c.y;
	float d = sqrt(dx * dx + dy * dy);
	if (r == 0)
		r = 0.0001;
	if(r >= 0)
		if (d <= r)
		{
			re.x = r / d * asin(d / r) * dx + c.x;
			re.y = r / d * asin(d / r) * dy + c.y;
		}
		else
		{
			//赋值为无效点
			re.x = c.x * 4;
			re.y = c.y * 4;
		}
	else
		if (d <= (-1)*r)
		{
			re.x = dx/( r / d * asin(d / r)) + c.x;
			re.y = dy/( r / d * asin(d / r)) + c.y;
		}
		else
		{
			//赋值为无效点
			re.x = c.x * 4;
			re.y = c.y * 4;
		}
	return re;
}
