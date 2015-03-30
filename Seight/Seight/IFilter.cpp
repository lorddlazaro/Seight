#include "stdafx.h"
#include "IFilter.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

IFilter::IFilter()
{
}


IFilter::~IFilter()
{
}

Mat IFilter::perform(Mat image)
{
    return image;
}