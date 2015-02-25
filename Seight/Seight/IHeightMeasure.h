#pragma once
#ifndef IPreprocess_H
#define IPreprocess_H

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

#endif IPreprocess_H