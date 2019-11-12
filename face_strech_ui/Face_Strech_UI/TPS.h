#include "stdafx.h"

class TPS
{
public:
	TPS(std::vector<Point2d>& src_ps, std::vector<Point2d>& dst_ps);
	TPS();
	std::vector<Point2d> static readfile(String filename);
	Point2d project(const Point2d& p);
	bool resetsrc(std::vector<Point2d>& ps);
	bool resetdst(std::vector<Point2d>& ps);
private:
	std::vector<Point2d> src_ps;
	std::vector<Point2d> dst_ps;
	bool updated;
	int _n;
	Mat _K;
	Mat _P;
	Mat _L;
	Mat _V;
	Mat _Y;
	Mat _W;
	Mat _A;
	Mat a1, ax, ay, w;
	bool update();
	double U(double x) { return x > 0.01 ? x * x * 2 * log(x) : 0.0; }
};