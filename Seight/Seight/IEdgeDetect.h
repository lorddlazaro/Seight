#ifndef IEdgeDetect_H
#define IEdgeDetect_H

#include "stdafx.h"
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class IEdgeDetect
{
public:
	IEdgeDetect();
	~IEdgeDetect();
	virtual Mat perform(Mat image);
};

#endif
