#pragma once

#include "stdafx.h"
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class HeightMeasurer
{
public:
	HeightMeasurer();
	~HeightMeasurer();
	int measureHeight(Mat image);
	Point getTopPixel(Mat image);
	void markPixel(Mat image, Point point);
	Point getNextPixel(Mat image, Point currentPixel, vector<Point> previousPixels);
};

