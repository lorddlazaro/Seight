#ifndef IPerspectiveCorrect_H
#define IPerspectiveCorrect_H
#include <opencv2/opencv.hpp>
#include "stdafx.h"

using namespace cv;

class IPerspectiveCorrect
{
public:
	IPerspectiveCorrect();
	~IPerspectiveCorrect();
	virtual Mat perform(Mat image);
};

#endif
