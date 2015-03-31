#pragma once

#include "IHeightMeasure.h" 

//#include "stdafx.h"
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class HeightMeasurer : public IHeightMeasure
{
public:
	HeightMeasurer();
	~HeightMeasurer();
    float perform(Mat image);
	float measureHeight(Mat image);
	Point getTopPixel();
	void markPixel(Point point);
	Point getNextPixel(Point currentPixel, vector<Point> previousPixels);
    double computeAllEuclideanDistance(vector<Point> tiller);
    Mat getMarkedImage();
    bool isWhite(int x, int y);
};

