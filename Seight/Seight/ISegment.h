#ifndef ISegment_H
#define ISegment_H

#include "stdafx.h"
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ISegment
{
public:
	ISegment();
	~ISegment();
	virtual Mat ISegment::perform(Mat image); //vector<Point> perform(&Mat);
};

#endif