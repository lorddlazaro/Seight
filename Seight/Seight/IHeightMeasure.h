#pragma once
#ifndef IHeightMeasure_H
#define IHeightMeasure_H

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class IHeightMeasure
{
public:
	IHeightMeasure();
	~IHeightMeasure();
	virtual float perform(Mat image);
};

#endif IHeightMeasure_H