#include "stdafx.h"
#include "IEdgeDetect.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


IEdgeDetect::IEdgeDetect()
{
}


IEdgeDetect::~IEdgeDetect()
{
}

Mat IEdgeDetect::perform(Mat image) //vector<int> 
{
	return image;
}