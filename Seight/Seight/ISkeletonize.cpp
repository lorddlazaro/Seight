#include "stdafx.h"
#include "ISkeletonize.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

ISkeletonize::ISkeletonize()
{
}


ISkeletonize::~ISkeletonize()
{
}

Mat ISkeletonize::perform(Mat image) //vector<int>
{
    return image;
}

