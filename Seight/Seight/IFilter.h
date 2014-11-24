#ifndef IFilter_H
#define IFilter_H

//#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class IFilter
{
public:
	IFilter();
	~IFilter();
	virtual Mat perform(Mat img);
};

#endif