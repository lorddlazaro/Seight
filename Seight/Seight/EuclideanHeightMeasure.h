#pragma once

#ifndef EuclideanHeightMeasure_H
#define EuclideanHeightMeasure_H

#include "IHeightMeasure.h"

class EuclideanHeightMeasure : public IHeightMeasure
{
public:
	EuclideanHeightMeasure();
	~EuclideanHeightMeasure();
	float perform(Mat image);
	float getDistance(float x, float y);
};

#endif EuclideanHeightMeasure_H