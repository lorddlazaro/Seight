#ifndef ISkeletonize_H
#define ISkeletonize_H

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ISkeletonize
{
public:
	ISkeletonize();
	~ISkeletonize();

	virtual Mat perform(Mat img); //vector<int>
};

#endif