#pragma once
#include "Matmath.h"
#include "stdafx.h"
#include <fstream>
enum Warp_Method
{
	Alpha,
	Spherical,
	TPS_
};
Point2d AlphaWrap(const Point2d& p, const Point2d& c, float alpha_max, float r);
Point2d SphericalWarp(const Point2d& p, const Point2d& c, float r);

