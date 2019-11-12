#pragma once
#include "stdafx.h"
#include "Matmath.h"
#include <fstream>
 
enum Interp_Method
{
	nearest,
	bi_linear,
	bicubic
};
void bi_linearInterp(const Mat& map, Mat& dst, const Mat& src);
void bicubicInterp(const Mat& map, Mat& dst, const Mat& src);
float S(float uv);
void nearestInterp(const Mat& map, Mat& dst, const Mat& src);
void interp(const Mat& map, Mat& dst, const Mat& src, Interp_Method method);
