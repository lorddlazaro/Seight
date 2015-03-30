#ifndef HSVSegment_H
#define HSVSegment_H

#pragma once

#include "ISegment.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class HSVSegment : public ISegment
{
public:
	HSVSegment();
	~HSVSegment();
	Mat perform(Mat image);
    void setValues(vector<int> values);
};

#endif