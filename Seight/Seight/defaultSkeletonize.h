#pragma once

#ifndef defaultSkeletonize_H
#define defaultSkeletonize_H

#include "ISkeletonize.h"

class defaultSkeletonize : public ISkeletonize
{
public:
	defaultSkeletonize();
	~defaultSkeletonize();
	void perform(Mat image);
	void thinning(Mat& im);
	void thinningIteration(Mat& im, int iter);
};

#endif defaultSkeletonize_H