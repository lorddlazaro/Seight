#pragma once

#ifndef defaultSegment_H
#define defaultSegment_H

#include "ISegment.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class defaultSegment : public ISegment
{
public:
	defaultSegment();
	~defaultSegment();
	Mat perform(Mat image);
	void showImage(string name, Mat image);
	Mat addMatrices(Mat image1, Mat image2);
	void remove_contours(vector<vector<Point>>&contours, double cmin, double cmax);
};

#endif