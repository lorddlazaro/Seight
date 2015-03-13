#pragma once

#ifndef YCrCbSegment_H
#define YCrCbSegment_H

#include "ISegment.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class YCrCbSegment : public ISegment
{
public:
	YCrCbSegment();
	~YCrCbSegment();
	Mat perform(Mat image);
};

#endif YCrCbSegment_H